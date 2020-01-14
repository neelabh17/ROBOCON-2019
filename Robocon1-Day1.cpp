#include <Wire.h>
#include <PS4BT.h>
#include <usbhub.h>
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>
#include <SoftwareSerial.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <Sabertooth.h> 
SoftwareSerial St1(NOT_A_PIN, 18);
SoftwareSerial St(NOT_A_PIN, 16);
Sabertooth ST(128,St);
Sabertooth ST1(128,St1);
USB Usb;
BTD Btd(&Usb);
PS4BT PS4(&Btd, PAIR);
bool printAngle, printTouch;
uint8_t oldL2Value, oldR2Value;
float x,a;
float m1=1.08;
float tfs=0.1;
float tfm=0.1; //tfm=0.1 for v = 20-50
float vel = -40;
int cvel = 0;
#define BNO055_SAMPLERATE_DELAY_MS (100)

Adafruit_BNO055 bno = Adafruit_BNO055(55);

void setup() {
  Serial.begin(9600);
  St.begin(9600);
  St1.begin(9600);
  #if !defined(_MIPSEL_)
  while (!Serial);
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1);
  }
  if(!bno.begin())
  {
    while(1);
  }
  bno.setExtCrystalUse(true);

}

int lavishvelocity() {  
  int force = PS4.getAnalogButton(R2);
  int ans = map (force,0,255,0,100);
    if (PS4.getAnalogButton(L2) != oldL2Value || PS4.getAnalogButton(R2) != oldR2Value) // Only write value if it's different
      PS4.setRumbleOn(PS4.getAnalogButton(L2), PS4.getAnalogButton(R2));
    oldL2Value = PS4.getAnalogButton(L2);
    oldR2Value = PS4.getAnalogButton(R2);
  return ans; 
}

void loop() {
  Usb.Task();
  int swi = 0;
  sensors_event_t event;
  bno.getEvent(&event);
  x = event.orientation.x;
  vel = -(lavishvelocity());
  if (PS4.getButtonClick(CIRCLE)) {
     a=x;
     if(a<10 || a>350){PS4.setLed(Red);}
   }
  if (PS4.getAnalogHat(LeftHatY) < 100){
    if(cvel<(-50)){swi=1;}
    else if(cvel>(-50)){swi=0;}
    if(x>a){
      float dif = x-a;
      if (dif>1){dif=1;}
      
      ST.motor(1,-(tfs*dif*cvel*swi));
      ST1.motor(1,cvel*(1+tfm*dif)*m1);
      ST1.motor(2,cvel*(1-tfm*dif));
    }
    else if(x<a){
      float dif = a-x;
      if (dif>1){dif=1;}
      ST.motor(1,(tfs*dif*cvel*swi));
      ST1.motor(1,cvel*(1-
      tfm*dif)*m1);
      ST1.motor(2,cvel*(1+tfm*dif));
    }
    else{ST1.motor(1,cvel*m1);
         ST1.motor(2,cvel);
  }
  if(cvel>vel){--cvel;}
  if(cvel<vel){++cvel;}
  
  }
  if(PS4.getAnalogHat(LeftHatY) > 100){
    if(cvel<0){++cvel;}
  }
  
  if (PS4.getButtonClick(SQUARE)) {
     ST.motor(1,0);
     ST1.motor(1,0);
     ST1.motor(2,0);
   }
  if (PS4.getButtonClick(L1)) {
      ST.motor(1,10);
      ST1.motor(2,10);
      ST1.motor(1,-10);
    }
  if (PS4.getButtonClick(R1)) {
      ST.motor(1,-10);
      ST1.motor(2,-10);
      ST1.motor(1,10);
    }
       
  if (PS4.getButtonClick(UP)) {
        PS4.setLed(Red);
        vel=-100;
      } if (PS4.getButtonClick(RIGHT)) {
        vel=-45;
        PS4.setLed(Blue);
      } if (PS4.getButtonClick(DOWN)) {
        vel=-30;
        PS4.setLed(Yellow);
      } if (PS4.getButtonClick(LEFT)) {
        vel=-70;
        PS4.setLed(Green);
      }
  if (PS4.getAnalogHat(RightHatX) > 140) {
      ST.motor(1,-(20));
      ST1.motor(2,10);
      ST1.motor(1,-(10));
   }
  if (PS4.getAnalogHat(RightHatX) < 100){
      ST.motor(1,20);
      ST1.motor(2,-(10));
      ST1.motor(1,10);
  }
}