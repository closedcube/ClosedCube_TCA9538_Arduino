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

#ifndef _CLOSEDCUBE_TCA9538_h

#define _CLOSEDCUBE_TCA9538_h
#include <Arduino.h>

typedef enum {
	TCA9538_INPUT_PORT			= 0x00,
	TCA9538_OUTPUT_PORT			= 0x01,
	TCA9538_POLARITY_INVERSION	= 0x02,
	TCA9538_CONFIG				= 0x03,
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

