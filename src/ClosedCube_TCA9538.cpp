/*

Arduino Library for Texas Instruments Remote 8-Bit I2C and SMBus Low-Power I/O Expander
Written by AA for ClosedCube
---

Copyright (c) 2015-2018, ClosedCube
All rights reserved.

Redistribution and use in source and binary forms, with or without 
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, 
   this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, 
   this list of conditions and the following disclaimer in the documentation and/or 
   other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors 
   may be used to endorse or promote products derived from this software
   without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

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
