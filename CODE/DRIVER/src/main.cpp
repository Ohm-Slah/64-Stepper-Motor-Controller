/*
 * File name: main.cpp -> DRIVER
 * Project: 64 Motor Driver
 * Author: Elliot Eickholtz
 * Purpose: Drive 64 stepper motors with 2 Teensy 4.0's, 32 motors each. Slave to Teensy 4.1 microcontroller.
 * 
*/

#include <Arduino.h>
#include <Stepper_Music.h>

#define STEP 22

Motor singleMotor(STEP, 1, 1, 1, 1);

void setup() {
  Serial.begin(115200);
}

void loop() {
  singleMotor.testFunctionality(200, 10);
  Serial.println("DONE");
  delay(2500);
}