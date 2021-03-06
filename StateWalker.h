/*
 * StateWalker.h
 *
 *  Created on: May 9, 2015
 *      Author: rxk8345
 */

#ifndef STATEWALKER_H_
#define STATEWALKER_H_

#include "Events.h"
#include "State.h"
#include "Transition.h"

#include <cstdlib>
#include <cstdio>
#include <iostream>

#include <unistd.h>
#include <pthread.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include <assert.h>
#include <sys/syspage.h>
#include <sys/time.h>
#include <time.h>
#include <fcntl.h>
#include <semaphore.h>
#include <errno.h>



class StateWalker{
public:
	StateNode *currentState;
	void defaultTran();
	void accept(event e);
	state is_in();

	StateWalker();

	Transition* defaultTrans;
};


#endif /* STATEWALKER_H_ */
