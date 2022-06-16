# 64-Stepper-Motor-Controller
Controls an 8x8 array of stepper motors and RGB LED light strips, intended for audio/visual performance of a MIDI-like structure. You can certainly make this project with an FPGA, but I don't have much knowledge of FPGA's, so this project is written in C/C++ with the Arduino library included. Due to the incredible number of I/O, three Teensy microcontrollers are currently implemented, two Teensy 4.0's for I/O drivers (32 motors each), and one Teensy 4.1 for the 'main brain'. 

# Concetual initial design
General layout thoughts for such a large number of stepper motors and how to control them. Revision A is mostly based off of Concept #3.

<img src="https://github.com/Ohm-Slah/64-Stepper-Motor-Controller/blob/main/DOCUMENTS/FOR%20README/Screenshot%202022-05-12%20131638.png" alt="conceptual" width="400"/><img src="https://github.com/Ohm-Slah/64-Stepper-Motor-Controller/blob/main/DOCUMENTS/FOR%20README/Screenshot%202022-05-12%20131719.png" alt="PCB Layout" width="400"/><img src="https://github.com/Ohm-Slah/64-Stepper-Motor-Controller/blob/main/DOCUMENTS/FOR%20README/Screenshot%202022-05-12%20131742.png" alt="PCB Layout" width="400"/><img src="https://github.com/Ohm-Slah/64-Stepper-Motor-Controller/blob/main/DOCUMENTS/FOR%20README/Screenshot%202022-06-15%20123522.png" alt="PCB Layout" width="400"/>

# Revision A
This design is an attempt to create a fairly modular assembly for 64 stepper motor control. Each A4988 stepper driver can be extracted or replaced if neccessary. Eight total A4988 stepper drivers can be placed onto a single driver 'card'. These are designed to be edge-card connected to a larger board, the 32-stepper board. This board holds four driver cards, totalling to 32 stepper motors. There are 2 of these boards to total 64 motor drivers, with each having 20 74HC595 shift registers for I/O management, and visual indicator LED's for all outputs of the shift registers. Power is supplied to this board via a high-current connector. Both of these 32-stepper boards are then connected to a 'main board' containing the 3 microcontrollers, LED strip connections, and USB connection. 

## 8 Stepper PCB Card
<img src="https://github.com/Ohm-Slah/64-Stepper-Motor-Controller/blob/main/DOCUMENTS/FOR%20README/Screenshot%202022-06-15%20122505.png" alt="PCB design rev A" width="400"/><img src="https://github.com/Ohm-Slah/64-Stepper-Motor-Controller/blob/main/DOCUMENTS/FOR%20README/Screenshot%202022-06-15%20123018.png" alt="PCB 3D model rev A" width="400"/>

## 32 Stepper PCB Board
<img src="https://github.com/Ohm-Slah/64-Stepper-Motor-Controller/blob/main/DOCUMENTS/FOR%20README/Screenshot%202022-06-15%20124324.png" alt="PCB 3D model rev A" width="400"/><img src="https://github.com/Ohm-Slah/64-Stepper-Motor-Controller/blob/main/DOCUMENTS/FOR%20README/Screenshot%202022-06-16%20101221.png" alt="PCB 3D model rev A" width="400"/>

## 64 Stepper PCB Board
