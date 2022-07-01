/*
 * File name: Music_Serial.h -> DRIVER
 * Project: 64 Motor Driver
 * Author: Elliot Eickholtz
 * Purpose: Driver-side custom serial communication library.
 * 
*/

#ifndef MUSIC_SERIAL_H
#define MUSIC_SERIAL_H

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
};

#endif // MUSIC_SERIAL_H