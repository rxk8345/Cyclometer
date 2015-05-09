#include <cstdlib>
#include <iostream>
#include "Events.h"
#include "State.h"
#include "Transition.h"
#include <pthread.h>

#include "StateWalker.h"

int DEBUGINT = 0;

modeEnum mode = notSet;

int main(int argc, char *argv[]) {
	std::cout << "Welcome to the QNX Momentics IDE" << std::endl;
	StateWalker* skyWalker_resetState = new StateWalker();
	skyWalker_resetState->defaultTrans = new ResetDefaultTran();
	StateWalker* skyWalker_calState = new StateWalker();
	skyWalker_calState->defaultTrans = new CalDefaultTran();
	pthread_t polling;
	polling = pthread_create(&polling, NULL, PollingThread, NULL );
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

	skyWalker_calState->defaultTran();

	for(;;){
		receiveID = MsgReceive(channel_id->chid, &recievedMessage, sizeof(recievedMessage), NULL);
		if(recievedMessage.hdr.type == _IO_CONNECT){
			MsgReply(receiveID, EOK, NULL, 0);
		}else{
			MsgReply(receiveID, EOK, &replyMessage, sizeof(replyMessage));
			skyWalker_calState->accept(recievedMessage.triggerEvent);
			//std::cout << DEBUGINT << std::endl;
		}
	}
	return EXIT_SUCCESS;
}
