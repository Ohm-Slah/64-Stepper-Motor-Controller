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
  // Motor(uint8_t stepPin, uint8_t cardNumber, uint8_t motorNumber, uint8_t xGridPositionTopLeftOrigin, uint8_t yGridPositionTopLeftOrigin)
  Motor Motor1(A1STEP1, 1, 1, 1, 1);
  Motor Motor2(A2STEP1, 1, 2, 1, 2);
  Motor Motor3(A3STEP1, 1, 3, 1, 3);
  Motor Motor4(A4STEP1, 1, 4, 1, 4);
  Motor Motor5(A5STEP1, 1, 5, 1, 5);
  Motor Motor6(A6STEP1, 1, 6, 1, 6);
  Motor Motor7(A7STEP1, 1, 7, 1, 7);
  Motor Motor8(A8STEP1, 1, 8, 1, 8);

  Card Card1(Motor1, Motor2, Motor3, Motor4, Motor5, Motor6, Motor7, Motor8, 1);
  //Card Card2();
  //Card Card3();
  //Card Card4();
}

void loop() {
  singleMotor.testFunctionality(200, 10);
  Serial.println("DONE");
  delay(2500);
}