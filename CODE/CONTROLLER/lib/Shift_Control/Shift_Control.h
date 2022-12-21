/*
 * File name: Shift_Control.h -> CONTROLLER
 * Project: 64 Motor Driver
 * Author: Elliot Eickholtz
 * Purpose: Shift register control library.
 * 
*/

#include "Pinout.h"
#include "pitches.h"

#define DEBUG 1

class Card
{
    private:
        uint8_t _serialPin;
        uint8_t _clockPin;
        uint8_t _cardNumber;
        uint8_t _boardNumber;
        uint64_t _buffer = 0;

        int8_t _maxMidiNoteForMicrostep[6] = {
            -1, // No zero setting for microstepping
            73, // C5 - 523 Hz maximum for microstep setting 1
            84, // C6 - 1047 Hz maximum for microstep setting 2
            96, // C7 - 2093 Hz maximum for microstep setting 3
            111, // No maximum for microstep setting 4
            111  // No maximum for microstep setting 5
        };

        void _fillBuffer(uint64_t buf)
        {
            _buffer = buf;
        }

    public:
        uint8_t currentMicrostepSetting[8];
        uint8_t finalMicrostepSetting[8];
        uint64_t usTimeinMicrostepSetting[8];
        uint8_t motorState[8][4];   // 8 motors/card, 4 notes/motor

        // Time in microseconds before transitioning to new microstep setting
        int32_t timePerMicrostepRamp[6] = {
            -1,
            -1,
            50000,
            100000,
            200000,
            400000
        };

        Card(uint8_t cardNumber, uint8_t boardNumber) : 
            _cardNumber(cardNumber),
            _boardNumber(boardNumber)
        {
        // Constructor for a single card containing 8 motors. All shift register work is done here.
            if(cardNumber > 4 || !cardNumber) 
            {
                !DEBUG ? true : Serial.println("The Card Number entered for the Instantiation of Card class is out of range.");
                return;
            }

            switch (boardNumber)
            {
                case 1:
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
                break;

                case 2:
                    switch (cardNumber)
                    {
                        case 1:
                            _serialPin = SER5;
                            _clockPin = SRCLK5;
                        break;
                        case 2:
                            _serialPin = SER6;
                            _clockPin = SRCLK6;
                        break;
                        case 3:
                            _serialPin = SER7;
                            _clockPin = SRCLK7;
                        break;
                        case 4:
                            _serialPin = SER8;
                            _clockPin = SRCLK8;
                        break;
                    }
            }
            

            pinMode(_serialPin, OUTPUT);
            pinMode(_clockPin, OUTPUT);

        }

        void getInfo()
        {
            Serial.println("CARD INFORMATION");
            Serial.print("Board Number: ");Serial.println(_boardNumber);
            Serial.print("Card Number: ");Serial.println(_cardNumber);
            Serial.print("Serial Pin: ");Serial.println(_serialPin);
            Serial.print("Clock Pin: ");Serial.println(_clockPin);
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
            !DEBUG ? true : Serial.print("Register written with: ");
            !DEBUG ? true : Serial.println(_buffer);
        }

        void enableMotor(uint8_t motorNum)
        {
            _buffer &= ~((uint64_t)1 << (enablePins[motorNum-1]-1));
            !DEBUG ? true : Serial.print("MotorNum: ");
            !DEBUG ? true : Serial.println(motorNum);
            !DEBUG ? true : Serial.print("EnablePin: ");
            !DEBUG ? true : Serial.println(enablePins[motorNum-1]-1);
            !DEBUG ? true : Serial.print("Enable: "); 
            !DEBUG ? true : Serial.print(((uint64_t)1 << (enablePins[motorNum-1]-1)));
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

        uint8_t checkMicrostep(uint8_t microStep, byte note)
        {
            
            for(; microStep < 6; microStep++)
            {
                if(note < _maxMidiNoteForMicrostep[microStep]) break;
            }
            return microStep;
        }

        void changeMicroStep(uint8_t motorNum, uint8_t microStep)
        {
            switch (microStep)
            {
                case 1:
                    _buffer &= ~(((uint64_t)1 << (MS1Pins[motorNum-1]-1)) | ((uint64_t)1 << (MS2Pins[motorNum-1]-1)) | ((uint64_t)1 << (MS3Pins[motorNum-1]-1)));
                break;
                case 2:
                    _buffer &= ~(((uint64_t)1 << (MS2Pins[motorNum-1]-1)) | ((uint64_t)1 <<(MS3Pins[motorNum-1]-1)));
                    _buffer |= (1 << (MS1Pins[motorNum-1]-1));
                break;
                case 3:
                    _buffer &= ~(((uint64_t)1 << (MS1Pins[motorNum-1]-1)) | ((uint64_t)1 << (MS3Pins[motorNum-1]-1)));
                    _buffer |= ((uint64_t)1 << (MS2Pins[motorNum-1]-1));
                break;
                case 4:
                    _buffer &= ~((uint64_t)1 << (MS3Pins[motorNum-1]-1));
                    _buffer |= (((uint64_t)1 << (MS1Pins[motorNum-1]-1)) | ((uint64_t)1 << (MS2Pins[motorNum-1]-1)));
                break;
                case 5:
                    _buffer |= (((uint64_t)1 << (MS1Pins[motorNum-1]-1)) | ((uint64_t)1 << (MS2Pins[motorNum-1]-1)) | ((uint64_t)1 << (MS3Pins[motorNum-1]-1)));
                break;
            }
        }

};

class ControlBoard
{
    private:
        uint8_t _controlBoardNumber;
        uint8_t SRCLR, RCLK, OE;
        
