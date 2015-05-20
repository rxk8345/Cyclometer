/*
 * Display.cpp
 *
 *  Created on: May 10, 2015
 *      Author: rxk8345
 */
#include "Display.h"

extern int elapsedTime;

extern double averageSpeedMPH;
extern double currentSpeedMPH;
extern double averageSpeedKMPH;
extern double currentSpeedKMPH;

extern double totalDistanceM;
extern double totalDistanceKM;

extern int units;

extern int displayMode;
bool displayCalc = false;
pthread_t displayThread;
pthread_t displayModeThread;

void startDisplayThread(){

	//HARDWARE INTERFACE THREAD
	if( pthread_create(&displayThread, NULL, &runDisplay, NULL) == -1){
		std::cout << "Failed to create runDisplay thread" << std::endl;
	}

	//Update display thread (speed, distance, time)
	if( pthread_create(&displayModeThread, NULL, &runDisplayMode, NULL) == -1){
		std::cout << "Failed to create runDisplay thread" << std::endl;
	}
}

void * runDisplayMode( void * dummy ){
	for(;;){
		sleep(1);
		if( displayCalc ){
			displayCalculations();
		}
	}
}

void setDisplayCalc(bool b){
	displayCalc = b;
}

void toggleDisplay(){
	int temp = displayMode + 1;
	temp = temp % 3;
	displayMode = temp;
	clearDisplay();
	if(displayMode == 0){
		displaySpeed();
	}else if(displayMode == 1){
		displayDistance();
	}else if(displayMode == 2){
		displayTime();
	}
}

void displayNumbers( int a, int b, int c, int d){
	setAnode0(a);
	setAnode1(b);
	setAnode2(c);
	setAnode3(d);

}

double getCurrentSpeed(){
	if( units == 1){
		return currentSpeedKMPH;
	}else{
		return currentSpeedMPH;
	}
}

double getAverageSpeed(){
	if( units == 1){
		return averageSpeedKMPH;
	}else{
		return averageSpeedMPH;
	}
}

double getTotalDistance(){
	if( units == 1){
		return totalDistanceKM;
	}else{
		return totalDistanceM;
	}
}

void displayCalculations(){

	switch(displayMode){
	case 0:
		displaySpeed();
		break;
	case 1:
		displayDistance();
		break;
	case 2:
		displayTime();
		break;
	default:
		displayNumbers(-1,-1,-1,-1);
		break;
	}

}

void displaySpeed(){
	int a,b,c,d;

	double currSpeed = getCurrentSpeed();
	double averSpeed = getAverageSpeed();
	//current speed in left most
	if(currSpeed >= 100){
		// only allow display two digits, display 99
		a = 9;
		b = 9;
	}else if(currSpeed > 10 ){
		// no decimal pt
		a = currSpeed / 10;
		setDecimalAnode0(false);
		b = (currSpeed - a * 10);
	}else{
		//1 digit + decimal
		a = currSpeed;
		setDecimalAnode0(true);
		b = (currSpeed * 10 ) - (a * 10);
	}

	if(averSpeed >= 100){
		// only allow display two digits, display 99
		c = 9;
		d = 9;
	}else if(averSpeed > 10 ){
		// no decimal pt
		c = averSpeed / 10;
		setDecimalAnode2(false);
		d = (averSpeed - c * 10);
	} else{
		//1 digit + decimal
		c = averSpeed;
		setDecimalAnode2(true);
		d = (averSpeed * 10 ) - (c * 10);
	}

	displayNumbers(a,b,c,d);
}

void displayDistance(){
	int a,b,c,d;

	double totalDis = getTotalDistance();

	if(totalDis >= 1000 ){
		// only allow display four digits, max display 9999
		a = 9;
		b = 9;
		c = 9;
		setDecimalAnode2(true);
		d = 9;
	}else{
		//3 digit + decimal
		a = totalDis / 100;
		b = (totalDis - a * 100) / 10;
		c = (totalDis - a * 100 - b * 10);
		setDecimalAnode2(true);
		d = (totalDis - a * 100 - b * 10 - c) * 10;
	}

	displayNumbers(a,b,c,d);
}

void displayTime(){
	int a,b,c,d;

	int elapsedTimeMin;
	int elapsedTimeSec;
	elapsedTimeMin = elapsedTime / 60;
	a = elapsedTimeMin / 10;
	b = elapsedTimeMin % 10;
	setDecimalAnode1(true);

	elapsedTimeSec = elapsedTime % 60;
	c = elapsedTimeSec / 10;
	d = elapsedTimeSec % 10;
	displayNumbers(a,b,c,d);
}

