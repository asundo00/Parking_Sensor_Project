#ifndef Network_Ping_h
#define Network_Ping_h

#include <avr/pgmspace.h>
#include <SPI.h>

// Payload that child sends to the parent
struct SensorData {
    float distance;
};

typedef enum {
  READ_SERIAL,
  GOTO_SLEEP,
  READ_SENSORS,
  RECEIVING_RADIO,
  SENDING_RADIO
} State;

#endif
