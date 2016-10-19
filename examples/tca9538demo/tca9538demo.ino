/*

This is example for Texas Instruments TCA9538 Remote 8-Bit I2C and SMBus Low-Power I/O Expander Arduino Library
ClosedCube TCA9538 8-bit I2C Low-Power I/O Expander breakout module

Written by AA for ClosedCube

Initial Date: 19-Oct-2016

Hardware connections for Arduino Uno:
VDD to 3.3V DC
SDA to A4
SCL to A5
GND to common ground

MIT License

*/

#include "ClosedCube_TCA9538.h"
#include <Wire.h>

ClosedCube_TCA9538 tca9538;

#define TCA9538_ADDRESS 0x70

void setup()
{
	Serial.begin(9600);
	Serial.println("ClosedCube TCA9538 Arduino Test");

	tca9538.begin(TCA9538_ADDRESS);
}

void loop()
{

}

