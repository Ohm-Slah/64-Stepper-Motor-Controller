/*
 * File name: Music_Serial.h -> DRIVER
 * Project: 64 Motor Driver
 * Author: Elliot Eickholtz
 * Purpose: Driver-side custom serial communication library.
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
 * New Serial Command Structure:
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

#ifndef MUSIC_SERIAL_H
#define MUSIC_SERIAL_H

//* Declare bitwise filters *//
#define STATECHANGE     63  // 1
#define COMMAND         61  // 2
#define MOTORNUMBER     56  // 5
#define NOTENUMBER      54  // 2
#define FREQUENCYSTART  42  // 12
#define FREQUENCYEND    30  // 12
#define MICROSTEPSTART  27  // 3
#define MICROSTEPEND    24  // 3
#define TIMEINMS        8  // 16
#define NOTESUSTAINED   7   // 1
#define SPECIALCOMMAND  0   // 7
//*^^^^^^^^^^^^^^^^^^^^^^^^^*//

//* Create instance of motor class for each motor *//
Motor Motor1(A1STEP1, 1);
Motor Motor2(A2STEP1, 2);
Motor Motor3(A3STEP1, 3);
Motor Motor4(A4STEP1, 4);
Motor Motor5(A5STEP1, 5);
Motor Motor6(A6STEP1, 6);
Motor Motor7(A7STEP1, 7);
Motor Motor8(A8STEP1, 8);

Motor Motor9(A1STEP2, 9);
Motor Motor10(A2STEP2, 10);
Motor Motor11(A3STEP2, 11);
Motor Motor12(A4STEP2, 12);
Motor Motor13(A5STEP2, 13);
Motor Motor14(A6STEP2, 14);
Motor Motor15(A7STEP2, 15);
Motor Motor16(A8STEP2, 16);

Motor Motor17(A1STEP3, 17);
Motor Motor18(A2STEP3, 18);
Motor Motor19(A3STEP3, 19);
Motor Motor20(A4STEP3, 20);
Motor Motor21(A5STEP3, 21);
Motor Motor22(A6STEP3, 22);
Motor Motor23(A7STEP3, 23);
Motor Motor24(A8STEP3, 24);

Motor Motor25(A1STEP4, 25);
Motor Motor26(A2STEP4, 26);
Motor Motor27(A3STEP4, 27);
Motor Motor28(A4STEP4, 28);
Motor Motor29(A5STEP4, 29);
Motor Motor30(A6STEP4, 30);
Motor Motor31(A7STEP4, 31);
Motor Motor32(A8STEP4, 32);
//*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*//

Motor AllMotors[32] = {	
	Motor1, Motor2,  Motor3,  Motor4,  Motor5,  Motor6,  Motor7,  Motor8, 
	Motor9, Motor10, Motor11, Motor12, Motor13, Motor14, Motor15, Motor16, 
	Motor17, Motor18, Motor19, Motor20, Motor21, Motor22, Motor23, Motor24, 
	Motor25, Motor26, Motor27, Motor28, Motor29, Motor30, Motor31, Motor32	
};


class Music_Serial
{
    private:
        char _readLine[20];
        uint64_t masterRead;
    public:
        Music_Serial(uint8_t nothing)
        {
            Serial2.begin(115200);
        }

        void serialInit()
        {
            !DEBUG ? true : Serial.println("initializing serial with slave...");
            // Make sure confirm master is present
            while(!available());
            read();
            
            if(_readLine[0] == 'I') 
            {
                !DEBUG ? true : Serial.println("Serial communications confirmed.");
                send("I\n");
            } else {
                !DEBUG ? true : Serial.print("ERROR with serial comms: ");
                !DEBUG ? true : Serial.println(_readLine);
                !DEBUG ? true : Serial.println(sizeof(_readLine));
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

        bool available()
        {
            return Serial2.available();
        }

        void send(char toSend[])
        {
            Serial2.write(toSend, sizeof(toSend));
        }

        void read()
        {
            uint8_t recieveBytes = Serial2.readBytesUntil(0x7F, _readLine, 100);
            masterRead = 0;
            
            for(uint8_t i=0; i < recieveBytes; i++)
            {
                //!DEBUG ? true : Serial.print(_readLine[i], BIN);!DEBUG ? true : Serial.print(" ");
                masterRead |= (uint64_t)_readLine[i] << 8*(7-i);
            }
            !DEBUG ? true : Serial.println(masterRead, BIN);
        }

        void clearAllMotors()
        {
            for(int i=0; i < 32; i++)
            {
                for(int j=0; j < 4; j++)
                {
                    AllMotors[i].motorMove(false, 0, 0, j, 0, 0);
                }
            }
        }

        void setMasterCommand()
        {
            uint8_t motorNumber, state, command, noteNumber;
            uint16_t frequencyStart, frequencyEnd; 
            uint8_t microstepStart, microstepEnd;
            uint16_t timems;
            uint8_t noteSustain, specialCommand;

            motorNumber = masterRead >> MOTORNUMBER & 0B11111;
            command = masterRead >> COMMAND & 0B11;
            state = masterRead >> STATECHANGE & 0B1;
            noteNumber = masterRead >> NOTENUMBER & 0B11;
            frequencyStart = masterRead >> FREQUENCYSTART & 0B111111111111;
            frequencyEnd = masterRead >> FREQUENCYEND & 0B111111111111;
            microstepStart = masterRead >> MICROSTEPSTART & 0B111;
            microstepEnd = masterRead >> MICROSTEPEND & 0B111;
            timems = masterRead >> TIMEINMS & 0B1111111111111111;
            noteSustain = masterRead >> NOTESUSTAINED & 0B1;
            //specialCommand = masterRead >> SPECIALCOMMAND & 0B1111111;
            
            !DEBUG ? true : Serial.print("motorNumber : ");!DEBUG ? true : Serial.println(motorNumber);
            !DEBUG ? true : Serial.print("command : ");!DEBUG ? true : Serial.println(command);
            !DEBUG ? true : Serial.print("state : ");!DEBUG ? true : Serial.println(state);
            !DEBUG ? true : Serial.print("noteNumber : ");!DEBUG ? true : Serial.println(noteNumber);
            !DEBUG ? true : Serial.print("frequencyStart : ");!DEBUG ? true : Serial.println(frequencyStart);
            !DEBUG ? true : Serial.print("frequencyEnd : ");!DEBUG ? true : Serial.println(frequencyEnd);
            !DEBUG ? true : Serial.print("microstepStart : ");!DEBUG ? true : Serial.println(microstepStart);
            !DEBUG ? true : Serial.print("microstepEnd : ");!DEBUG ? true : Serial.println(microstepEnd);
            !DEBUG ? true : Serial.print("timems : ");!DEBUG ? true : Serial.println(timems);
            !DEBUG ? true : Serial.print("noteSustain : ");!DEBUG ? true : Serial.println(noteSustain);
            
            if(!command)
            {
                clearAllMotors();
            } else {
                AllMotors[motorNumber-1].motorMove(state, frequencyStart, frequencyEnd, noteNumber, timems, noteSustain);
            }
        }
};

#endif // MUSIC_SERIAL_H