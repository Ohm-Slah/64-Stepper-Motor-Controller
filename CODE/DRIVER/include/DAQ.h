/*
 * File name: DAQ.h -> DRIVER
 * Project: 64 Motor Driver
 * Author: Elliot Eickholtz
 * Purpose: General purpose data aquisition.
 * 
*/

//-----------------------Create quick-read info definitions----------------------------//
// Give analog Reading Converted to voltage
#define VCCVOLTAGE map(analogRead(VCCVOLTAGEREADPIN), 1, 1023, 1, 1023)
#define FIVEVOLTAGE map(analogRead(FIVEVOLTAGEREADPIN), 1, 1023, 1, 1023)

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^//