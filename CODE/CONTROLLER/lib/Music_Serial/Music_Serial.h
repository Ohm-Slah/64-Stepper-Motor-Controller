/*
 * File name: Music_Serial.h -> CONTROLLER
 * Project: 64 Motor Driver
 * Author: Elliot Eickholtz
 * Purpose: Serial communication library between Msster and Slaves.
 * 
*/

/*
 * Old Serial Command Structure:
 * (64-bit command)
 * 12233333 - 44444444 - 44445555 - 55555555 - 66677788 - 88888888 - 8888889X - XXXXXXXX
 * 1: STATECHANGE (Bool)    : On or Off
 * 2: COMMAND (Switch Case) : 00:Off ~ 01:On ~ 10:Special   //? Not used, defaults to 01
 * 3: MOTORNUMBER (Int)     : Range 0 - 31
 * 4: FREQUENCYSTART (Int)  : Range 0 - 4095
 * 5: FREQUENCYEND (Int)    : Range 0 - 4095                //? Not used
 * 6: MICROSTEPSTART (Int)  : Range 0 - 7
 * 7: MICROSTEPEND (Int)    : Range 0 - 7                   //? Not used
 * 8: TIMEINMS (Int)        : Range 0 - 65535               //? Not used
 * 9: NOTESUSTAINED (Bool)  : True of False                 //? Not used
 * X: Not Used
*/

/*
 * New Serial Command Structure:        //? As of 12/21/2022
 * (64-bit command)
 * 01122222 - 33444444 - 44444455 - 55555555 - 55666777 - 88888888 - 88888888 - 9AAAAAAA
 * 0: STATECHANGE (Bool)    : On or Off
 * 1: COMMAND (Switch Case) : 00:Off ~ 01:On ~ 10:Special   //? Not used, defaults to 01
 * 2: MOTORNUMBER (Int)     : Range 0 - 31
 * 3: NOTENUMBER (Int)      : Range 0- 3
 * 4: FREQUENCYSTART (Int)  : Range 0 - 4095
 * 5: FREQUENCYEND (Int)    : Range 0 - 4095                //? Not used
 * 6: MICROSTEPSTART (Int)  : Range 0 - 7
 * 7: MICROSTEPEND (Int)    : Range 0 - 7                   //? Not used
 * 8: TIMEINMS (Int)        : Range 0 - 65535               //? Not used
 * 9: NOTESUSTAINED (Bool)  : True of False                 //? Not used
 * A: SPECIALCOMMAND (Int)  : TBD                           //? Not Used
*/

#include "Light_Control.h"

#define CONFIRM 'C'

#ifndef DEBUG
#define DEBUG 0
#endif

#define STATECHANGE     63  // 1
#define COMMAND         61  // 2
#define MOTORNUMBER     56  // 5
#define NOTENUMBER      44  // 2
#define FREQUENCYSTART  42  // 12
#define FREQUENCYEND    30  // 12
#define MICROSTEPSTART  27  // 3
#define MICROSTEPEND    24  // 3
#define TIMEINMS        8  // 16
#define NOTESUSTAINED   7   // 1
#define SPECIALCOMMAND  0   // 7

// class Music_Serial_From_Computer
// {
//     private:
//     public:
//         Music_Serial_From_Computer()
//         {
//         }
//         void serialInit()
//         {
//         }
//         void send(char toSend[])
//         {
//         }
//         void read()
//         {
//         }
// };

class Music_Serial_To_Slave
{
    private:
        char _readLine[100];
        uint8_t _controlBoardNumber;
    
    public:
        Music_Serial_To_Slave(uint8_t controlBoardNumber) :
        _controlBoardNumber(controlBoardNumber)
        {
            
        }

        void serialInit()
        {
            !DEBUG ? true : Serial.println("initializing serial with slave...");
            switch(_controlBoardNumber)
            {
                case 1:
                    Serial7.begin(115200);
                    send("I\n");
                    while (!Serial7.available());
                    Serial7.readBytesUntil('\n', _readLine, 100);
                break;

                case 2:
                    Serial8.begin(115200);
                    send("I\n");
                    while (!Serial8.available());
                    Serial8.readBytesUntil('\n', _readLine, 100);
                break;
            }

            if(_readLine[0] == 'I')
            {
                !DEBUG ? true : Serial.println("Serial communications confirmed.");
            }else {
                !DEBUG ? true : Serial.println("ERROR with serial comms");
            }

            pinMode(13, OUTPUT);
            for(int i=0; i<3; i++)
            {
                digitalWrite(13, HIGH);
                delay(250);
                digitalWrite(13, LOW);
                delay(250);
            }
        }

        void readConfirmByte()
        {
            if(Serial.available())
            {
                char readByte;
                switch(_controlBoardNumber)
                {
                    case 1:
                        readByte = Serial7.read();
                    break;
                    case 2:
                        readByte = Serial8.read();
                    break;
                }

                Serial.flush();

                if (readByte != CONFIRM)
                    !DEBUG ? true : Serial.println("CONFIRM BYTE ERROR");
            }
            
        }

        void send(char toSend[])
        {
            switch(_controlBoardNumber)
            {
                case 1:
                    Serial7.write(toSend, sizeof(toSend));
                    Serial7.write(0x7F);
                break;

                case 2:
                    Serial8.write(toSend, sizeof(toSend));
                    Serial8.write(0x7F);
                break;
            }
        }

        void sendSingleMotor(uint8_t motorNumber, uint8_t state, uint8_t noteNumber,
                            uint16_t frequencyStart, uint16_t frequencyEnd=0, 
                            uint8_t microstepStart=0, uint8_t microstepEnd=0,
                            uint16_t timems=0, uint8_t noteSustain=0, uint8_t specialCommand=0)
        {
            uint64_t toSend =   (uint64_t)state << STATECHANGE |
                                (uint64_t)1 << COMMAND |
                                (uint64_t)motorNumber << MOTORNUMBER |
                                (uint64_t)noteNumber << NOTENUMBER |
                                (uint64_t)frequencyStart << FREQUENCYSTART |
                                (uint64_t)frequencyEnd << FREQUENCYEND |
                                (uint64_t)microstepStart << MICROSTEPSTART |
                                (uint64_t)microstepEnd << MICROSTEPEND |
                                (uint64_t)timems << TIMEINMS |
                                (uint64_t)noteSustain << NOTESUSTAINED |
                                (uint64_t)specialCommand << SPECIALCOMMAND;

            !DEBUG ? true : Serial.println(toSend, BIN);
            !DEBUG ? true : Serial.print(state);
            !DEBUG ? true : Serial.print(" : ");
            !DEBUG ? true : Serial.print(STATECHANGE);
            !DEBUG ? true : Serial.print(" : ");
            !DEBUG ? true : Serial.println(state << STATECHANGE);

            char cstr[8];
            for(int i=0; i < 8; i++)
            {
                cstr[7-i] = (toSend >> (8*i)) & 0xFF;
                !DEBUG ? true : Serial.print(cstr[i], BIN);!DEBUG ? true : Serial.print(" ");
            }
            !DEBUG ? true : Serial.println();
            send(cstr);

            changeBoxColor(((motorNumber-1)%8)+1, motorNumber > 8 ? 2 : 1, (makeColor(motorNumber*45, 100, 50)) * state); //!temporary change
        }

};