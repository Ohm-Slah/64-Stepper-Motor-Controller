/*
 * File name: main.cpp -> DRIVER
 * Project: 64 Motor Driver
 * Author: Elliot Eickholtz
 * Purpose: Drive 64 stepper motors with 2 Teensy 4.0's, 32 motors each. Slave to Teensy 4.1 microcontroller.
 * 
*/

#include <Arduino.h>
#include <Stepper_Music.h>
#include <Music_Serial.h>

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

Music_Serial Master(1);

void setup() 
{
	Serial.begin(115200);
	Master.serialInit();
}

void loop() {
  	// update serial

  	for(int i=0; i<32; i++)
  	{
		if(! AllMotors[i].pulseWait)
		{
			AllMotors[i].singleStep();
		}
  	}
}