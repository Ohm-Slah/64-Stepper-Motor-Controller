/*
 * File name: Pinout.h -> DRIVER
 * Project: 64 Motor Driver
 * Author: Elliot Eickholtz
 * Purpose: Define all pins used on the Teensy 4.0.
 * 
*/

#ifndef PINOUT_H
#define PINOUT_H

//  *Initialize all stepper driver freq pins to a unique identifier*  //
//  *--------------------------------------------------------------*  //
#define A1STEP1 -1 // Temporary placeholder
#define A2STEP1 -1 // Temporary placeholder
#define A3STEP1 -1 // Temporary placeholder
#define A4STEP1 -1 // Temporary placeholder
#define A5STEP1 -1 // Temporary placeholder
#define A6STEP1 -1 // Temporary placeholder
#define A7STEP1 -1 // Temporary placeholder
#define A8STEP1 -1 // Temporary placeholder
#define A1STEP2 -1 // Temporary placeholder
#define A2STEP2 -1 // Temporary placeholder
#define A3STEP2 -1 // Temporary placeholder
#define A4STEP2 -1 // Temporary placeholder
#define A5STEP2 -1 // Temporary placeholder
#define A6STEP2 -1 // Temporary placeholder
#define A7STEP2 -1 // Temporary placeholder
#define A8STEP2 -1 // Temporary placeholder
#define A1STEP3 -1 // Temporary placeholder
#define A2STEP3 -1 // Temporary placeholder
#define A3STEP3 -1 // Temporary placeholder
#define A4STEP3 -1 // Temporary placeholder
#define A5STEP3 -1 // Temporary placeholder
#define A6STEP3 -1 // Temporary placeholder
#define A7STEP3 -1 // Temporary placeholder
#define A8STEP3 -1 // Temporary placeholder
#define A1STEP4 -1 // Temporary placeholder
#define A2STEP4 -1 // Temporary placeholder
#define A3STEP4 -1 // Temporary placeholder
#define A4STEP4 -1 // Temporary placeholder
#define A5STEP4 -1 // Temporary placeholder
#define A6STEP4 -1 // Temporary placeholder
#define A7STEP4 -1 // Temporary placeholder
#define A8STEP4 -1 // Temporary placeholder

// Latch clock
#define RCLK -1 // Temporary placeholder

// Data in
#define SER1 -1 // Temporary placeholder
#define SER2 -1 // Temporary placeholder
#define SER3 -1 // Temporary placeholder
#define SER4 -1 // Temporary placeholder

// Shift clock
#define SRCLK1 -1 // Temporary placeholder
#define SRCLK2 -1 // Temporary placeholder
#define SRCLK3 -1 // Temporary placeholder
#define SRCLK4 -1 // Temporary placeholder

// Reset
#define SRCLR -1 // Temporary placeholder

// Output enable
#define OE -1 // Temporary placeholder

#define VCCVOLTAGEREADPIN -1 // Temporary placeholder
#define FIVEVOLTAGEREADPIN -1 // Temporary placeholder

//  *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*  //

//  *Define shift register pin order*   //
//  *-------------------------------*   //

// TODO Used as reference for now
// char shiftRegisterOne[40][6] = {
//!     "DIR01", "DIR05", "A01EN", "A05EN", "A1MS1", "A5MS1", "A1MS2", "A5MS2", "A1MS3", "A5MS3",
//!     "DIR02", "DIR06", "A02EN", "A06EN", "A2MS1", "A6MS1", "A2MS2", "A6MS2", "A2MS3", "A6MS3",
//!     "DIR03", "DIR07", "A03EN", "A07EN", "A3MS1", "A7MS1", "A3MS2", "A7MS2", "A3MS3", "A7MS3",
//!     "DIR04", "DIR08", "A04EN", "A08EN", "A4MS1", "A8MS1", "A4MS2", "A8MS2", "A4MS3", "A8MS3"
// };

// char shiftRegisterTwo[40][6] = {
//     "DIR01", "DIR05", "A01EN", "A05EN", "A1MS1", "A5MS1", "A1MS2", "A5MS2", "A1MS3", "A5MS3",
//     "DIR02", "DIR06", "A02EN", "A06EN", "A2MS1", "A6MS1", "A2MS2", "A6MS2", "A2MS3", "A6MS3",
//     "DIR03", "DIR07", "A03EN", "A07EN", "A3MS1", "A7MS1", "A3MS2", "A7MS2", "A3MS3", "A7MS3",
//     "DIR04", "DIR08", "A04EN", "A08EN", "A4MS1", "A8MS1", "A4MS2", "A8MS2", "A4MS3", "A8MS3"
// };

// char shiftRegisterThree[40][6] = {
//     "DIR01", "DIR05", "A01EN", "A05EN", "A1MS1", "A5MS1", "A1MS2", "A5MS2", "A1MS3", "A5MS3",
//     "DIR02", "DIR06", "A02EN", "A06EN", "A2MS1", "A6MS1", "A2MS2", "A6MS2", "A2MS3", "A6MS3",
//     "DIR03", "DIR07", "A03EN", "A07EN", "A3MS1", "A7MS1", "A3MS2", "A7MS2", "A3MS3", "A7MS3",
//     "DIR04", "DIR08", "A04EN", "A08EN", "A4MS1", "A8MS1", "A4MS2", "A8MS2", "A4MS3", "A8MS3"
// };

// char shiftRegisterFour[40][6] = {
//     "DIR01", "DIR05", "A01EN", "A05EN", "A1MS1", "A5MS1", "A1MS2", "A5MS2", "A1MS3", "A5MS3",
//     "DIR02", "DIR06", "A02EN", "A06EN", "A2MS1", "A6MS1", "A2MS2", "A6MS2", "A2MS3", "A6MS3",
//     "DIR03", "DIR07", "A03EN", "A07EN", "A3MS1", "A7MS1", "A3MS2", "A7MS2", "A3MS3", "A7MS3",
//     "DIR04", "DIR08", "A04EN", "A08EN", "A4MS1", "A8MS1", "A4MS2", "A8MS2", "A4MS3", "A8MS3"
// };

//  *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*   //

#endif  // PINOUT_H