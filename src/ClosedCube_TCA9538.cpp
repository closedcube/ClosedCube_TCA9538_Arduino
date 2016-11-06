/*

Arduino Library for Texas Instruments Remote 8-Bit I2C and SMBus Low-Power I/O Expander
Written by AA for ClosedCube
---

The MIT License (MIT)

Copyright (c) 2016 ClosedCube Limited

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#include <Wire.h>

#include "ClosedCube_TCA9538.h"


ClosedCube_TCA9538::ClosedCube_TCA9538()
{
}

void ClosedCube_TCA9538::begin(uint8_t address) {
	_address = address;
	Wire.begin();

}

TCA9538_Input ClosedCube_TCA9538::readInput() {
	Wire.beginTransmission(_address);
	Wire.write(TCA9538_INPUT_PORT);
	Wire.endTransmission();

	Wire.requestFrom(_address, (uint8_t)1);
	TCA9538_Input input;
	input.rawData = Wire.read();

	return input;
}


void ClosedCube_TCA9538::writePolarity(TCA9538_PolarityInversion polarity) {
	writeData(TCA9538_POLARITY_INVERSION, polarity.rawData);
}

void ClosedCube_TCA9538::writeOutput(TCA9538_Output output) {
	writeData(TCA9538_OUTPUT_PORT, output.rawData);
}

TCA9538_Output ClosedCube_TCA9538::readOutput() {
	Wire.beginTransmission(_address);
	Wire.write(TCA9538_OUTPUT_PORT);
	Wire.endTransmission();

	Wire.requestFrom(_address, (uint8_t)1);
	TCA9538_Output input;
	input.rawData = Wire.read();

	return input;
}


void ClosedCube_TCA9538::writeConfig(TCA9538_Config config) {
	writeData(TCA9538_CONFIG, config.rawData);
}

void ClosedCube_TCA9538::init(TCA9538_Registers regs) {	
	writeConfig(regs.config);
	writeOutput(regs.output);
	writePolarity(regs.polarity);
}

uint8_t ClosedCube_TCA9538::writeData(TCA9538_Commands cmd, uint8_t rawData) {
	Wire.beginTransmission(_address);
	Wire.write(cmd);
	Wire.write(rawData);
	return Wire.endTransmission();
}
