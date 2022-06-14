/*
 * File name: Stepper_Music.h -> DRIVER
 * Project: 64 Motor Driver
 * Author: Elliot Eickholtz
 * Purpose: Create classes and functions for individual motor control.
 * 
*/

#ifndef STEPPER_MUSIC_H
#define STEPPER_MUSIC_H

//  *Initialize all stepper driver freq pins to a unique identifier*  //
//  *--------------------------------------------------------------*  //
#define A1STEP1 -1 // Temporary placeholder
#define A2STEP1 -1 // Temporary placeholder
#define A3STEP1 -1 // Temporary placeholder
#define A4STEP1 -1 // Temporary placeholder
#define A5STEP1 -1 // Temporary placeholder
#define A6STEP1 -1 // Temporary placeholder
#define A7STEP1 -1 // Temporary placeholder
#define A8STEP1 -1 // Temporary placeholder
#define A1STEP2 -1 // Temporary placeholder
#define A2STEP2 -1 // Temporary placeholder
#define A3STEP2 -1 // Temporary placeholder
#define A4STEP2 -1 // Temporary placeholder
#define A5STEP2 -1 // Temporary placeholder
#define A6STEP2 -1 // Temporary placeholder
#define A7STEP2 -1 // Temporary placeholder
#define A8STEP2 -1 // Temporary placeholder
#define A1STEP3 -1 // Temporary placeholder
#define A2STEP3 -1 // Temporary placeholder
#define A3STEP3 -1 // Temporary placeholder
#define A4STEP3 -1 // Temporary placeholder
#define A5STEP3 -1 // Temporary placeholder
#define A6STEP3 -1 // Temporary placeholder
#define A7STEP3 -1 // Temporary placeholder
#define A8STEP3 -1 // Temporary placeholder
#define A1STEP4 -1 // Temporary placeholder
#define A2STEP4 -1 // Temporary placeholder
#define A3STEP4 -1 // Temporary placeholder
#define A4STEP4 -1 // Temporary placeholder
#define A5STEP4 -1 // Temporary placeholder
#define A6STEP4 -1 // Temporary placeholder
#define A7STEP4 -1 // Temporary placeholder
#define A8STEP4 -1 // Temporary placeholder

#define SER1 -1 // Temporary placeholder
#define SER2 -1 // Temporary placeholder
#define SER3 -1 // Temporary placeholder
#define SER4 -1 // Temporary placeholder

#define SRCLK1 -1 // Temporary placeholder
#define SRCLK2 -1 // Temporary placeholder
#define SRCLK3 -1 // Temporary placeholder
#define SRCLK4 -1 // Temporary placeholder
#define SRCLR1 -1 // Temporary placeholder
#define SRCLR2 -1 // Temporary placeholder
#define OE -1 // Temporary placeholder

#define VCCVOLTAGEREADPIN -1 // Temporary placeholder
#define FIVEVOLTAGEREADPIN -1 // Temporary placeholder

//  *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*  //


//  *Constants for calculation and balancing. Do not touch unless you know what you're doing.*    //
//  *----------------------------------------------------------------------------------------*    //

#define MAXMOTORSPEEDRPS 0
#define MAXMOTORACCRPS2 0
#define MAXMOTORJERKRPS3 0

//  *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*    //

class Motor
{
    public:
        Motor(uint8_t stepPin, uint8_t cardNumber, uint8_t motorNumber, uint8_t xGridPositionTopLeftOrigin, uint8_t yGridPositionTopLeftOrigin)
        {
            _stepPin = stepPin;
            _cardNumber = cardNumber;
            _motorNumber = motorNumber;
            _xGridPositionTopLeftOrigin = xGridPositionTopLeftOrigin;
            _yGridPositionTopLeftOrigin = yGridPositionTopLeftOrigin;

            pinMode(_stepPin, OUTPUT);
        }

        void pulse()
        {
            digitalWrite(_stepPin, HIGH);
            delayMicroseconds(1);
            digitalWrite(_stepPin, LOW);
        }

    private:

        uint8_t _stepPin, _cardNumber, _motorNumber, _xGridPositionTopLeftOrigin, _yGridPositionTopLeftOrigin;

        void _generate_Acceleration_Points()
        {

        }

        void _acceleration_Applied()
        {

        }

        uint32_t _get_Next_Time_Delay()
        {
            // import pitches.h file of musical note to frequency.
            // Find if acceleration curve geration is necessary/already-created
            // Gernerate acceleration curve if necessary
            // Find if note has pitch shift applied, account for this.
            // Get delay time of motor for given pulse over the frame of a single note
            // Return time in uS for delay at that given time
        }

        uint32_t _get_Delay_Time()
        {

        }
};

#endif // STEPPER_MUSIC_H