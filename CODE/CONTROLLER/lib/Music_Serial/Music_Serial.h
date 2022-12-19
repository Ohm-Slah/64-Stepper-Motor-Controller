/*
* 
* 1 bit  - state or multi-state change
*    - 0 : state change
*    1 bit  - lights or motors
*      - 0 : motors
*      2 bits - command type
*          - 00 : off
*          - 01 : on
*          - 10 : special
*          12 bits - frequency start
*              - 0x000 : 0 Hz (Will ignore)
*                      :::
*              - 0x140 : 320 Hz
*                      :::
*              - 0xFFF : 4095 Hz (Unlikely feasible)
*    
*          12 bits - frequency end
*              - 0x000 : 0 Hz (Will ignore)
*                      :::
*              - 0x140 : 320 Hz
*                      :::
*              - 0xFFF : 4095 Hz (Unlikely feasible)
*          
*           3 bits - Start volume?
*              - 0b000 : off
*                      :::
*              - 0b010 : mid volume
*                      :::
*              - 0b100 : max volume
* 
*           3 bits - End volume?
*              - 0b000 : off
*                      :::
*              - 0b010 : mid volume
*                      :::
*              - 0b100 : max volume
*    
*          16 bits - time in ms
*              - 0x0 : 0 ms (lol why)
*                      :::
*              - 0x0 : 3.85 s
*                      :::
*              - 0xFFFF : 65.535 s (upper limit)
*          1  bit  - note sustained after end?
*    
*          - 11 : -
*   
*    6 bits - motor number
* 
*      - 1:lights
* 
*    - 1 : state change
*  
*/
#include "Light_Control.h"

#define CONFIRM 'C'

#define STATECHANGE     63  // 1
#define COMMAND         61  // 2
#define MOTORNUMBER     56  // 5
#define FREQUENCYSTART  44  // 12
#define FREQUENCYEND    32  // 12
#define MICROSTEPSTART  29  // 3
#define MICROSTEPEND    26  // 3
#define TIMEINMS        10  // 16
#define NOTESUSTAINED   9   // 1

class Music_Serial_From_Computer
{
    private:

    public:
        Music_Serial_From_Computer()
        {

        }

        

        void serialInit()
        {
            
        }

        void send(char toSend[])
        {

        }

        void read()
        {

        }

        
};

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
            Serial.println("initializing serial with slave...");
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
                Serial.println("Serial communications confirmed.");
            }else {
                Serial.println("ERROR with serial comms");
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
                    Serial.println("CONFIRM BYTE ERROR");
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

        void sendSingleMotor(uint8_t motorNumber, uint8_t state, 
                            uint16_t frequencyStart, uint16_t frequencyEnd=0, 
                            uint8_t microstepStart=0, uint8_t microstepEnd=0,
                            uint16_t timems=0, uint8_t noteSustain=0)
        {
            uint64_t toSend =   (uint64_t)state << STATECHANGE | 
                                (uint64_t)1 << COMMAND |
                                (uint64_t)motorNumber << MOTORNUMBER |
                                (uint64_t)frequencyStart << FREQUENCYSTART |
                                (uint64_t)frequencyEnd << FREQUENCYEND |
                                (uint64_t)microstepStart << MICROSTEPSTART |
                                (uint64_t)microstepEnd << MICROSTEPEND |
                                (uint64_t)noteSustain << NOTESUSTAINED;

            Serial.println(toSend, BIN);
            Serial.print(state);Serial.print(" : ");Serial.print(STATECHANGE);Serial.print(" : ");Serial.println(state << STATECHANGE);

            char cstr[8];
            for(int i=0; i < 8; i++)
            {
                cstr[7-i] = (toSend >> (8*i)) & 0xFF;
                Serial.print(cstr[i], BIN);Serial.print(" ");
            }
            Serial.println();
            send(cstr);

            changeBoxColor(((motorNumber-1)%8)+1, motorNumber > 8 ? 2 : 1, (makeColor(motorNumber*45, 100, 50)) * state); //!temporary change
        }

};