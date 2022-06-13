/*
 * File name: main.cpp -> DRIVER
 * Project: 64 Motor Driver
 * Author: Elliot Eickholtz
 * Purpose: Drive 64 stepper motors with 2 Teensy 4.0's, 32 motors each. Slave to Teensy 4.1 microcontroller.
 * 
*/

#include <Arduino.h>

//------------ Initialize all stepper driver freq pins to a unique identifier----------//
#define A1STEP1 -1 // Temporary placeholder
#define A2STEP1 -1 // Temporary placeholder
#define A3STEP1 -1 // Temporary placeholder
#define A4STEP1 -1 // Temporary placeholder
#define A5STEP1 -1 // Temporary placeholder
#define A6STEP1 -1 // Temporary placeholder
#define A7STEP1 -1 // Temporary placeholder
#define A8STEP1 -1 // Temporary placeholder
#define A1STEP2 -1 // Temporary placeholder
#define A2STEP2 -1 // Temporary placeholder
#define A3STEP2 -1 // Temporary placeholder
#define A4STEP2 -1 // Temporary placeholder
#define A5STEP2 -1 // Temporary placeholder
#define A6STEP2 -1 // Temporary placeholder
#define A7STEP2 -1 // Temporary placeholder
#define A8STEP2 -1 // Temporary placeholder
#define A1STEP3 -1 // Temporary placeholder
#define A2STEP3 -1 // Temporary placeholder
#define A3STEP3 -1 // Temporary placeholder
#define A4STEP3 -1 // Temporary placeholder
#define A5STEP3 -1 // Temporary placeholder
#define A6STEP3 -1 // Temporary placeholder
#define A7STEP3 -1 // Temporary placeholder
#define A8STEP3 -1 // Temporary placeholder
#define A1STEP4 -1 // Temporary placeholder
#define A2STEP4 -1 // Temporary placeholder
#define A3STEP4 -1 // Temporary placeholder
#define A4STEP4 -1 // Temporary placeholder
#define A5STEP4 -1 // Temporary placeholder
#define A6STEP4 -1 // Temporary placeholder
#define A7STEP4 -1 // Temporary placeholder
#define A8STEP4 -1 // Temporary placeholder

#define SER1 -1 // Temporary placeholder
#define SER2 -1 // Temporary placeholder
#define SER3 -1 // Temporary placeholder
#define SER4 -1 // Temporary placeholder

#define SRCLK1 -1 // Temporary placeholder
#define SRCLK2 -1 // Temporary placeholder
#define SRCLK3 -1 // Temporary placeholder
#define SRCLK4 -1 // Temporary placeholder
#define SRCLR1 -1 // Temporary placeholder
#define SRCLR2 -1 // Temporary placeholder
#define OE -1 // Temporary placeholder

#define VCCVOLTAGEREADPIN -1 // Temporary placeholder
#define FIVEVOLTAGEREADPIN -1 // Temporary placeholder

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^//

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

void setup() {
  Serial.begin(115200);
  for(int i=0; i<32; i++) pinMode(i, OUTPUT);
}

void loop() {
  
}