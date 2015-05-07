/*
 * State.h
 *
 *  Created on: Mar 16, 2015
 *      Author: rdl8212
 */

#ifndef STATE_H_
#define STATE_H_

#include "common.h"

class Transistion;

//**********Prototype*************

class StateNode{
public:
	virtual void entry(){
	}
	virtual void exitState(){
	}
	virtual StateNode* accept(event e){
	}
	virtual state is_in(){
	}
};



#endif /* STATE_H_ */
