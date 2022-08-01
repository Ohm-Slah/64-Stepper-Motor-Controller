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

Music_Serial Master(1);

void setup() 
{
	Serial.begin(115200);
	Master.serialInit();
}

void loop() {
  	if(Master.available()) 
	{
		Master.read();
		Master.setMasterCommand();
	}

  	for(int i=0; i<32; i++)
  	{
		if(! AllMotors[i].pulseWait)
		{
			AllMotors[i].singleStep();
		}
  	}
	// Serial.println("TEST");
	// AllMotors[1].testFunctionality(200, 10000);
	// delay(1000);
}