/*
 * File name: main.cpp -> DRIVER
 * Project: 64 Motor Driver
 * Author: Elliot Eickholtz
 * Purpose: Drive 64 stepper motors with 2 Teensy 4.0's, 32 motors each. Slave to Teensy 4.1 microcontroller.
 * 
*/

#include <Arduino.h>
#include <Stepper_Music.h>

Motor Motor1(A1STEP1, 1, 1, 1, 1);
Motor Motor2(A2STEP1, 1, 2, 1, 2);
Motor Motor3(A3STEP1, 1, 3, 1, 3);
Motor Motor4(A4STEP1, 1, 4, 1, 4);
Motor Motor5(A5STEP1, 1, 5, 1, 5);
Motor Motor6(A6STEP1, 1, 6, 1, 6);
Motor Motor7(A7STEP1, 1, 7, 1, 7);
Motor Motor8(A8STEP1, 1, 8, 1, 8);

Motor Motor9(A1STEP1, 1, 1, 1, 1);
Motor Motor10(A2STEP1, 1, 2, 1, 2);
Motor Motor11(A3STEP1, 1, 3, 1, 3);
Motor Motor12(A4STEP1, 1, 4, 1, 4);
Motor Motor13(A5STEP1, 1, 5, 1, 5);
Motor Motor14(A6STEP1, 1, 6, 1, 6);
Motor Motor15(A7STEP1, 1, 7, 1, 7);
Motor Motor16(A8STEP1, 1, 8, 1, 8);

Card Card1(Motor1, Motor2, Motor3, Motor4, Motor5, Motor6, Motor7, Motor8, 1);
Card Card2(Motor9, Motor10, Motor11, Motor12, Motor13, Motor14, Motor15, Motor16, 2);
Card Card3(Motor9, Motor10, Motor11, Motor12, Motor13, Motor14, Motor15, Motor16, 3);
Card Card4(Motor9, Motor10, Motor11, Motor12, Motor13, Motor14, Motor15, Motor16, 4);

ControlBoard Board(Card1, Card2, Card3, Card4, 1);

void setup() {
  Serial.begin(115200);

  Board.enableAllRegisters();
  Board.clearAllRegisters();
  Board.resetLatch();
  delay(500);
  
  Card1.writeRegister();
  Board.resetLatch();
}

void loop() {
  for(int i=1; i<6; i++)
  {
    Card1.changeMicroStep(1, i);
    Card1.enableMotor(1);
    Card1.writeRegister();
    Board.resetLatch();
    Motor1.testFunctionality(200*i, 2273);
    Serial.println("FULL");
    delayMicroseconds(1000);
    Card1.disableMotor(1);
    Board.resetLatch();
    delay(1000);
  }
  
  // Card1.fillBuffer(0);
  // Board.unlatchRegisters();
  // Card1.writeRegister();
  // Board.latchRegisters();
  // Motor1.testFunctionality(200, 2273);
  // Serial.println("FULL");
  // delayMicroseconds(1000);
  // Card1.fillBuffer(0b100);
  // Board.unlatchRegisters();
  // Card1.writeRegister();
  // Board.latchRegisters();
  // delay(1000);

  //  Card1.fillBuffer(0b10000);
  // Board.unlatchRegisters();
  // Card1.writeRegister();
  // Board.latchRegisters();
  // Motor1.testFunctionality(400, 1136);
  // Serial.println("1/2");
  // delayMicroseconds(1000);
  // Card1.fillBuffer(0b10100);
  // Board.unlatchRegisters();
  // Card1.writeRegister();
  // Board.latchRegisters();
  // delay(1000);

  //  Card1.fillBuffer(0b1000000);
  // Board.unlatchRegisters();
  // Card1.writeRegister();
  // Board.latchRegisters();
  // Motor1.testFunctionality(800, 568);
  // Serial.println("1/4");
  // delayMicroseconds(1000);
  // Card1.fillBuffer(0b1000100);
  // Board.unlatchRegisters();
  // Card1.writeRegister();
  // Board.latchRegisters();
  // delay(1000);

  //  Card1.fillBuffer(0b1010000);
  // Board.unlatchRegisters();
  // Card1.writeRegister();
  // Board.latchRegisters();
  // Motor1.testFunctionality(1600, 284);
  // Serial.println("1/8");
  // delayMicroseconds(1000);
  // Card1.fillBuffer(0b1010100);
  // Board.unlatchRegisters();
  // Card1.writeRegister();
  // Board.latchRegisters();
  // delay(1000);

  // Card1.fillBuffer(0b101010000);
  // Board.unlatchRegisters();
  // Card1.writeRegister();
  // Board.latchRegisters();
  // Motor1.testFunctionality(3200, 142);
  // Serial.println("1/64");
  // delayMicroseconds(1000);
  // Card1.fillBuffer(0b101010100);
  // Board.unlatchRegisters();
  // Card1.writeRegister();
  // Board.latchRegisters();
  // delay(1000);
}