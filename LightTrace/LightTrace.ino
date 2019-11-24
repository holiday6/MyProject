#define leftAnalog A0
#define rightAnalog 15
#include <Servo.h>

int leftvalue=0,rightvalue=0;
Servo leftservo;
int pos = 1;

void setup() {
  // put your setup code here, to run once:
  /*left analog input pin of photoresistor*/
  pinMode(leftAnalog,INPUT);
  /*right analog input pin of photoresistor*/
  pinMode(rightAnalog,INPUT);
  leftservo.attach(9);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  leftvalue = analogRead(leftAnalog);
  rightvalue = analogRead(rightAnalog);
  
  Serial.print(leftvalue);
  Serial.print(" ");
  Serial.print(rightvalue+27);
  Serial.print(" ");
  Serial.print(pos);
  Serial.print("\n");
  for(pos = 1;pos<180;pos++)
  {
  leftservo.write(pos);
  //Serial.print(pos);
  delay(100);
  }
  delay(100);
  for(pos = 180;pos>0;pos--)
  {
  leftservo.write(pos);
  //Serial.print(pos);
  delay(100);
  }
  delay(100);
}
