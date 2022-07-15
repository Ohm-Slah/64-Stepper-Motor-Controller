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
    
    public:
        Music_Serial(uint8_t controlBoardNumber)
        {
            
        }

};