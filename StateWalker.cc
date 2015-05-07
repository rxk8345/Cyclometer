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

//*****************State Walker Class Definition
class StateWalker{
public:
	StateNode *currentState;
	void defaultTran(){
		currentState = defaultTransition.accept();
	}
	void accept(event e){
		currentState = currentState->accept(e);//ask the current state to accept this event
	}
	state is_in(){
		return currentState->is_in();
	}

protected:
	DefaultTran defaultTransition;
};

StateWalker skyWalker;


//*****************Polling Thread
//The polling thread listens for input type events and sends them to the state machine controller thread(main)
void* PollingThread(void* args){
	//Seting up the channel to send events to
	std::cout << "Polling Thread has started\n" << std::endl;
	Message sendingMessage;
	Message replyMessage;
	sendingMessage.hdr.type = 0 ;
	sendingMessage.hdr.subtype = 0 ;
	sendingMessage.triggeredEvent = BP;
	int connectionID = name_open( CHANNELNAME, 0 ) ;
	sleep(1);//ensure that the server channel has been created before we continue

	char inChar;
	for(;;){
		std::cin >> inChar;
		switch(inChar){
		case 'r' :
			sendingMessage.triggeredEvent = BP;
			break;
		case 'm':
			sendingMessage.triggeredEvent = OC;
			break;
		case 'i':
			sendingMessage.triggeredEvent = IR;
			break;
		}

		MsgSend( connectionID, &sendingMessage, sizeof(sendingMessage), &replyMessage, sizeof(replyMessage) );
		//send the message to the State Machine Controller
	}
	return 0;
}


int main(int argc, char *argv[]) {

	
	return EXIT_SUCCESS;
}
