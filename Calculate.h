/*
 * Calculate.h
 *
 *  Created on: May 10, 2015
 *      Author: rxk8345
 */

#ifndef CALCULATE_H_
#define CALCULATE_H_


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
#include "WheelSensor.h"
#include "HAL.h"
#include "StateWalker.h"

extern WheelSensor sensor;
extern int tireSize;


void initCalculations();
void resetCalculations();
void * calcTimer( void * dummy);
void performCalculations();

#endif /* CALCULATE_H_ */
