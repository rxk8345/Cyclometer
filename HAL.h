/*
 * HAL.h
 *
 *  Created on: May 10, 2015
 *      Author: rxk8345
 */

#ifndef HAL_H_
#define HAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include "Events.h"
#include <hw/inout.h>
#include <sys/mman.h>
#include <sys/iofunc.h>
#include <stdint.h>
#include <unistd.h>

#define DAQBASEADDR	0x280	//base address
#define DIOCR		0x28B	//digital i/o control register
#define PORTA		0x288	//port A (output from QNX)
#define PORTB		0x289	//port B (output from QNX)
#define PORTC		0x28A 	//port C (input from QNX)

#define DIRB	0b00000000	// bit2 = 0 for output
#define DIRA	0b00000000	// bit5 = 0 for output
#define DIRC	0b00000001  // last bit = 1 for input

// push button masks
#define MBMASK	0b00000001 	// mode button mask
#define SSMASK	0b00000010	// start/stop button mask
#define SBMASK	0b00000100	// set button mask


void setUpHardware();
void setDecimalAnode0(bool b);
void setDecimalAnode1(bool b);
void setDecimalAnode2(bool b);
void setDecimalAnode3(bool b);

void setAnode0(int i);
void setAnode1(int i);
void setAnode2(int i);
void setAnode3(int i);

int intToSegment(int i);
void clearDisplay();
void * runDisplay( void * dummy);
event pollInputs();

void setWheelRotationLEDOn();
void setWheelRotationLEDOff();
void setMeasurementUnitLEDOn();
void setMeasurementUnitLEDOff();
void setStartStopLEDOn();
void setStartStopLEDOff();
void * runLedThread(void * dummy);

#endif /* HAL_H_ */
