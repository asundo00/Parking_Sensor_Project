#include "printf.h"
#include "Sensors.h"
#include "Network_Ping.h"
#include "Radio_nRF.h"

// These are the Octal addresses that will be assigned
const uint16_t node_address_set[10] = { 00, 02, 05, 012, 015, 022, 025, 032, 035, 045 };

// 0 = Master
// 1-2 (02,05)   = Children of Master(00)
// 3,5 (012,022) = Children of (02)
// 4,6 (015,025) = Children of (05)
// 7   (032)     = Child of (02)
// 8,9 (035,045) = Children of (05)

uint16_t this_node;                           // Our node address
uint8_t NODE_ADDRESS = 2;  // Use numbers 0 through to select an address from the array
const int trigPin = 5;
const int echoPin = 6;


/***********************************************************************/
/***********************************************************************/

unsigned long last_time_sent;
const unsigned long interval = 1000; // ms       // Delay manager to send pings regularly.

/***********************************************************************/
/***********************************************************************/

bool send_T(uint16_t to);                      // Prototypes for functions to send & handle messages

SENSORS sensor;

RADIO radioNRF;

/*----------- Radio variables -----------*/
// Payload that the child sends to a parent
SensorData sensorData;

void setup(){

  Serial.begin(115200);
  pinMode(inputPin, INPUT);

pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(4, OUTPUT);

  this_node = node_address_set[NODE_ADDRESS];            // Which node are we?

  //sensor.PIR_init();

  radioNRF.nRF_init();
  radioNRF.nRF_network_init(this_node);

  printf_begin();
  printf_P(PSTR("\n\rRF24Network/examples/meshping/\n\r"));

}

void loop(){

  State state = GOTO_SLEEP;
  for(;;) {
    switch(state) {
      case READ_SERIAL:
        state = GOTO_SLEEP;
        break;
      case GOTO_SLEEP:
        //state = RECEIVING_RADIO;
        state = READ_SENSORS;
        break;
     case READ_SENSORS:
        sensorData.distance = sensor.distance();
      Serial.println(sensorData.distance);
        delay(2000); // give some time to send data over Serial
      state = SENDING_RADIO;
        break;
      case SENDING_RADIO:
        if ( millis() - last_time_sent >= interval ){                     // Send sensor data to the next node every 'interval' ms
          last_time_sent = millis();
          if ( this_node > 00){
            if (send_T(00)){                                              // Notify us of the result
                printf_P(PSTR("%lu: APP Send ok\n\r"),millis());
            }else{
                printf_P(PSTR("%lu: APP Send failed\n\r"),millis());
                last_time_sent -= 100;                                    // Try sending at a different time next time due to possible collisions
          }
          }
       }
        state = RECEIVING_RADIO;
        break;
      case RECEIVING_RADIO:
        SensorData sensorDataRec;
        radioNRF.RF_receive(sensorDataRec, this_node);
        state = READ_SERIAL;
        break;
    }
  }

}

/**
 * Send a message containing sensor data
 */
bool send_T(uint16_t to)
{
  return radioNRF.RF_send(to, sensorData);
}
