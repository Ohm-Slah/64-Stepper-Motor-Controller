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
#define STATE       0b1
#define COMMAND     0b1
#define FREQSTART   0b1
#define FREQEND     0b1
#define VOLSTART    0b1
#define VOLEND      0b1


class Music_Serial
{
    private:
        char _readLine[100];
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
            Serial2.readBytesUntil('\n', _readLine, 100);
        }
};

#endif // MUSIC_SERIAL_H