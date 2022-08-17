/*
 * File name: main.cpp -> CONTROLLER
 * Project: 64 Motor Driver
 * Author: Elliot Eickholtz
 * Purpose: Master controller to 2 slave Teensy 4.0's, 40 shift registers, and LED lighting. 
 * Custom com protocal used for communication over USB and serial busses.
 * 
*/

#include <Arduino.h>
#include "Music_Serial.h"
#include "Shift_Control.h"

ControlBoard BoardTwo(2);

void setup()
{
    Serial.begin(115200);

    BoardTwo.Driver.serialInit();

    // BoardTwo.getInfo();
    // BoardTwo.Cards[0].getInfo();
    BoardTwo.Cards[0].enableMotor(2);
    BoardTwo.Cards[0].writeRegister();
    BoardTwo.resetLatch();
}

void loop()
{
    BoardTwo.Cards[0].changeMicroStep(2, 1);
    BoardTwo.Cards[0].writeRegister();
    BoardTwo.resetLatch();
    BoardTwo.Driver.sendSingleMotor(2, 1, 200);
    delay(500);
    BoardTwo.Driver.sendSingleMotor(2, 0, 0);
    delay(500);
    BoardTwo.Cards[0].changeMicroStep(2, 2);
    BoardTwo.Cards[0].writeRegister();
    BoardTwo.resetLatch();
    BoardTwo.Driver.sendSingleMotor(2, 1, 400);
    delay(500);
    BoardTwo.Driver.sendSingleMotor(2, 0, 0);
    delay(500);
    BoardTwo.Cards[0].changeMicroStep(2, 3);
    BoardTwo.Cards[0].writeRegister();
    BoardTwo.resetLatch();
    BoardTwo.Driver.sendSingleMotor(2, 1, 800);
    delay(500);
    BoardTwo.Driver.sendSingleMotor(2, 0, 0);
    delay(500);
    BoardTwo.Cards[0].changeMicroStep(2, 4);
    BoardTwo.Cards[0].writeRegister();
    BoardTwo.resetLatch();
    BoardTwo.Driver.sendSingleMotor(2, 1, 1600);
    delay(500);
    BoardTwo.Driver.sendSingleMotor(2, 0, 0);
    delay(500);
    BoardTwo.Cards[0].changeMicroStep(2, 5);
    BoardTwo.Cards[0].writeRegister();
    BoardTwo.resetLatch();
    BoardTwo.Driver.sendSingleMotor(2, 1, 3200);
    delay(500);
    BoardTwo.Driver.sendSingleMotor(2, 0, 0);
    delay(500);
    // BoardTwo.Cards[0].enableMotor(2);

    // BoardTwo.Cards[0].writeRegister();
    // BoardTwo.resetLatch();
    // delay(1000);

    // BoardTwo.Cards[0].disableMotor(2);

    // BoardTwo.Cards[0].writeRegister();
    // BoardTwo.resetLatch();
    // delay(1000);
}