/*
 * File name: main.cpp -> CONTROLLER
 * Project: 64 Motor Driver
 * Author: Elliot Eickholtz
 * Purpose: Master controller to 2 slave Teensy 4.0's, 40 shift registers, and LED lighting. 
 * Custom com protocol used for communication over USB and serial busses.
 * 
*/

#include <Arduino.h>
#include "Music_Serial.h"
#include "Shift_Control.h"
#include "Light_Control.h"

MainControl Control(1);


void OnNoteOff(byte channel, byte note, byte velocity)
{
    Serial.print("channel On: ");Serial.println(channel);
    Control.midiEvent(channel, note, velocity);
}

void OnNoteOn(byte channel, byte note, byte velocity)
{
    Serial.print("channel Off: ");Serial.println(channel);
    Control.midiEvent(channel, note, velocity);
}

void setup()
{
    Serial.begin(115200);

    // BoardOne.Driver.serialInit();
    // BoardTwo.Driver.serialInit();

    usbMIDI.setHandleNoteOff(OnNoteOff);
    usbMIDI.setHandleNoteOn(OnNoteOn);

    leds.begin();
    leds.show();
    delay(3000);
}

void loop()
{
    usbMIDI.read();

    Control.handler();
    // Control.midiEvent(1, 53, 127);
    // delay(500);
    // Control.midiEvent(1, 53, 0);
    // delay(500);
    // Control.midiEvent(1, 52, 127);
    // delay(500);
    // Control.midiEvent(1, 52, 0);
    // delay(500);
    // Control.midiEvent(1, 51, 127);
    // delay(500);
    // Control.midiEvent(1, 51, 0);
    // delay(500);
}