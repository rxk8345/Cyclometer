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

//segments for anode 0
int Anode0;
int Anode1;
int Anode2;
int Anode3;

bool Anode0Dec = false;
bool Anode1Dec = false;
bool Anode2Dec = false;
bool Anode3Dec = false;

bool Led2 = false; //miles
bool Led1 = false; //start/stop
bool Led0 = false; // rotation

int ledMask = 0;

pthread_t ledThread;

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

	if(pthread_create(&ledThread, NULL, &runLedThread, NULL) == -1){
		std::cout << "Failed to create Led Thread\n" << std::endl;
	}


	// testing LEDs
	//out8(portA, (0b00000000));

	// testing 7 segment display
	// bit0 - right most display
	//out8(portB, (0x00));
	//out8(portA, 0b00001110);
	//out8(portB, 0b10100100);

	//out8(portA, 0b00001100);
	//out8(portB, 0b10110000);


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

event lastEvent;

event pollInputs(){

	// testing pushbuttons
	int input = in8(portC);
	event returnEvent = NAE;
	if( input == 127 ){
		std::cout << "Reset Button Pressed\n" << std::endl;
		returnEvent = Reset;
	}else if(input & MBMASK){
		std::cout << "Mode Button Pressed\n" << std::endl;
		returnEvent = Mode;
	}
	else if(input & SSMASK){
		std::cout << "Start/Stop Button Pressed\n" << std::endl;
		returnEvent = Start_Stop;
	}
	else if(input & SBMASK){
		std::cout << "Set Button Pressed\n" << std::endl;
		returnEvent = Set;
	}
	else{
		//std::cout << "Unknown/No Button Pressed\n" << std::endl;
		returnEvent= NAE;
	}

	return returnEvent;
}

void setDecimalAnode0( bool b ){
	Anode0Dec = b;
}

void setDecimalAnode1( bool b ){
	Anode1Dec = b;
}
void setDecimalAnode2( bool b ){
	Anode2Dec = b;
}
void setDecimalAnode3( bool b ){
	Anode3Dec = b;
}

//3 --> 10110000
void setAnode0(int i){
	int temp = intToSegment(i);
	if(Anode0Dec){
		temp = temp & 0b01111111;
	}
	Anode0 = temp;
}

void setAnode1(int i){
	int temp = intToSegment(i);
	if(Anode1Dec){
		temp = temp & 0b01111111;
	}
	Anode1 = temp;
}

void setAnode2(int i){
	int temp = intToSegment(i);
	if(Anode2Dec){
		temp = temp & 0b01111111;
	}
	Anode2 = temp;
}

void setAnode3(int i){
	int temp = intToSegment(i);
	if(Anode3Dec){
		temp = temp & 0b01111111;
	}
	Anode3 = temp;
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
		return 0b11111111;

	}
}

void clearDisplay(){
	usleep(500);
	// Anodes (0 is on, 1 is off);
	out8(portA, (ledMask | 0b00001111));
	// clear the 7-segment display (1 is off, 0 is on)
	out8(portB, (0xFF));
	Anode0Dec = false;
	Anode1Dec = false;
	Anode2Dec = false;
	Anode3Dec = false;
}

void * runDisplay( void * dummy){
	setUpHardware();

	while(1){

		//first digit
		out8(portA, 0b00000111 | ledMask ); // anodes
		out8(portB, Anode0); // segments
		clearDisplay();

		//second digit
		out8(portA, 0b00001011 | ledMask );
		out8(portB, Anode1);
		clearDisplay();

		//third digit
		out8(portA, 0b00001101 | ledMask);
		out8(portB, Anode2);
		clearDisplay();

		//fourth digit
		out8(portA, 0b00001110 | ledMask);
		out8(portB, Anode3);
		clearDisplay();


	}
	return dummy;
}

void * runLedThread(void * dummy){

	while(1){
		if(Led2){
			ledMask |= 0b10000000;
		}

		if(Led1){
			ledMask |= 0b01000000;
		}

		if(Led0){
			ledMask |= 0b00100000;
		}
		sleep(0.5);

		if(Led2){ //keep miles light on
			ledMask = 0b10000000;
		}else{
			ledMask = 0;
		}

		sleep(0.5);
	}
	return dummy;
}

void setWheelRotationLEDOn(){
	Led0 = true;
}

void setWheelRotationLEDOff(){
	Led0 = false;
}

void setMeasurementUnitLEDOn(){
	//on for miles, off for km
	Led2 = true;
}

void setMeasurementUnitLEDOff(){
	//on for miles, off for km
	Led2 = false;
}

void setStartStopLEDOn(){
	Led1 = true;
}

void setStartStopLEDOff(){
	Led1 = false;
}
