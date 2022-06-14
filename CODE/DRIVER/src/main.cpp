/*
 * File name: main.cpp -> DRIVER
 * Project: 64 Motor Driver
 * Author: Elliot Eickholtz
 * Purpose: Drive 64 stepper motors with 2 Teensy 4.0's, 32 motors each. Slave to Teensy 4.1 microcontroller.
 * 
*/

#include <Arduino.h>
#include <Stepper_Music.h>

//-----------------------Create quick-read info definitions----------------------------//
// Give analog Reading Converted to voltage
#define VCCVOLTAGE map(analogRead(VCCVOLTAGEREADPIN), 1, 1023, 1, 1023)
#define FIVEVOLTAGE map(analogRead(FIVEVOLTAGEREADPIN), 1, 1023, 1, 1023)

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^//


int8_t pinArray[] = {
  A1STEP1, A2STEP1, A3STEP1, A4STEP1, A5STEP1, A6STEP1, A7STEP1, A8STEP1, 
  A1STEP2, A2STEP2, A3STEP2, A4STEP2, A5STEP2, A6STEP2, A7STEP2, A8STEP2, 
  A1STEP3, A2STEP3, A3STEP3, A4STEP3, A5STEP3, A6STEP3, A7STEP3, A8STEP3, 
  A1STEP4, A2STEP4, A3STEP4, A4STEP4, A5STEP4, A6STEP4, A7STEP4, A8STEP4
};

#define DIR 23
#define STEP 22


void setup() {
  Serial.begin(115200);
  //for(int i=0; i<32; i++) pinMode(i, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(STEP, OUTPUT);
  digitalWrite(DIR, LOW);
  digitalWrite(STEP, LOW);
}

void loop() {
  for(int i=0; i<200; i++) 
  {
    digitalWrite(STEP, HIGH);
    delayMicroseconds(1);
    digitalWrite(STEP, LOW);
    delay(10);
  }
  Serial.println("DONE");
  delay(2500);
}