    public:
        Card Cards[4];
        Music_Serial_To_Slave Driver;

        ControlBoard(uint8_t controlBoardNumber) :
            _controlBoardNumber(controlBoardNumber),
            Driver(controlBoardNumber),
            Cards{  Card(1, controlBoardNumber), 
                    Card(2, controlBoardNumber), 
                    Card(3, controlBoardNumber), 
                    Card(4, controlBoardNumber) }
        {
            if (_controlBoardNumber == 1)
            {
                SRCLR = SRCLR1;
                RCLK = RCLK1;
                OE = OE1;
            } else {
                SRCLR = SRCLR2;
                RCLK = RCLK2;
                OE = OE2;
            }

            
            
            pinMode(SRCLR, OUTPUT); // reset pin
            pinMode(RCLK, OUTPUT);  // latch pin
            pinMode(OE, OUTPUT);    // output enable pin

            digitalWrite(OE, LOW);
            digitalWrite(SRCLR, HIGH);

            enableAllRegisters();

            for(uint8_t i=0; i < 4; i++)
            {
                Cards[i].clearBuffer();
                Cards[i].disableAllMotors();
                Cards[i].writeRegister();
            }
            resetLatch();
        }

        void getInfo()
        {
            Serial.println("BOARD INFORMATION");
            Serial.print("Control Board: ");Serial.println(_controlBoardNumber);
            Serial.print("SRCLR Pin: ");Serial.println(SRCLR);
            Serial.print("RCLK Pin: ");Serial.println(RCLK);
            Serial.print("OE Pin: ");Serial.println(OE);
        }

        void midiEvent(byte cardNumber, byte motorNumber, byte note, byte velocity)
        {
            uint32_t frequency = 1000000/pitchVals[note];
            !DEBUG ? true : Serial.println(cardNumber);
            !DEBUG ? true : Serial.println(motorNumber);
            !DEBUG ? true : Serial.println(note);
            !DEBUG ? true : Serial.println(frequency);

            uint8_t noteNumber = 0;

            if (velocity > 0)
            {
                for(; noteNumber<4; noteNumber++)
                {
                    if (Cards[cardNumber].motorState[motorNumber][noteNumber] == note)
                    {
                        Cards[cardNumber].motorState[motorNumber][noteNumber] = 0;
                        Cards[cardNumber].disableMotor(motorNumber);
                        break;
                    }
                }
            } else {
                for(;noteNumber < 4; noteNumber++)
                {
                    if (Cards[cardNumber].motorState[motorNumber][noteNumber] == 0)
                    {
                        Cards[cardNumber].motorState[motorNumber][noteNumber] = note;
                        Cards[cardNumber].disableMotor(motorNumber);
                        break;
                    }
                }
            }
            if (noteNumber >= 4) !DEBUG ? true : Serial.println("\nMotor at max capacity, ignoring.");

            uint8_t microstep = int(map(velocity, 0, 127, 5, 1));

            // limit microstepping setting to maximum an average motor can handle.
            microstep = Cards[cardNumber].checkMicrostep(microstep, note);
            
            Cards[cardNumber].changeMicroStep(motorNumber, microstep);
            Cards[cardNumber].writeRegister();
            resetLatch();
            Driver.sendSingleMotor(motorNumber+(cardNumber*8), (velocity ? true : false), noteNumber, frequency);//!temporary change
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

ControlBoard BoardOne(1);
ControlBoard BoardTwo(2);

class MainControl
{
    //private:
    public:
        MainControl(uint8_t literallyNothing)
        {
            BoardOne.Driver.serialInit();
            BoardTwo.Driver.serialInit();
        }

        void midiEvent(uint8_t channel, uint8_t note, uint8_t velocity)
        {
            uint8_t x = (channel-1) % 8;
            uint8_t y = channel > 8 ? 1 : 0;

            //! temporary
            !DEBUG ? true : Serial.print("Card: ");
            !DEBUG ? true : Serial.println(channel > 8 ? 1 : 0);
            !DEBUG ? true : Serial.print("Motor on Card: ");
            !DEBUG ? true : Serial.println(((channel-1)%8)+1);
            BoardTwo.midiEvent(channel > 8 ? 1 : 0,((channel-1)%8)+1, note, velocity);

            // (gridToCard(x, y) == 1)
            // ?   BoardOne.midiEvent(gridToCard(x, y), gridToMotorNumber(x, y), note, velocity)
            // :   BoardTwo.midiEvent(gridToCard(x, y), gridToMotorNumber(x, y), note, velocity);
        }

        uint8_t gridToBoard(uint8_t x, uint8_t y)
        {
            return (x > 3) + 1;
        }

        uint8_t gridToCard(uint8_t x, uint8_t y)
        {
            return (y / 2);
        }

        uint8_t gridToMotorInCard(uint8_t x, uint8_t y)
        {
            return (y % 2 ? 0 : 4) + (x % 4) + 1;
        }

        uint8_t gridToMotorNumber(uint8_t x, uint8_t y)
        {
            return gridToCard(x, y) * 8 + gridToMotorInCard(x, y);
        }
};