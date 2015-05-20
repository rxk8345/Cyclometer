/*
 * WheelSensor.cpp
 *
 *  Created on: Feb 4, 2013
 *      Author: rfd6477
 *
 *      Description: The wheel sensor class monitors
 *      the DIO port 25 and handles the interrupts.
 *      When an interrupt occurs the pulse count variable
 *      is incremented and stored for others to retrieve.
 */

#include "WheelSensor.h"

extern bool calculateIsOn;

WheelSensor::WheelSensor() {
	int privity_err;
	uintptr_t ctrl_handle;
	uintptr_t clear_handle;

	privity_err = ThreadCtl( _NTO_TCTL_IO, NULL );
	if ( privity_err == -1)
	{
		printf( "Can't get root permissions\n");
	}

	// Get a handle to Interrupt Control Register
	ctrl_handle = mmap_device_io( PORT_LENGTH, CTRL_ADDRESS );
	clear_handle = mmap_device_io( PORT_LENGTH, CLEAR_ADDRESS );

	if ( ctrl_handle == MAP_DEVICE_FAILED ) {
		perror( "control map failed" );

	}

	out8( ctrl_handle, INIT_BIT );
	out8( clear_handle, CLEAR );

	_pulseHist = 0;
}

WheelSensor::~WheelSensor() {
	// TODO Auto-generated destructor stub
}

/* Starts the thread. This is the function that should be called
 * by pthread_create */
void * startWheelSensor(void * sensor)
{
	((WheelSensor *)sensor)->run();
	return NULL;
}

/* Runs the logic for the Wheel Sensor */
void  WheelSensor::run()
{
	_interruptID = InterruptAttach(DIO_IRQ, interruptReceived, this, sizeof(this), 0);
	if (_interruptID == -1) {
		fprintf(stderr, "can't attach to IRQ %d\n", DIO_IRQ);
		perror(NULL);
	}

	for(;;){
		sleep(1);
		if (_pulseCount != _pulseHist)
		{
			_pulseHist = _pulseCount;
		}
		_pulseCount = 0;
	}
}

int WheelSensor::getCount()
{
	return _pulseHist;
}

void WheelSensor::updateCount()
{
	if(calculateIsOn){
		_pulseCount++;
	}
}

const struct sigevent * interruptReceived(void *arg, int id)
{
	uintptr_t clear_handle;
	clear_handle = mmap_device_io( PORT_LENGTH, CLEAR_ADDRESS );

	((WheelSensor *)arg)->updateCount();
	out8( clear_handle, CLEAR );
	setWheelRotationLEDOn();
	return NULL;
}

