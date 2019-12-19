#define topAnalog_left A0
#define topAnalog_right A1
#define botAnalog_left A2
#define botAnalog_right A3
#define servo_xy_control 9
#define servo_z_control 10
#include <Servo.h>

int leftvalue=0,rightvalue=0;
Servo servo_xy,servo_z;
int pos_xy = 0,pos_z = 0;
int band_xy = 40,band_z = 40;
int tlv=0,trv=0,blv=0,brv=0;
int c_xy=0,c_z=0;
int pre_z=pos_z;
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
  Serial.print(trv);
  Serial.print("\n");
  Serial.print(blv);
  Serial.print(" ");
  Serial.print(brv);
  Serial.print("\n");
  
  
  if(abs(tlv+blv-trv-brv)>band_xy)
  {
    if(pos_z<=90)
    {
    if(tlv+blv>trv+brv)
    {
      pos_xy--;
      if(pos_xy<0)
      {
        pos_xy=0;
        
      }
    }else{
      pos_xy++;
      if(pos_xy>180)
      {
        pos_xy=180;
        
      }
    }
    }else{
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
    }
  }
  if(abs(tlv+trv-blv-brv)>band_z)
  {
    pre_z=pos_z;
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
    
  }
  
  servo_xy.write(pos_xy);
  servo_z.write(pos_z);
  
  Serial.print(pos_xy);
  Serial.print(" ");
  Serial.print(pos_z);
  Serial.print("\n");
  delay(150);












  
}
