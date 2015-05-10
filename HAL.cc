/*
 * HAL.cc
 *
 *  Created on: May 10, 2015
 *      Author: rxk8345
 */

#include "HAL.h"

uintptr_t portA;
uintptr_t portB;
uintptr_t portC;
uintptr_t controlPort ;

int Anode0;
int Anode1;
int Anode2;
int Anode3;

void setUpHardware(){
	int privity_err;
	// give thread root permissions to access the hardware
	privity_err = ThreadCtl( _NTO_TCTL_IO, NULL);

	if(privity_err == -1){
		std::cout << "Can't get root permissions\n" << std::endl;
	}

	controlPort = mmap_device_io(1, DIOCR);
	// set the direction of Digital I/O
	out8(controlPort, DIRC);

	// map the ports to pointers
	portA = mmap_device_io(1, PORTA);
	portB = mmap_device_io(1, PORTB);
	portC = mmap_device_io(1, PORTC);

	// LEDs (0 is off, 1 is on)
	// Anodes (0 is on, 1 is off);
	out8(portA, (0x00));
	// clear the 7-segment display (1 is off, 0 is on)
	out8(portB, (0xFF));
	sleep(1);

	// testing LEDs
	//out8(portA, (0b00000000));

	// testing 7 segment display
	// bit0 - right most display
	//out8(portB, (0x00));
	//out8(portA, 0b00001110);
	//out8(portB, 0b10100100);

	//out8(portA, 0b00001100);
	//out8(portB, 0b10110000);


	// testing pushbuttons
	int input = in8(portC);
	if(input & MBMASK){
		std::cout << "Mode Button Pressed\n" << std::endl;
	}
	else if(input & SSMASK){
		std::cout << "Start/Stop Button Pressed\n" << std::endl;
	}
	else if(input & SBMASK){
		std::cout << "Set Button Pressed\n" << std::endl;
	}
	else{
		std::cout << "Unknown/No Button Pressed\n" << std::endl;
	}


	//testing anodes display

	/*
	int seg;
	for(int i = 0; i < 10; i++){
		seg = intToSegment(i);
		out8(portA, 0b00001110);
		out8(portB, seg);
		sleep(1);
	}*/

}

//3 --> 10110000
void setAnode0(int i){
	Anode0 = intToSegment(i);
}

void setAnode1(int i){
	Anode1 = intToSegment(i);
}

void setAnode2(int i){
	Anode2 = intToSegment(i);
}

void setAnode3(int i){
	Anode3 = intToSegment(i);
}

int intToSegment(int i){
	switch(i){
	case 0:
		return 0b11000000;
	case 1:
		return 0b11111001;
	case 2:
		return 0b10100100;
	case 3:
		return 0b10110000;
	case 4:
		return 0b10011001;
	case 5:
		return 0b10010010;
	case 6:
		return 0b10000010;
	case 7:
		return 0b11111000;
	case 8:
		return 0b10000000;
	case 9:
		return 0b10010000;
	default:
		return 0b11000000;

	}
}

void clearDisplay(){
	usleep(500);
	// Anodes (0 is on, 1 is off);
	out8(portA, (0x0F));
	// clear the 7-segment display (1 is off, 0 is on)
	out8(portB, (0xFF));
}

void runDisplay(){
	setUpHardware();
	setAnode0(1);
	setAnode1(2);
	setAnode2(3);
	setAnode3(4);

	while(1){
		//first digit
		out8(portA, 0b00000111);
		out8(portB, Anode0);
		clearDisplay();

		//second digit
		out8(portA, 0b00001011);
		out8(portB, Anode1);
		clearDisplay();

		//third digit
		out8(portA, 0b00001101);
		out8(portB, Anode2);
		clearDisplay();

		//fourth digit
		out8(portA, 0b00001110);
		out8(portB, Anode3);
		clearDisplay();
	}

}

