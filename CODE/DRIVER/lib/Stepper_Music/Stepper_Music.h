/*
 * File name: Stepper_Music.h -> DRIVER
 * Project: 64 Motor Driver
 * Author: Elliot Eickholtz
 * Purpose: Create classes and functions for individual motor control.
 * 
*/

#ifndef STEPPER_MUSIC_H
#define STEPPER_MUSIC_H

#include <pitches.h>
#include <DAQ.h>
#include <Serial_Shift_Register.h>
#include <Pinout.h>

//  *Constants for calculation and balancing. Do not touch unless you know what you're doing.*    //
//  *----------------------------------------------------------------------------------------*    //
// ? Do velocity, acceleration, and jerk calculations? Hard code accel steps instead?
// TODO Try dynamic linear accel and a 'fake smoothed' accel
#define MAXMOTORSPEEDRPS 0
#define MAXMOTORACCRPS2 0
#define MAXMOTORJERKRPS3 0

//  *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*    //

#define ON 1
#define OFF 0

int8_t pinArray[] = {
  A1STEP1, A2STEP1, A3STEP1, A4STEP1, A5STEP1, A6STEP1, A7STEP1, A8STEP1, 
  A1STEP2, A2STEP2, A3STEP2, A4STEP2, A5STEP2, A6STEP2, A7STEP2, A8STEP2, 
  A1STEP3, A2STEP3, A3STEP3, A4STEP3, A5STEP3, A6STEP3, A7STEP3, A8STEP3, 
  A1STEP4, A2STEP4, A3STEP4, A4STEP4, A5STEP4, A6STEP4, A7STEP4, A8STEP4
};

class Motor
{
// Class to create individual motor objects to control. All things stepping is controlled here.
    public:
        Motor(uint8_t stepPin, uint8_t cardNumber, uint8_t motorNumber, uint8_t xGridPositionTopLeftOrigin, uint8_t yGridPositionTopLeftOrigin)
        {
        // Constructor used for initialization of a single stepper motor
            _stepPin = stepPin;
            _cardNumber = cardNumber;
            _motorNumber = motorNumber;
            _xGridPositionTopLeftOrigin = xGridPositionTopLeftOrigin;
            _yGridPositionTopLeftOrigin = yGridPositionTopLeftOrigin;
            _shiftRegisterNumber = _cardNumber;
            _enablePin = enablePins[_motorNumber];
            _ms1Pin = MS1Pins[_motorNumber];
            _ms2Pin = MS2Pins[_motorNumber];
            _ms3Pin = MS3Pins[_motorNumber];

            pinMode(_stepPin, OUTPUT);
            digitalWrite(_stepPin, LOW);
        }

        void pulse()
        {
            digitalWrite(_stepPin, HIGH);
            delayMicroseconds(1);
            digitalWrite(_stepPin, LOW);
        }

        void testFunctionality(uint32_t pulses, uint16_t delayus)
        {
            for(; pulses;  pulses--)
            {
                pulse();
                delayMicroseconds(delayus);
            }
        }

    private:
        uint8_t _stepPin, _cardNumber, _motorNumber, _xGridPositionTopLeftOrigin, _yGridPositionTopLeftOrigin, _shiftRegisterNumber;
        uint8_t _enablePin, _ms1Pin, _ms2Pin, _ms3Pin, _directionPin;

        void _generate_Acceleration_Points()
        {

        }

        void _acceleration_Applied()
        {

        }

        uint32_t _get_Next_Time_Delay()
        {
            // TODO import pitches.h file of musical note to frequency.
            // TODO Find if acceleration curve geration is necessary/already-created
            // TODO Gernerate acceleration curve if necessary
            // TODO Find if note has pitch shift applied, account for this.
            // TODO Get delay time of motor for given pulse over the frame of a single note
            // TODO Return time in uS for delay at that given time
            return 0;
        }

        uint32_t _get_Delay_Time()
        {
            return 0;
        }

        void _changeMotorState(bool desiredState)
        {
            // Enable/disable the motor
        }

        void _changeMotorDirection(bool desiredState)
        {
            // CW/CCW rotation of the motor
        }
};

class Card
{
    private:
        Motor _Motors[8];
        uint8_t _serialPin;
        uint8_t _clockPin;
        uint8_t _cardNumber;
        uint64_t _buffer = 0;

    public:
        Card(Motor MotorOne, Motor MotorTwo, Motor MotorThree, Motor MotorFour, 
            Motor MotorFive, Motor MotorSix, Motor MotorSeven, Motor MotorEight, uint8_t cardNumber) : 
            _cardNumber(cardNumber),
            _Motors{{MotorOne}, {MotorTwo}, {MotorThree}, {MotorFour}, {MotorFive}, {MotorSix}, {MotorSeven}, {MotorEight}}
        {
        // Constructor for a single card containing 8 motors. All shift register work is done here.
            if(cardNumber > 4 || !cardNumber) 
            {
                Serial.println("The Card Number entered for the Instantiation of Card class is out of range.");
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
        }

        void clearBuffer()
        {
            _buffer = 0;
        }

        uint64_t getBuffer()
        {
            return _buffer;
        }

        void writeRegister()
        {
        // Push buffer data out to shift registers. Will not show until latch is reset.
            for(int i=0; i<5; i++)  shiftOut(_serialPin, _clockPin, MSBFIRST, _buffer>>(8*i)&0xFF);
        }

};

class ControlBoard
{
    private:
        Card _Cards[4];
        uint8_t _controlBoardNumber;

    public:
        ControlBoard(Card Card1, Card Card2, Card Card3, Card Card4, uint8_t controlBoardNumber) :
            _controlBoardNumber(controlBoardNumber),
            _Cards{{Card1}, {Card2}, {Card3}, {Card4}}
        {
            pinMode(SRCLR, OUTPUT); // reset pin
            pinMode(RCLK, OUTPUT);  // latch pin
            pinMode(OE, OUTPUT);    // output enable pin
        }

        void enableAllRegisters()
        {
            digitalWrite(OE, LOW);
        }

        void disableAllRegisters()
        {
        // Unlatch shift registers, will display what data has been shifted out.
            digitalWrite(OE, HIGH);
        }

        void clearAllRegisters()
        {
            digitalWrite(SRCLR, LOW);
            delayMicroseconds(1);
            digitalWrite(SRCLR, HIGH);
        }

        void latchRegisters()
        {
            digitalWrite(RCLK, HIGH);
        }

        void unlatchRegisters()
        {
            digitalWrite(RCLK, LOW);
        }
};

#endif // STEPPER_MUSIC_H
