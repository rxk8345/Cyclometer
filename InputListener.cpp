/*
 * InputListener.cpp
 *
 *  Created on: May 19, 2015
 *      Author: xxz1530
 */

#include "InputListener.h"

extern StateWalker* currentWalker;

//*****************Polling Thread
//The polling thread listens for input type events and sends them to the state machine controller thread(main)
void* PollingThread(void* args){
	//Seting up the channel to send events to
	std::cout << "Polling Thread has started\n" << std::endl;
	Message sendingMessage;
	Message replyMessage;
	sendingMessage.hdr.type = 0 ;
	sendingMessage.hdr.subtype = 0 ;
	sendingMessage.triggerEvent = NAE;
	int connectionID = name_open( CHANNELNAME, 0 ) ;
	sleep(1);//ensure that the server channel has been created before we continue
	event prevEvent;
	event currEvent;
	int countReset = 0;
	int countIncrease = 0;

	for(;;){
		//sendingMessage.triggerEvent = pollInputs();
		currEvent = pollInputs();
		if(currEvent == Mode && (currentWalker->is_in() == Set_Tire_Circ || currentWalker->is_in() == Change_Circ)){
			currEvent = Increase;
		}

		if( currEvent == prevEvent && currEvent == Reset){
			//holding button down
			countReset++;
		}else if( currEvent == prevEvent && currEvent == Increase){
			//holding button down
			countIncrease++;
		}else{
			countReset = 0;
			countIncrease = 0;
		}


		if((currEvent == NAE && prevEvent != NAE )|| (countReset > 200) || (countIncrease > 100)){
			//release button so fire the event
			sendingMessage.triggerEvent = prevEvent;
			std::cout << prevEvent << std::endl;
			MsgSend(connectionID, &sendingMessage, sizeof(sendingMessage), &replyMessage, sizeof(replyMessage));
			countReset = 0;
			countIncrease = 0;
		}

		prevEvent = currEvent;

		//0.01 seconds looping 200 times == 2 seconds
		usleep(10000);
	}

	char inChar;
	for(;;){
		std::cin >> inChar;
		switch(inChar){
		case 's' :
			sendingMessage.triggerEvent = Set;
			break;
		case 't':
			sendingMessage.triggerEvent = SetTire;
			break;
		case 'i':
			sendingMessage.triggerEvent = Increase;
			break;
		case 'm':
			sendingMessage.triggerEvent = Mode;
			break;
		case 'a':
			sendingMessage.triggerEvent = Start_Stop;
			break;
		case 'r':
			sendingMessage.triggerEvent = Reset;
			break;
		case 'e':
			sendingMessage.triggerEvent = Sensor;
		}

		MsgSend( connectionID, &sendingMessage, sizeof(sendingMessage), &replyMessage, sizeof(replyMessage) );
		//send the message to the State Machine Controller
	}
	return 0;
}
