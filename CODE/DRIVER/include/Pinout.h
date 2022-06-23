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
#define A1STEP1 22 // Temporary placeholder
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
#define RCLK 16 // Temporary placeholder

// Data in
#define SER1 18 // Temporary placeholder
#define SER2 10 // Temporary placeholder
#define SER3 11 // Temporary placeholder
#define SER4 12 // Temporary placeholder

// Shift clock
#define SRCLK1 17 // Temporary placeholder
#define SRCLK2 7 // Temporary placeholder
#define SRCLK3 8 // Temporary placeholder
#define SRCLK4 9 // Temporary placeholder

// Reset
#define SRCLR 15 // Temporary placeholder

// Output enable
#define OE 14 // Temporary placeholder

#define VCCVOLTAGEREADPIN -1 // Temporary placeholder
#define FIVEVOLTAGEREADPIN -1 // Temporary placeholder

//  *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*  //

//  *Define shift register pin order*   //
//  *-------------------------------*   //

#define DIR01 1
#define DIR05 2
#define A01EN 3
#define A05EN 4
#define A1MS1 5
#define A5MS1 6
#define A1MS2 7
#define A5MS2 8
#define A1MS3 9
#define A5MS3 10
#define DIR02 11
#define DIR06 12
#define A02EN 13
#define A06EN 14
#define A2MS1 15
#define A6MS1 16
#define A2MS2 17
#define A6MS2 18
#define A2MS3 19
#define A6MS3 20
#define DIR03 21
#define DIR07 22
#define A03EN 23
#define A07EN 24
#define A3MS1 25
#define A7MS1 26
#define A3MS2 27
#define A7MS2 28
#define A3MS3 29
#define A7MS3 30
#define DIR04 31
#define DIR08 32
#define A04EN 33
#define A08EN 34
#define A4MS1 35
#define A8MS1 36
#define A4MS2 37
#define A8MS2 38
#define A4MS3 39
#define A8MS3 40

uint8_t enablePins[8] = {A01EN, A02EN, A03EN, A04EN, A05EN, A06EN, A07EN, A08EN};
uint8_t directionPins[8] = {DIR01, DIR02, DIR03, DIR04, DIR05, DIR06, DIR07, DIR08};
uint8_t MS1Pins[8] = {A1MS1, A2MS1, A3MS1, A4MS1, A5MS1, A6MS1, A7MS1, A8MS1};
uint8_t MS2Pins[8] = {A1MS2, A2MS2, A3MS2, A4MS2, A5MS2, A6MS2, A7MS2, A8MS2};
uint8_t MS3Pins[8] = {A1MS3, A2MS3, A3MS3, A4MS3, A5MS3, A6MS3, A7MS3, A8MS3};

// char shiftRegisterOne[40][6] = {
//     "DIR01", "DIR05", "A01EN", "A05EN", "A1MS1", "A5MS1", "A1MS2", "A5MS2", "A1MS3", "A5MS3",
//     "DIR02", "DIR06", "A02EN", "A06EN", "A2MS1", "A6MS1", "A2MS2", "A6MS2", "A2MS3", "A6MS3",
//     "DIR03", "DIR07", "A03EN", "A07EN", "A3MS1", "A7MS1", "A3MS2", "A7MS2", "A3MS3", "A7MS3",
//     "DIR04", "DIR08", "A04EN", "A08EN", "A4MS1", "A8MS1", "A4MS2", "A8MS2", "A4MS3", "A8MS3"
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