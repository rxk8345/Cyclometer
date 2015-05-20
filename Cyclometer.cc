#include <cstdlib>
#include <iostream>
#include <time.h>
#include "Events.h"
#include "State.h"
#include "Transition.h"
#include "HAL.h"
#include <pthread.h>
#include "WheelSensor.h"
#include "StateWalker.h"
#include "Calculate.h"
#include "Display.h"
#include "InputListener.h"


int DEBUGINT = 0;

modeEnum mode = notSet;
WheelSensor sensor;

//USER INPUT
bool calculateIsOn = false;
int tireSize = 210;
int units = 1;
int displayMode = 0;


StateWalker* currentWalker;

int main(int argc, char *argv[]) {
	std::cout << "Welcome to the QNX Momentics IDE" << std::endl;

	StateWalker* skyWalker_resetState = new StateWalker();
	skyWalker_resetState->defaultTrans = new ResetDefaultTran();
	StateWalker* skyWalker_calState = new StateWalker();
	skyWalker_calState->defaultTrans = new CalDefaultTran();

	currentWalker = skyWalker_resetState;


	// starting threads here
	startDisplayThread();

	pthread_t sensorThread;
	sensorThread = pthread_create(&sensorThread, NULL, &startWheelSensor, (void *)&sensor );

	pthread_t polling;
	polling = pthread_create(&polling, NULL, &PollingThread, NULL );
	if(polling){
		std::cerr << "Error failed to create polling thread" << std::endl;
	}

	name_attach_t *channel_id;
	int receiveID;
	Message recievedMessage;
	Message replyMessage;
	replyMessage.hdr.type = 0;
	replyMessage.hdr.subtype = 0;
	replyMessage.triggerEvent = NAE;

	channel_id = name_attach( NULL, CHANNELNAME, 0);

	if( channel_id ){
		std::cout << "Event Server is started\n" << std::endl;
	}else{
		std::cout << "Event Server was not created\n" << std::endl;
	}

	std::cout << "System Initialized\n" << std::endl;
	currentWalker->defaultTran();

	// start calc thread after default transition
	initCalculations();

	for(;;){
		receiveID = MsgReceive(channel_id->chid, &recievedMessage, sizeof(recievedMessage), NULL);
		if(recievedMessage.hdr.type == _IO_CONNECT){
			MsgReply(receiveID, EOK, NULL, 0);
		}else{
			MsgReply(receiveID, EOK, &replyMessage, sizeof(replyMessage));

			if(recievedMessage.triggerEvent == Reset){
				currentWalker = skyWalker_resetState;
				currentWalker->defaultTran();
				resetCalculations();

			}else if( currentWalker->is_in() == Set_Tire_Circ && recievedMessage.triggerEvent == Set){
				currentWalker = skyWalker_calState;
				currentWalker->defaultTran();
			}else if( (currentWalker->is_in() == Manual || currentWalker->is_in() == Automatic)
						&& recievedMessage.triggerEvent == Mode){
				//Toggle the display
				toggleDisplay();
			}else{
				currentWalker->accept(recievedMessage.triggerEvent);
			}
			//std::cout << DEBUGINT << std::endl;


		}
	}
	return EXIT_SUCCESS;
}
