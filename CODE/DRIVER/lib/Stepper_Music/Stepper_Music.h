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
        uint16_t pulseWait;

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

        uint16_t getNewTimems()
        {

            if((_glissandoMoveTime != 0) && (micros() - _msLastFrequencyChange >= _msPerFrequency))
            {
                _moveTimems += 0;
            }

            return _moveTimems;
        }

        void singleStep()
        {
            // if(_motorNumber == 2)
            // {
            //     Serial.println(micros() - _previousDelayms);
            //     Serial.println(_moveTimems);
            //     Serial.println(_totalTimems);
            // }
            
            if((micros() - _previousDelayms >= _moveTimems) && (_totalTimems != 0))
            {
                Serial.println("STEP");
                _previousDelayms += getNewTimems();
                digitalWrite(_stepPin, HIGH);
                delayMicroseconds(1);
                digitalWrite(_stepPin, LOW);
            }
        }

        void motorMove(uint8_t state, uint16_t startFreq, uint16_t endFreq, uint16_t timems, uint8_t sustain)
        {
            if(!state) 
            {
                _totalTimems = 0;
            } else {
                _totalTimems = 1;
                _msPerFrequency = timems / abs(startFreq-endFreq);
                _totalMovePulses = startFreq * timems;
                pulseWait = (uint16_t) (1.0/startFreq * 1000000);
                _moveTimems = pulseWait;
                _previousDelayms = micros();
            }
            Serial.print("\nmotorNum : ");Serial.println(_motorNumber);
            Serial.print("pulseWait : ");Serial.println(pulseWait);
            Serial.print("state : ");Serial.println(state);
            Serial.print("_moveTimems : ");Serial.println(_moveTimems);
            Serial.print("_totalTimems : ");Serial.println(_totalTimems);
        }

    private:
        uint8_t _stepPin, _motorNumber;
        uint16_t _glissandoMoveTime;
        uint16_t _moveTimems, _msPerFrequency;
        uint32_t _msLastFrequencyChange;
        uint16_t _totalTimems;
        uint16_t _currentTimems;
        uint32_t _totalMovePulses;
        uint16_t _previousDelayms;
};

#endif // STEPPER_MUSIC_H
