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

}

void loop()
{
    BoardTwo.Cards[0].enableMotor(2);

    BoardTwo.Cards[0].writeRegister();
    BoardTwo.resetLatch();
    delay(1000);

    BoardTwo.Cards[0].disableMotor(2);

    BoardTwo.Cards[0].writeRegister();
    BoardTwo.resetLatch();
    delay(1000);
}