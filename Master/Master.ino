#include <Wire.h>

union Buffer
{
    long lngNum;
    byte lngBytes[4];
};

const int red = 12;
const int green = 11;
const int blue = 10;
const int buzzerPin = 9;
const int enable = 2;
const int in1 = 3;
const int in2 = 4;

long temp = 0;
long distance = 0;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  Wire.setClock(400000);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(enable, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
}

void loop()
{
  byte Bytes[8];
  Buffer tempBuffer;
  Buffer distanceBuffer;
  int i = 0;
  Wire.requestFrom(10, 8);
  while(Wire.available())
  {
    Bytes[i++] = Wire.read();
  }
  for(int j = 0; j < 4; j++)
  {
    tempBuffer.lngBytes[j] = Bytes[j];
  }
  for(int j = 0; j < 4; j++)
  {
    distanceBuffer.lngBytes[j] = Bytes[j+4];
  }
  Serial.print("temp ");
  Serial.println(tempBuffer.lngNum);
  Serial.print("distance ");
  Serial.println(distanceBuffer.lngNum);
  temp = tempBuffer.lngNum;
  distance = distanceBuffer.lngNum;
  if(distance < 200)
  {
    buzzerOn();
    Serial.println("STAY AWAY!");
  }
  if(temp > 20 && temp < 30)
  {
    stopMotor();
    digitalWrite(blue, LOW);
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
  }
  else if(temp > 30)
  {
    rotateMotorOne();
    digitalWrite(blue, LOW);
    digitalWrite(red, HIGH); 
  	digitalWrite(green, LOW);
  }
  else if(temp < 20)
  {
    rotateMotorTwo();
    digitalWrite(blue, HIGH);
    digitalWrite(red, LOW);
    digitalWrite(green, LOW);
  }
}

void buzzerOn()
{
  tone(buzzerPin, 50);
  delay(200);
  noTone(buzzerPin); 
}
void stopMotor()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}
void rotateMotorOne()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}
void rotateMotorTwo()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}