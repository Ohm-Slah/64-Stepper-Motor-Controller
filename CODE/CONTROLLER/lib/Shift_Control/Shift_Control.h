/*
 * File name: Shift_Control.h -> CONTROLLER
 * Project: 64 Motor Driver
 * Author: Elliot Eickholtz
 * Purpose: Shift register control library.
 * 
*/

#include "Pinout.h"

#define DEBUG 1

class Card
{
    private:
        uint8_t _serialPin;
        uint8_t _clockPin;
        uint8_t _cardNumber;
        uint64_t _buffer = 0;

        void _fillBuffer(uint64_t buf)
        {
            _buffer = buf;
        }

    public:
        Card(uint8_t cardNumber) : 
            _cardNumber(cardNumber)
        {
        // Constructor for a single card containing 8 motors. All shift register work is done here.
            if(cardNumber > 4 || !cardNumber) 
            {
                !!DEBUG ? true : Serial.println("The Card Number entered for the Instantiation of Card class is out of range.");
                return;
            }

            switch (cardNumber)
            {
                case 1:
                    _serialPin = SER1;
                    _clockPin = SRCLK1;
                break;
                case 2:
                    _serialPin = SER2;
                    _clockPin = SRCLK2;
                break;
                case 3:
                    _serialPin = SER3;
                    _clockPin = SRCLK3;
                break;
                case 4:
                    _serialPin = SER4;
                    _clockPin = SRCLK4;
                break;
            }

            pinMode(_serialPin, OUTPUT);
            pinMode(_clockPin, OUTPUT);

        }

        void fillBuffer(uint64_t buf)
        {
            _buffer = buf;
            !DEBUG ? true : Serial.print("Filling Buffer with: ");
            !DEBUG ? true : Serial.println(buf);
            !DEBUG ? true : Serial.print("Buffer is now: ");
            !DEBUG ? true : Serial.println(_buffer);
        }

        void clearBuffer()
        {
            _buffer = 0;
            !DEBUG ? true : Serial.print("Buffer is now: ");
            !DEBUG ? true : Serial.println(_buffer);
        }

        uint64_t getBuffer()
        {
            return _buffer;
        }

        void writeRegister()
        {
        // Push buffer data out to shift registers. Will not show until latch is reset.
            for(int i=0; i<5; i++)  shiftOut(_serialPin, _clockPin, MSBFIRST, _buffer>>(8*i)&0xFF);
            !DEBUG ? true : Serial.print("Register wirtten with: ");
            !DEBUG ? true : Serial.println(_buffer);
        }

        void enableMotor(uint8_t motorNum)
        {
            _buffer &= ~(uint64_t)(1 << (enablePins[motorNum-1]-1));
            !DEBUG ? true : Serial.print("MotorNum: ");
            !DEBUG ? true : Serial.println(motorNum);
            !DEBUG ? true : Serial.print("EnablePin: ");
            !DEBUG ? true : Serial.println(enablePins[motorNum-1]-1);
            !DEBUG ? true : Serial.print("Enable: "); 
            !DEBUG ? true : Serial.print((uint64_t)(1 << (enablePins[motorNum-1]-1)));
            !DEBUG ? true : Serial.print("\t");
            !DEBUG ? true : Serial.println(_buffer, BIN);
        }

        void disableMotor(uint8_t motorNum)
        {
            _buffer |= ((uint64_t)1 << (enablePins[motorNum-1]-1));
            !DEBUG ? true : Serial.print("disable: "); 
            !DEBUG ? true : Serial.print(((uint64_t)1 << (enablePins[motorNum-1]-1)));
            !DEBUG ? true : Serial.print("\t\t");
            !DEBUG ? true : Serial.println(_buffer, BIN);
        }

        void disableAllMotors()
        {
            for(int i=1; i<9; i++)
            {
                disableMotor(i);
            }
        }

        void changeDirection(uint8_t motorNum, bool direction)
        {
            if (direction)
            {
                _buffer &= ~(1 << (directionPins[motorNum-1]-1));
            } else
            {
                _buffer |= (1 << (directionPins[motorNum-1]-1));
            }
        }

        void changeMicroStep(uint8_t motorNum, uint8_t microStep)
        {
            switch (microStep)
            {
                case 1:
                    _buffer &= ~(uint64_t)((1 << (MS1Pins[motorNum-1]-1)) | (1 << (MS2Pins[motorNum-1]-1)) | (1 << (MS3Pins[motorNum-1]-1)));
                break;
                case 2:
                    _buffer &= ~(uint64_t)((1 << (MS2Pins[motorNum-1]-1)) | (1 <<(MS3Pins[motorNum-1]-1)));
                    _buffer |= (1 << (MS1Pins[motorNum-1]-1));
                break;
                case 3:
                    _buffer &= ~(uint64_t)((1 << (MS1Pins[motorNum-1]-1)) | (1 << (MS3Pins[motorNum-1]-1)));
                    _buffer |= (1 << (MS2Pins[motorNum-1]-1));
                break;
                case 4:
                    _buffer &= ~(uint64_t)(1 << (MS3Pins[motorNum]-1));
                    _buffer |= ((1 << (MS1Pins[motorNum-1]-1)) | (1 << (MS2Pins[motorNum-1]-1)));
                break;
                case 5:
                    _buffer |= ((1 << (MS1Pins[motorNum-1]-1)) | (1 << (MS2Pins[motorNum-1]-1)) | (1 << (MS3Pins[motorNum-1]-1)));
                break;
            }
        }

};

class ControlBoard
{
    private:
        uint8_t _controlBoardNumber;
        Music_Serial _Driver();

    public:
        ControlBoard(uint8_t controlBoardNumber) :
            _controlBoardNumber(controlBoardNumber)
        {
            pinMode(SRCLR, OUTPUT); // reset pin
            pinMode(RCLK, OUTPUT);  // latch pin
            pinMode(OE, OUTPUT);    // output enable pin

        }

        void enableAllRegisters()
        {
            digitalWrite(OE, LOW);
            !DEBUG ? true : Serial.println("Register Enabled");
        }

        void disableAllRegisters()
        {
            digitalWrite(OE, HIGH);
            !DEBUG ? true : Serial.println("Register Disabled");
        }

        void clearAllRegisters()
        {
            digitalWrite(SRCLR, LOW);
            delayMicroseconds(1);
            digitalWrite(SRCLR, HIGH);

            !DEBUG ? true : Serial.println("Register cleared");
        }

        void latchRegisters()
        {
            digitalWrite(RCLK, HIGH);
            !DEBUG ? true : Serial.println("Register latched");
        }

        void unlatchRegisters()
        {
            digitalWrite(RCLK, LOW);
            !DEBUG ? true : Serial.println("Register unlatched");
        }

        void resetLatch()
        {
            unlatchRegisters();
            latchRegisters();
            !DEBUG ? true : Serial.println("Register Reset");
        }
};