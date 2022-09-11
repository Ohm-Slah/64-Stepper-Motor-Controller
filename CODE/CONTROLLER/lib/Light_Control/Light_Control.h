/*
 * File name: Light_Control.h -> CONTROLLER
 * Project: 64 Motor Driver
 * Author: Elliot Eickholtz
 * Purpose: Lighting control library.
 * 
*/

#pragma once
#include <OctoWS2811.h>

// Any group of digital pins may be used
const int numPins = 3;
byte pinList[numPins] = {1, 2, 3};//, 2, 3, 4, 5, 6, 7, 8};

const uint8_t boxRows = 8;
const uint8_t boxColumns = 8;

const int ledsPerStrip = 32;

// These buffers need to be large enough for all the pixels.
// The total number of pixels is "ledsPerStrip * numPins".
// Each pixel needs 3 bytes, so multiply by 3.  An "int" is
// 4 bytes, so divide by 4.  The array is created using "int"
// so the compiler will align it to 32 bit memory.
const int bytesPerLED = 3;  // change to 4 if using RGBW
DMAMEM int displayMemory[ledsPerStrip * numPins * bytesPerLED / 4];
int drawingMemory[ledsPerStrip * numPins * bytesPerLED / 4];

const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config, numPins, pinList);

unsigned int h2rgb(unsigned int v1, unsigned int v2, unsigned int hue)
{
	if (hue < 60) return v1 * 60 + (v2 - v1) * hue;
	if (hue < 180) return v2 * 60;
	if (hue < 240) return v1 * 60 + (v2 - v1) * (240 - hue);
	return v1 * 60;
}

int makeColor(unsigned int hue, unsigned int saturation, unsigned int lightness)
{
	unsigned int red, green, blue;
	unsigned int var1, var2;

	if (hue > 359) hue = hue % 360;
	if (saturation > 100) saturation = 100;
	if (lightness > 100) lightness = 100;

	// algorithm from: http://www.easyrgb.com/index.php?X=MATH&H=19#text19
	if (saturation == 0) {
		red = green = blue = lightness * 255 / 100;
	} else {
		if (lightness < 50) {
			var2 = lightness * (100 + saturation);
		} else {
			var2 = ((lightness + saturation) * 100) - (saturation * lightness);
		}
		var1 = lightness * 200 - var2;
		red = h2rgb(var1, var2, (hue < 240) ? hue + 120 : hue - 240) * 255 / 600000;
		green = h2rgb(var1, var2, hue) * 255 / 600000;
		blue = h2rgb(var1, var2, (hue >= 120) ? hue - 120 : hue + 240) * 255 / 600000;
	}
	return (red << 16) | (green << 8) | blue;
}

uint16_t gridToLed(uint8_t x, uint8_t y)
{
    return ((y % 2) ? (boxColumns * 2 - x - 1) : x) + (y * boxRows * 2);
    // return ((row - (ledNumber < 3 ? 0 : 1)) * (boxRows*2)) + (ledNumber < 3 ? (boxColumns*2 - column) : ((column-1)*2));
}

void changeBoxColor(uint8_t box_x, uint8_t box_y, uint32_t color)
{
    if(box_x > boxRows || box_y > boxColumns) 
    {
        Serial.println("changeBoxColor() outside maximum matrix size.");
        return;
    }
    uint8_t actual_x = (box_x - 1) * 2;
    uint8_t actual_y = (box_y - 1) * 2;

    // Serial.print(actual_x);Serial.print(" : ");Serial.println(actual_y);
    // Serial.print(actual_x+1);Serial.print(" : ");Serial.println(actual_y);
    // Serial.print(actual_x);Serial.print(" : ");Serial.println(actual_y+1);
    // Serial.print(actual_x+1);Serial.print(" : ");Serial.println(actual_y+1);

    leds.setPixel(gridToLed(actual_x, actual_y), color);
    leds.setPixel(gridToLed(actual_x+1, actual_y), color);
    leds.setPixel(gridToLed(actual_x, actual_y+1), color);
    leds.setPixel(gridToLed(actual_x+1, actual_y+1), color);
    leds.show();
}

void changeSegmentColor(uint8_t x, uint8_t y, uint32_t color)
{
    if(x > boxRows || y > boxColumns) 
    {
        Serial.println("changeSegmentColor() outside maximum matrix size.");
        return;
    }
    leds.setPixel(gridToLed(x, y), color);
    leds.show();
}
