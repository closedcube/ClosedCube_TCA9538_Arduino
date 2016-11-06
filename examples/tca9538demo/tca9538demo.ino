/*

This is example for Texas Instruments Remote TCA9538 8-Bit I2C and SMBus Low-Power I/O Expander Arduino Library
ClosedCube TCA9538 Remote 8-bit I2C Low-Power I/O Expander breakout module

Written by AA for ClosedCube

Initial Date: 19-Oct-2016

Hardware connections for Arduino Uno:
VDD to 3.3V DC
SDA to A4
SCL to A5
GND to common ground
P0 to Pin 13 to be defined as Output
P7 to Pin 7 to be defined as Input

TCA9538		 	P0  (Input)		P7 (Output)
Arduino Uno		13	(Output)	7 (Input)

MIT License

*/

#include "ClosedCube_TCA9538.h"
#include <Wire.h>

#define TCA9538_ADDRESS 0x70

#define INPUT_PIN	7
#define OUTPUT_PIN	13

ClosedCube_TCA9538 tca9538;
TCA9538_Registers regs;

int val = 0;

void setup()
{
	Serial.begin(9600);
	Serial.println("ClosedCube TCA9538 Arduino Test");
	
	pinMode(OUTPUT_PIN, OUTPUT);
	pinMode(INPUT_PIN, INPUT);

	tca9538.begin(TCA9538_ADDRESS);

	regs.output.rawData = 0xFF;
	regs.polarity.rawData = 0x00;
	regs.input.rawData = 0x00;
	regs.config.rawData = 0xFF;

	regs.config.ports.P7= 0;

	tca9538.init(regs);
}

void loop() {
	val = ~val; 

	digitalWrite(OUTPUT_PIN, val); // Arduino Output pin

	printHeader();

	printHighOrLow(val);
	Serial.print("\t\t");

	TCA9538_Input input = tca9538.readInput(); // TCA9538 Input P0 pin
	printHighOrLow(input.ports.P0);
	Serial.print("\t\t\t");
	
	regs.output.ports.P7 = ~regs.output.ports.P7; // TCA9538 Output P7 pin
	tca9538.writeOutput(regs.output);
	printHighOrLow(tca9538.readOutput().ports.P7); 
	Serial.print("\t\t");

	printHighOrLow(digitalRead(INPUT_PIN)); // Arduino Input pin
	Serial.println();

	Serial.println();
	delay(3000);
}


void printHighOrLow(int val) {
	if (val)
		Serial.print("HIGH");
	else
		Serial.print("LOW");
}

void printHeader() {
	Serial.println("Arduino\t\tTCA9538\t\t\tTCA9538\t\tArduino");
	Serial.print("Pin ");
	Serial.print(OUTPUT_PIN);
	Serial.print(" Out\tP0 In\t\t\tP7 Out\t\tPin ");
	Serial.print(INPUT_PIN);
	Serial.println(" In");
}