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


