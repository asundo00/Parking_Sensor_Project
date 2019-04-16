#ifndef Sensors_h
#define Sensors_h

#include <Arduino.h>
#include <Adafruit_Sensor.h>

#define inputPin 2



class SENSORS {
public:
        SENSORS();
        ~SENSORS();

        float distance();
            //void printMotion(int);

};

#endif
