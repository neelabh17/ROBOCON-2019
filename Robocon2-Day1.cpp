//--------- Libraries for Motor Controller --------------
#include <SoftwareSerial.h>
#include <Sabertooth.h>
#include <Kangaroo.h>
#include <Encoder.h>
//--------- Libraries for PS4 --------------
#include <PS4BT.h>
#include <usbhub.h>
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>
#include <Wire.h>
//--------- Libraries for IMU --------------
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
//------ Libraries for Ulrasonic Sensor ---------
#include "Ultrasonic.h"
// ----
USB Usb;
BTD Btd(&Usb);
PS4BT PS4(&Btd, PAIR);
Adafruit_BNO055 bno = Adafruit_BNO055(55);
Ultrasonic U1(2, 3);
Ultrasonic U2(4, 5);
//Ultrasonic U3(6, 7);
//Ultrasonic U4(8, 9);
//----
// ----
KangarooSerial  J(Serial3);
KangarooSerial  K(Serial2);           //       FRONT
KangarooChannel J1 (J, '1');           //    K2-------K1
KangarooChannel J2 (J, '2');           //     |       |
//LEFT |       | RIGHT
KangarooChannel K1 (K, '1');           //     |       |
KangarooChannel K2 (K, '2');           //    J1-------J2
//----
//----
imu::Vector<3> euler;
imu::Vector<3> gyro;
#define kang_ramp 1500
#define kang_deramp 15000
#define v 4000
int direction1;
boolean first;
unsigned long time1;
//----
void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
  Serial3.begin(115200);
  direction1 = 0;
  first=false;
  /* ----------------------------------------------------------- */
  /*  Initialise the PS4 */
#if !defined(MIPSEL)
  while (!Serial); // Wait for serial port to connect - used on Leonardo,
#endif             // Teensy and other boards with built-in USB CDC serial connection
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS4 USB Library Started"));
  /* ----------------------------------------------------------- */
  /* Initialise the Kangaroos */
  K1.start();
  K1.home().wait();
  K2.start();
  K2.home().wait();
  J1.start();
  J1.home().wait();
  J2.start();
  J2.home().wait();
  /* ----------------------------------------------------------- */
  /* Initialise the sensor */
//  if(!bno.begin())
//  {
//    /* There was a problem detecting the BNO055 ... check your connections */
//    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
//    while(1);
//  }
// bno.setExtCrystalUse(true);
  /* ----------------------------------------------------------- */
  //Serial.println("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");


  /* ----------------------------------------------------------- */
  
delay(3000);
}

void loop() {
  
 Serial.println(direction1);
// // euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
// sensors_event_t event;
//  bno.getEvent(&event);
  Serial.println(direction1);
  Serial.println(U1.Ranging(CM));
  Serial.println(U2.Ranging(CM));
  delay(1000);
  //K1.s(2000,1500);
//  vv
  if(direction1 == 0){
//    K1.s(v, kang_ramp);
//    K2.s(-v/5, kang_ramp);
//    J1.s(v, kang_ramp);
//    J2.s(-v/5, kang_ramp);
}

 if(direction1 == 1){
//    K1.s(v, kang_ramp);
//    K2.s(v, kang_ramp);
//    J1.s(v, kang_ramp);
//    J2.s(v, kang_ramp);
}
if(direction1 == 2){
//    K1.s(-v/5, kang_ramp);
//    K2.s(v, kang_ramp);
//    J1.s(-v/5, kang_ramp);
//    J2.s(v, kang_ramp);
}
if(direction1 == 3){
//    K1.s(v, kang_ramp);
//    K2.s(v, kang_ramp);
//    J1.s(v, kang_ramp);
//    J2.s(v, kang_ramp);
}
  if (U1.Ranging(CM) < 20)  {
    direction1 = 1;
  }
  if(U1.Ranging(CM) > 20){
    time1=millis();
  }
  if (millis() - time1 < 20000) {
    direction1 = 2;
  }
  if (U2.Ranging(CM) < 20) {
    direction1 = 1;
  }
//  if(U2.Ranging(CM) > 20){
//    time1=millis();
//  }
//  if (millis() - time1 < 20000) {
//    direction1 = 0;
//  }
 // if(U1.Ranging(CM) < 35 && U2.Ranging(CM) < 35)
//bb
//  if(event.orientation.x>2 && event.orientation.x<358){
//    if(event.orientation.x>0 && event.orientation.x < 5){
//        K1.s(-v, kang_ramp);
//        K2.s(v, kang_deramp);
//        J1.s(v, kang_ramp);
//        J2.s(-v, kang_deramp);
//    }else if(event.orientation.x>355 && event.orientation.x < 360){
//        K1.s(v, kang_ramp);
//        K2.s(-v, kang_deramp);
//        J1.s(-v, kang_ramp);
//        J2.s(v, kang_deramp);
//    }
//  }
//  else {
//  if (PS4.getButtonClick(PS)) {
//    Serial.print(F("\r\nPS"));
//    PS4.disconnect();
//  }
//  if (PS4.getButtonClick(CROSS)) {
//    K1.s(0, kang_ramp);
//    K2.s(0, kang_ramp);
//    J1.s(0, kang_ramp);
//    J2.s(0, kang_ramp);
//  }
//  if (PS4.getButtonClick(TRIANGLE)) {
//    /*
//      .
//      .
//      .
//    */
//  }
//  if (PS4.getButtonClick(CIRCLE)) {
//    /*
//      .
//      .
//      .
//    */
//  }
//  if (PS4.getButtonClick(SQUARE)) {
//    /*
//      .
//      .
//      .
//    */
//  }
//  if (PS4.getAnalogButton(R2) > 70 && PS4.getAnalogButton(L2) == 0) //ClockWise Rotation
//  {
//    PS4.setRumbleOn(PS4.getAnalogButton(L2), PS4.getAnalogButton(R2));
//    K1.s(-v, kang_ramp);
//    K2.s(v, kang_ramp);
//    J1.s(v, kang_ramp);
//    J2.s(-v, kang_ramp);
//  }
//  if (PS4.getAnalogButton(L2) > 70 && PS4.getAnalogButton(R2 ) == 0) //Anti-ClockWise Rotation
//  {
//    PS4.setRumbleOn(PS4.getAnalogButton(L2), PS4.getAnalogButton(R2));
//    K1.s(v, kang_ramp);
//    K2.s(-v, kang_ramp);
//    J1.s(-v, kang_ramp);
//    J2.s(v, kang_ramp);
//  }
//  if (PS4.getAnalogHat(LeftHatX) > 137 || PS4.getAnalogHat(LeftHatX) < 117 || PS4.getAnalogHat(LeftHatY) > 137 || PS4.getAnalogHat(LeftHatY) < 117) {
//    int  lhx = PS4.getAnalogHat(LeftHatX) - 133;
//    int  lhy = PS4.getAnalogHat(LeftHatY) - 127;
//    K1.s(v * ((lhy) + (1.5 * (lhx))), kang_ramp);
//    K2.s(v * ((lhy) - (1.5 * (lhx))), kang_ramp);
//    J1.s(v * ((lhy) + (1.5 * (lhx))), kang_ramp);
//    J2.s(v * ((lhy) - (1.5 * (lhx))), kang_ramp);
//  }
//
//  }
}