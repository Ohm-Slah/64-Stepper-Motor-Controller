/*
 * File name: main.cpp -> DRIVER
 * Project: 64 Motor Driver
 * Author: Elliot Eickholtz
 * Purpose: Drive 64 stepper motors with 2 Teensy 4.0's, 32 motors each. Slave to Teensy 4.1 microcontroller.
 * 
*/

#include <Arduino.h>
#include <Stepper_Music.h>
#include <Music_Serial.h>

Motor Motor1(A1STEP1, 1);
Motor Motor2(A2STEP1, 1);
Motor Motor3(A3STEP1, 1);
Motor Motor4(A4STEP1, 1);
Motor Motor5(A5STEP1, 1);
Motor Motor6(A6STEP1, 1);
Motor Motor7(A7STEP1, 1);
Motor Motor8(A8STEP1, 1);

Motor Motor9(A1STEP1, 1);
Motor Motor10(A2STEP1, 1);
Motor Motor11(A3STEP1, 1);
Motor Motor12(A4STEP1, 1);
Motor Motor13(A5STEP1, 1);
Motor Motor14(A6STEP1, 1);
Motor Motor15(A7STEP1, 1);
Motor Motor16(A8STEP1, 1);

void setup() {
  Serial.begin(115200);

}

void loop() {

}