#include <Wire.h>

union Buffer
{
    long lngNum;
    byte lngBytes[4];
};

const int tempSensor = A0;
volatile long temp;
const int triggerPin = 10; 
const int echoPin = 9; 
volatile long distance;

void setup()
{
  Serial.begin(9600);
  Wire.begin(10);
  Wire.onRequest(requestEvent);
}

void loop()
{
  delay(100);
}

void requestEvent()
{
  temp = getTemp();
  distance = getDistance();
  Buffer bufferTemp;
  bufferTemp.lngNum = temp;
  Buffer bufferDistance;
  bufferDistance.lngNum = distance;
  Wire.write(bufferTemp.lngBytes, 4);
  Wire.write(bufferDistance.lngBytes, 4);
  
}

long getTemp() {
  int tempInput = analogRead(A0);
  float voltage = tempInput * 5.0;
  voltage /= 1024.0; 
  float ftemperature = (voltage - 0.5) * 100 ; 
  long temp = (long) ftemperature;
  return temp;
}

long getDistance(){
  long duration, distance;
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 29 / 2;
  return distance;
}



