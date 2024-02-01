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
    !DEBUG ? true : Serial.print("channel On: ");Serial.println(channel);
    Control.midiEvent(channel, note, velocity, usbMIDI.getCable());
}

void OnNoteOn(byte channel, byte note, byte velocity)
{
    !DEBUG ? true : Serial.print("channel Off: ");Serial.println(channel);
    Control.midiEvent(channel, note, velocity, usbMIDI.getCable());
}

void OnControlChange(byte channel, byte number, byte value)
{
    Serial.println("--Control change--");
    Serial.print("Channel: ");Serial.println(channel);
    Serial.print("Number: ");Serial.println(number);
    Serial.print("Value: ");Serial.println(value);
    Control.controlEvent(channel, number, value);
}

void setup()
{
    Serial.begin(115200);

    usbMIDI.setHandleNoteOff(OnNoteOff);
    usbMIDI.setHandleNoteOn(OnNoteOn);
    usbMIDI.setHandleControlChange(OnControlChange);

    leds.begin();
    leds.show();
    delay(3000);
}

void loop()
{
    usbMIDI.read();
    // Control.midiEvent(1, 36, 100);
    // delay(500);
    // Control.midiEvent(1, 48, 100);
    // delay(500);
    // Control.midiEvent(1, 60, 100);
    // delay(500);
    // Control.midiEvent(1, 36, 0);
    // delay(500);
    // Control.midiEvent(1, 48, 0);
    // delay(500);
    // Control.midiEvent(1, 60, 0);
    // delay(500);
}