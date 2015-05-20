/*
 * InputListener.h
 *
 *  Created on: May 19, 2015
 *      Author: xxz1530
 */

#ifndef INPUTLISTENER_H_
#define INPUTLISTENER_H_

#include "Events.h"
#include "State.h"
#include "Transition.h"
#include "StateWalker.h"

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

#define CHANNELNAME "bike_channel"
typedef struct _pulse msg_header_t;
typedef struct{
	msg_header_t hdr;
	event triggerEvent;
}Message;


void* PollingThread(void* args);

#endif /* INPUTLISTENER_H_ */
