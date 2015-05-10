/*
 * Display.cpp
 *
 *  Created on: May 10, 2015
 *      Author: rxk8345
 */

int displayMode = 0;

void toggleDisplay(){
	displayMode++;
	displayMode = displayMode % 3;
}

