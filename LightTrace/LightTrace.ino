#define leftAnalog A0
#define rightAnalog A1
#define servo_xy_control 9
#define servo_z_control 10
#include <Servo.h>

int leftvalue=0,rightvalue=0;
Servo servo_xy,servo_z;
int pos = 1;

void setup() {
  // put your setup code here, to run once:
  pinMode(leftAnalog,INPUT);
  pinMode(rightAnalog,INPUT);
  servo_xy.attach(servo_xy_control);
  servo_z.attach(servo_z_control);
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

  int compare = leftvalue-rightvalue;
  if(compare>10)
  {
    pos++;
    if(pos>=180)
    {
      pos = 180;
    }
    servo_xy.write(pos);
  }else if(compare<0)
  {
    pos--;
    if(pos<0)
    {
      pos = 0;
    }
    servo_xy.write(pos);
  }
  delay(300);












  
}
