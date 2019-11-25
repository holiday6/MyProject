#define topAnalog_left A0
#define topAnalog_right A1
#define botAnalog_left A2
#define botAnalog_right A3
#define servo_xy_control 9
#define servo_z_control 10
#include <Servo.h>

int leftvalue=0,rightvalue=0;
Servo servo_xy,servo_z;
int pos_xy = 1,pos_z = 1;
int band_xy = 10,band_z = 10;
int tlv=0,trv=0,blv=0,brv=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(topAnalog_left,INPUT);
  pinMode(topAnalog_right,INPUT);
  pinMode(botAnalog_left,INPUT);
  pinMode(botAnalog_right,INPUT);
  servo_xy.attach(servo_xy_control);
  servo_z.attach(servo_z_control);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  tlv = analogRead(topAnalog_left);
  trv = analogRead(topAnalog_right);
  blv = analogRead(botAnalog_left);
  brv = analogRead(botAnalog_right);
  Serial.print(tlv);
  Serial.print(" ");
  trv = trv+27;
  Serial.print(trv);
  Serial.print("\n");
  Serial.print(blv);
  Serial.print(" ");
  Serial.print(brv);
  Serial.print("\n");
  

  if(abs(tlv+blv-trv-brv-27)>band_xy)
  {
    if(tlv+blv>trv+brv)
    {
      pos_xy++;
      if(pos_xy>180)
      {
        pos_xy=180;
      }
    }else{
      pos_xy--;
      if(pos_xy<0)
      {
        pos_xy=0;
      }
    }
    servo_xy.write(pos_xy);
  }
  if(abs(tlv+trv-blv-brv-27)>band_z)
  {
    if(tlv+trv>blv+brv)
    {
      pos_z++;
      if(pos_z>180)
      {
        pos_z=180;
      }
    }else{
      pos_z--;
      if(pos_z<0)
      {
        pos_z=0;
      }
    }
    servo_xy.write(pos_z);
  }
  Serial.print(pos_xy);
  Serial.print(" ");
  Serial.print(pos_z);
  Serial.print("\n");
  delay(500);












  
}
