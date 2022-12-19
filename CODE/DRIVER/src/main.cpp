/*
 * File name: main.cpp -> DRIVER
 * Project: 64 Motor Driver
 * Author: Elliot Eickholtz
 * Purpose: Drive 64 stepper motors with 2 Teensy 4.0's, 32 motors each. Slave to Teensy 4.1 microcontroller.
 * 
*/

//* Library includes *//
#include <Arduino.h>
#include <Stepper_Music.h>
#include <Music_Serial.h>
//*^^^^^^^^^^^^^^^^^^*//

// Initialize Class, "1" means nothing.
Music_Serial Master(1);

void setup() 
{
	Serial.begin(115200);
	Master.serialInit();
}

void loop() {
  	if(Master.available()) 
	{
		// Read Serial buffer from master
		Master.read();
		// Decode and set master command into action
		Master.setMasterCommand();
	}

	// Loop through all 32 motors tied to microcontroller
  	for(int i=0; i<32; i++)
  	{
		// Wait the alloted time to replicate set frequency
		if(AllMotors[i].pulseWait)
		{
			AllMotors[i].singleStep();
		}
  	}
}