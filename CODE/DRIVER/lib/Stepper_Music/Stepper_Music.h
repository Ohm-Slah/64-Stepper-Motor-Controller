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
        uint16_t pulseWait[4];

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

        uint16_t getNewTimems(uint8_t motorNumber)
        {
            // if((_glissandoMoveTime != 0) && (micros() - _msLastFrequencyChange >= _msPerFrequency[motorNumber]))
            // {
            //     _moveTimems[motorNumber] += 0;
            // }
            return _moveTimems[motorNumber];
        }

        void singleStep()
        {
            for(int i=0; i<4; i++)
            {
                if(pulseWait[i] == 0) continue;

                if((micros() - _previousDelayms[i] >= _moveTimems[i]) && (_totalTimems[4] != 0))
                {
                    _previousDelayms[i] += getNewTimems(i);
                    pulse();
                }
            }
        }

        void motorMove(uint8_t state, uint16_t startFreq, uint16_t endFreq, uint8_t noteNumber, uint16_t timems, uint8_t sustain)
        {   
            if(!state) 
            {
                _totalTimems[noteNumber] = 0;
            } else {
                if(noteNumber >= 4) 
                {
                    !DEBUG ? true : Serial.print("\nMotor ");
                    !DEBUG ? true : Serial.print(_motorNumber);
                    !DEBUG ? true : Serial.println(" noteNumber above allowed number of notes, ignoring.");
                }

                _totalTimems[noteNumber] = 1;
                _msPerFrequency[noteNumber] = timems / abs(startFreq-endFreq);
                _totalMovePulses[noteNumber] = startFreq * timems;
                pulseWait[noteNumber] = (uint16_t) (1.0/startFreq * 1000000);
                _moveTimems[noteNumber] = pulseWait[noteNumber];
                _previousDelayms[noteNumber] = micros();
            }
            !DEBUG ? true : Serial.print("\nmotorNum : ");!DEBUG ? true : Serial.println(_motorNumber);
            !DEBUG ? true : Serial.print("pulseWait : ");!DEBUG ? true : Serial.println(pulseWait[noteNumber]);
            !DEBUG ? true : Serial.print("state : ");!DEBUG ? true : Serial.println(state);
            !DEBUG ? true : Serial.print("micros : ");!DEBUG ? true : Serial.println(micros());
            !DEBUG ? true : Serial.print("_previousDelayms : ");!DEBUG ? true : Serial.println(_previousDelayms[noteNumber]);
            !DEBUG ? true : Serial.print("_moveTimems : ");!DEBUG ? true : Serial.println(_moveTimems[noteNumber]);
            !DEBUG ? true : Serial.print("_totalTimems : ");!DEBUG ? true : Serial.println(_totalTimems[noteNumber]);
            !DEBUG ? true : Serial.print("First conditional : ");!DEBUG ? true : Serial.println(micros() - _previousDelayms[noteNumber] >= _moveTimems[noteNumber]);
            !DEBUG ? true : Serial.print("Second conditional : ");!DEBUG ? true : Serial.println(_totalTimems[noteNumber] != 0);
        }

    private:
        uint8_t _stepPin, _motorNumber;
        uint16_t _glissandoMoveTime;
        uint16_t _moveTimems[4], _msPerFrequency[4];
        uint32_t _msLastFrequencyChange;
        uint16_t _totalTimems[4];
        uint16_t _currentTimems;
        uint32_t _totalMovePulses[4];
        uint64_t _previousDelayms[4];
};

#endif // STEPPER_MUSIC_H
