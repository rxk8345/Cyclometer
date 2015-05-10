#include <cstdlib>
#include <cstdio>
#include <iostream>


#include <unistd.h>
#include <pthread.h>
#include <sys/iofunc.h>			// used by name_open()
#include <sys/dispatch.h>		// used by name_open()
#include <assert.h>
#include <sys/syspage.h>
#include <sys/time.h>
#include <time.h>
#include <fcntl.h>
#include <semaphore.h>
#include <errno.h>			// defines EOK
#include <StateWalker.h>

extern int DEBUGINT;

//*****************State Walker Class Definition
StateWalker::StateWalker(){}

void StateWalker::defaultTran(){
	currentState = defaultTrans->accept();
}

void StateWalker::accept(event e){
	DEBUGINT++;
	StateNode* temp = currentState->accept(e);//ask the current state to accept this event
	delete(currentState);
	currentState = temp;
}

state StateWalker::is_in(){
	return currentState->is_in();
}



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
