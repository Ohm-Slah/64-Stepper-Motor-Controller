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

class Music_Serial
{
    private:
        char _readLine[100];
        uint8_t _controlBoardNumber;
    
    public:
        Music_Serial(uint8_t controlBoardNumber) :
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
            digitalWrite(13, HIGH);
            delay(250);
            digitalWrite(13, LOW);
            delay(250);
            digitalWrite(13, HIGH);
            delay(250);
            digitalWrite(13, LOW);
            delay(250);
            digitalWrite(13, HIGH);
            delay(250);
            digitalWrite(13, LOW);
        }

        void send(char toSend[])
        {
            switch(_controlBoardNumber)
            {
                case 1:
                    // for(uint8_t i=0; i<sizeof(toSend); i++)
                    // {
                    //     Serial7.write(toSend[i]);
                    // }
                    // Serial7.write('\n');
                    Serial7.write(toSend, sizeof(toSend));
                break;

                case 2:
                    // for(uint8_t i=0; i<sizeof(toSend)-1; i++)
                    // {
                    //     Serial8.write(toSend[i]);
                    // }
                    // Serial8.write('\n');
                    
                    Serial8.write(toSend, sizeof(toSend));
                    //Serial8.write('\n');
                break;
            }
        }

};