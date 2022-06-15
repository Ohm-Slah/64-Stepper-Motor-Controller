/*
 * File name: Serial_Shift_Register.h -> DRIVER
 * Project: 64 Motor Driver
 * Author: Elliot Eickholtz
 * Purpose: Create classes and functions for shift register usage.
 * 
*/

#ifndef SERIAL_SHIFT_REGISTER_H
#define SERIAL_SHIFT_REGISTER_H

#include <Pinout.h>

class ShiftRegisterControl
{
// Class to control the 4 serial lines per 32 motors to control.
    public:
        ShiftRegisterControl(uint8_t serialPin, uint8_t clockPin)
        {
            _serialPin = serialPin;
            _clockPin = clockPin;
        }

        void clear()
        {
            _buffer = 0;
            write();
        }

        void fillBuffer(uint64_t data)
        {
            _buffer = data;
        }

        uint64_t getBuffer()
        {
            return _buffer;
        }

        void write()
        {
            for(int i=0; i<5; i++)  shiftOut(_serialPin, _clockPin, LSBFIRST, _buffer>>(8*i));
        }

    private:
        uint64_t _buffer = 0;
        
        uint8_t _serialPin, _clockPin;
};

ShiftRegisterControl Shift1(SER1, SRCLK1);
ShiftRegisterControl Shift2(SER2, SRCLK2);
ShiftRegisterControl Shift3(SER3, SRCLK3);
ShiftRegisterControl Shift4(SER4, SRCLK4);

void initShiftRegisters()
{
    pinMode(SRCLR, OUTPUT); // reset pin
    pinMode(RCLK, OUTPUT);  // latch pin
    pinMode(OE, OUTPUT);    // output enable pin

    Shift1.clear();
    Shift2.clear();
    Shift3.clear();
    Shift4.clear();

    digitalWrite(SRCLR, HIGH);
    digitalWrite(RCLK, LOW);
    digitalWrite(OE, LOW);
}

void clearAllShiftRegisters()
{
    digitalWrite(SRCLR, LOW);
    delayMicroseconds(1);
    digitalWrite(SRCLR, HIGH);
}

void showAllSerial()
{
    digitalWrite(RCLK, HIGH);
    delayMicroseconds(1);
    digitalWrite(RCLK, LOW);
}

void disableSerialOutput()
{
    digitalWrite(OE, HIGH);
}

void enableSerialOutput()
{
    digitalWrite(OE, LOW);
}

#endif  // SERIAL_SHIFT_REGISTER_H