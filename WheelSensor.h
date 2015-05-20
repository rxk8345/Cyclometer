/*
 * WheelSensor.h
 *
 *  Created on: Feb 4, 2013
 *      Author: rfd6477
 */

#ifndef WHEELSENSOR_H_
#define WHEELSENSOR_H_

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <hw/inout.h>
#include <time.h>
#include <stdint.h>
#include <sys/neutrino.h>
#include <sys/mman.h>
#include "HAL.h"

#define PORT_LENGTH     1  /* single register */

/* Define the addresses for ports C, B and their control register*/
#define BASE 0x280

#define CTRL_ADDRESS  BASE + 4
#define CLEAR_ADDRESS BASE + 0

#define INIT_BIT       0x02
#define CLEAR          0x02
#define DIO_IRQ        0x05 /* parallel port’s interrupt vector */

void * startWheelSensor(void *);

const struct sigevent * interruptReceived(void *arg, int id);

class WheelSensor {
public:
	WheelSensor();
	virtual ~WheelSensor();

	/* Run this thread */
	void run();

	int getCount();

	void updateCount();

private:

	int _pulseCount;
	int _pulseHist;
	int _interruptID;
};

#endif /* WHEELSENSOR_H_ */
