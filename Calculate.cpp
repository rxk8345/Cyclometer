/*
 * Calculate.cpp
 *
 *  Created on: May 10, 2015
 *      Author: rxk8345
 */

#include "Calculate.h"

double averageSpeed;
double currentSpeed;
int elapsedTime;
double totalDistance;

double averageSpeedMPH;
double currentSpeedMPH;
double averageSpeedKMPH;
double currentSpeedKMPH;

double totalDistanceM;
double totalDistanceKM;

extern int units;
extern bool calculateIsOn;
extern bool displayCalc;
extern pthread_t displayThread;
extern pthread_t displayModeThread;
extern StateWalker* currentWalker;



pthread_t timerThread;

void initCalculations(){

	timerThread = pthread_create(&timerThread, NULL, &calcTimer, NULL);

}

void * calcTimer( void * dummy){
	for(;;){
		sleep(2);
		if(calculateIsOn){
			performCalculations();
		}else{
			setStartStopLEDOff();
		}
	}
	return dummy;
}

void resetCalculations(){
	units = 1;
	averageSpeed = 0;
	currentSpeed = 0;
	elapsedTime = 0;
	totalDistance = 0;
	calculateIsOn = false;
	displayCalc = false;
}

void performCalculations(){

	int sensorCount = sensor.getCount();
	if( sensorCount == 0 &&  currentWalker->is_in() == Automatic){
		setWheelRotationLEDOff();
		setStartStopLEDOff();
		return;
	}
	setStartStopLEDOn();

	elapsedTime += 1;
	//std::cout << "sensorcount: " << sensorCount<< std::endl;
	// cm/s
	totalDistance += tireSize * sensorCount;
	//std::cout << "totalDistance: " << totalDistance<< std::endl;
	averageSpeed = totalDistance / elapsedTime;
	//std::cout << "averageSpeed: " << averageSpeed<< std::endl;
	currentSpeed = (tireSize * sensorCount);

	if( units == 2 ) { //mph
		averageSpeedMPH = averageSpeed * (0.0223693629);
		currentSpeedMPH = currentSpeed * (0.0223693629);
		totalDistanceM = totalDistance * (0.00000621371);
		//std::cout << "Average Speed: " << averageSpeedMPH << " mph" << std::endl;
		//std::cout << "Current Speed: " << currentSpeedMPH << " mph" << std::endl;
		//std::cout << "Total Distance: " << totalDistanceM << " m"  << std::endl;
		//std::cout << std::endl;

	}else if( units == 1){ //km/h
		averageSpeedKMPH = averageSpeed * (0.036);
		currentSpeedKMPH = currentSpeed * (0.036);
		totalDistanceKM = totalDistance * (0.00001);
//		std::cout << "Average Speed: " << averageSpeedKMPH << " km/h" << std::endl;
//		std::cout << "Current Speed: " << currentSpeedKMPH << " km/h" << std::endl;
//		std::cout << "Total Distance: " << totalDistanceKM << " km"  << std::endl;
//		std::cout << std::endl;
	}

}
