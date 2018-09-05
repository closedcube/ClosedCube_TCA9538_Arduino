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

#ifndef _CLOSEDCUBE_TCA9538_h

#define _CLOSEDCUBE_TCA9538_h
#include <Arduino.h>

typedef enum {
	TCA9538_INPUT_PORT = 0x00,
	TCA9538_OUTPUT_PORT = 0x01,
	TCA9538_POLARITY_INVERSION = 0x02,
	TCA9538_CONFIG = 0x03,
} TCA9538_Commands;


struct TCA9538_Ports {
	uint8_t P0 : 1;
	uint8_t P1 : 1;
	uint8_t P2 : 1;
	uint8_t P3 : 1;
	uint8_t P4 : 1;
	uint8_t P5 : 1;
	uint8_t P6 : 1;
	uint8_t P7 : 1;
};

union TCA9538_Input {
	uint8_t rawData;
	struct TCA9538_Ports ports;
};

union TCA9538_Output {
	uint8_t rawData;
	struct TCA9538_Ports ports;
};

union TCA9538_PolarityInversion {
	uint8_t rawData;
	struct TCA9538_Ports ports;
};

union TCA9538_Config {
	uint8_t rawData;
	struct TCA9538_Ports ports;
};

typedef struct {
	union TCA9538_Input input;
	union TCA9538_Output output;
	union TCA9538_PolarityInversion	polarity;
	union TCA9538_Config config;
} TCA9538_Registers;

class ClosedCube_TCA9538 {
public:
	ClosedCube_TCA9538();

	void begin(uint8_t address);
	void init(TCA9538_Registers regs);

	TCA9538_Input readInput();

	void writePolarity(TCA9538_PolarityInversion polarity);
	
	void writeOutput(TCA9538_Output output);
	TCA9538_Output readOutput();

	void writeConfig(TCA9538_Config config);

private:

	uint8_t writeData(TCA9538_Commands cmd, uint8_t rawData);
	uint8_t _address;
};

#endif

