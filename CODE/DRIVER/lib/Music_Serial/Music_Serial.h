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

    bool available()
    {
        return Serial1.available();
    }

    void read()
    {
        /*
        * command type, channel, on/off, volume
        * 1 bit  - lights or motors
        *   - 0 : motors
        *   2 bits - command type
        *       - 00 : off
        *       - 01 : on
        *       - 10 : glissando
        *       12 bits - frequency start
        *           - 0x000 : 0 Hz (Will ignore)
        *                   :::
        *           - 0x140 : 320 Hz
        *                   :::
        *           - 0xFFF : 4095 Hz (Unlikely feasible)
        * 
        *       12 bits - frequency end
        *           - 0x000 : 0 Hz (Will ignore)
        *                   :::
        *           - 0x140 : 320 Hz
        *                   :::
        *           - 0xFFF : 4095 Hz (Unlikely feasible)
        * 
        *       16 bits - time in ms
        *           - 0x0000 : 0 ms (lol why)
        *                   :::
        *           - 0x0F0A : 3.85 s
        *                   :::
        *           - 0xFFFF : 65.535 s (limit)
        *       1  bit  - note sustained after end?
        * 
        *       - 11 : crescendo/decrescendo
        *
        * 6 bits - motor number
        *  - 1:lights
        *  
        * 
        */
    }
};

#endif // MUSIC_SERIAL_H