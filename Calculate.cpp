/*
 * Calculate.cpp
 *
 *  Created on: May 10, 2015
 *      Author: rxk8345
 */

#include "Calculate.h"

int startTime;

void init(){
	struct timespec start;

	if( clock_gettime( CLOCK_REALTIME, &start) == -1){
		//it failed
		std::cout << "Clock Failed" << std::endl;
	}

	std::cout << "Clock Worked" << std::endl;
	std::cout << start.tv_sec << std::endl;
	startTime = start.tv_sec;
}

void addReading(){

	struct timespec start;

	if( clock_gettime( CLOCK_REALTIME, &start) == -1){
		//it failed
		std::cout << "Clock Failed" << std::endl;
	}

	std::cout << "Clock Worked" << std::endl;
	int curr = start.tv_sec;
	std::cout << curr - startTime << std::endl;

	//add reading to queue
}
