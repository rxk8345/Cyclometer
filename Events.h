/*
 * Events.h
 *
 *  Created on: May 9, 2015
 *      Author: rxk8345
 */

#ifndef EVENTS_H_
#define EVENTS_H_

typedef enum {
	NAE,
	SetTire,
	Set,
	Reset,
	ToggleMode,
	Start_Stop,
	Increase,
	Sensor,
	Calculate_Event
} event;
typedef enum {
	Set_Unit,
	Set_Tire_Circ,
	Automatic,
	Manual,
	Change_Circ,
	Calculate_State,
	Cal_Speed,
	Cal_Distance,
	Cal_Time,

} state;


typedef enum {
	autoMode,
	manualMode,
	notSet
} modeEnum;
#endif /* EVENTS_H_ */
