/*
 * File name: Music_Serial.h -> DRIVER
 * Project: 64 Motor Driver
 * Author: Elliot Eickholtz
 * Purpose: Driver-side custom serial communication library.
 * 
*/

#ifndef MUSIC_SERIAL_H
#define MUSIC_SERIAL_H

//* Declare bitwise filters *//
#define STATECHANGE     63  // 1
#define COMMAND         61  // 2
#define MOTORNUMBER     56  // 5
#define FREQUENCYSTART  44  // 12
#define FREQUENCYEND    32  // 12
#define MICROSTEPSTART  29  // 3
#define MICROSTEPEND    26  // 3
#define TIMEINMS        10  // 16
#define NOTESUSTAINED   9   // 1

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
            Serial.println("initializing serial with slave...");
            // Make sure confirm master is present
            while(!available());
            read();
            
            if(_readLine[0] == 'I') 
            {
                Serial.println("Serial communications confirmed.");
                send("I\n");
            } else {
                Serial.print("ERROR with serial comms: ");
                Serial.println(_readLine);
                Serial.println(sizeof(_readLine));
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
            // for(uint8_t i=0; i<sizeof(toSend); i++)
            // {
            //     Serial2.write(toSend[i]);
            // }
            // Serial2.write('\n');
            Serial2.write(toSend, sizeof(toSend));
        }

        void read()
        {
            // uint8_t i = 0;
            // for(; i< 100; i++) _readLine[i] = 0;
            // i = 0;
            // while(available())
            // {
            //     _readLine[i] = Serial2.read();
            //     i++;
            // }
            uint8_t recieveBytes = Serial2.readBytesUntil('\n', _readLine, 100);
            masterRead = 0;
            
            for(uint8_t i=0; i < recieveBytes; i++)
            {
                Serial.print(_readLine[i], BIN);Serial.print(" ");
                masterRead |= (uint64_t)_readLine[i] << 8*(7-i);
            }
            Serial.println(masterRead, BIN);
        }

        void setMasterCommand()
        {
            uint8_t motorNumber, state, command;
            uint16_t frequencyStart, frequencyEnd; 
            uint8_t microstepStart, microstepEnd;
            uint16_t timems;
            uint8_t noteSustain;

            motorNumber = masterRead >> MOTORNUMBER & 0B11111;
            command = masterRead >> COMMAND & 0B11;
            state = masterRead >> STATECHANGE & 0B1;
            frequencyStart = masterRead >> FREQUENCYSTART & 0B111111111111;
            frequencyEnd = masterRead >> FREQUENCYEND & 0B111111111111;
            microstepStart = masterRead >> MICROSTEPSTART & 0B111;
            microstepEnd = masterRead >> MICROSTEPEND & 0B111;
            timems = masterRead >> TIMEINMS & 0B1111111111111111;
            noteSustain = masterRead >> NOTESUSTAINED & 0B1;
            // Serial.print("motorNumber : ");Serial.println(motorNumber);
            // Serial.print("command : ");Serial.println(command);
            // Serial.print("frequencyStart : ");Serial.println(frequencyStart);
            // Serial.print("frequencyEnd : ");Serial.println(frequencyEnd);
            // Serial.print("microstepStart : ");Serial.println(microstepStart);
            // Serial.print("microstepEnd : ");Serial.println(microstepEnd);
            // Serial.print("timems : ");Serial.println(timems);
            // Serial.print("noteSustain : ");Serial.println(noteSustain);
            // Serial.print("state : ");Serial.println(state);

            AllMotors[motorNumber-1].motorMove(state, frequencyStart, frequencyEnd, timems, noteSustain);
        }
};

#endif // MUSIC_SERIAL_H