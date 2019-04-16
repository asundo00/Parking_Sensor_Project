#include "Sensors.h"

#define IN4  4
const int trigPin = 5;
const int echoPin = 6;

SENSORS::SENSORS(){}
SENSORS::~SENSORS(){}

float SENSORS::distance(){

  long duration;
  int distance = 0;

  delayMicroseconds(10);
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance); //distance is the returned integer, it is the distance in cm*/

  return distance;
  }
