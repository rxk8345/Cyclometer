/*
 * Display.h
 *
 *  Created on: May 10, 2015
 *      Author: rxk8345
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "HAL.h"

#include <pthread.h>
#include "Calculate.h"

double getCurrentSpeed();
double getAverageSpeed();
void displayCalculations();
void startDisplayThread();
void toggleDisplay();
void displayNumbers( int a, int b, int c, int d);
void setDisplayCalc(bool b);
void * runDisplayMode( void * dummy );
double getTotalDistance();
void displaySpeed();
void displayDistance();
void displayTime();


#endif /* DISPLAY_H_ */
