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
#include <Pinout.h>

#define DEBUG 1

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
        Motor(uint8_t stepPin, uint8_t motorNumber)
        {
        // Constructor used for initialization of a single stepper motor
            _stepPin = stepPin;
            _motorNumber = motorNumber;

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
        uint8_t _stepPin,  _motorNumber;

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

#endif // STEPPER_MUSIC_H
