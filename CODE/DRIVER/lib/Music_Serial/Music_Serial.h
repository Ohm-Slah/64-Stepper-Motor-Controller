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
    Music_Serial()
    {
        Serial1.begin(115200);
        while(!Serial1.available())
        {
            Serial1.println("SER_INIT");    // 'initialize serial' command

        }
        

    }

    bool available()
    {
        return Serial1.available();
    }

    void read()
    {
        
    }
};

#endif // MUSIC_SERIAL_H