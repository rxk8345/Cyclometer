/*
 * Transition.h
 *
 *  Created on: Mar 16, 2015
 *      Author: rdl8212
 */

#ifndef TRANSITION_H_
#define TRANSITION_H_

#include "common.h"

class StateNode;

//***************Prototype Class************
class Transition{
public:
	virtual bool checkAccept(event e){
	}
	virtual StateNode* accept(){
	}
};

#endif /* TRANSITION_H_ */
