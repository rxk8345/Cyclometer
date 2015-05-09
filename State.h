/*
 * State.h
 *
 *  Created on: Mar 16, 2015
 *      Author: rdl8212
 */

#ifndef STATE_H_
#define STATE_H_

#include "Events.h"

class Transistion;


//**********Prototype*************

class StateNode{
public:
	StateNode() {};
	virtual ~StateNode() {};
	virtual void entry()=0;
	virtual void exitState()=0;
	virtual StateNode* accept(event e)=0;
	virtual state is_in()=0;
};


class SetUnitState: public StateNode{
	void entry();
	void exitState();
	StateNode* accept(event e);
	state is_in(){return Set_Unit;};
};

class SetTireCircState: public StateNode{
	void entry();
	void exitState();
	StateNode* accept(event e);
	state is_in(){return Set_Tire_Circ;};
};

class AutomaticState: public StateNode{
	void entry();
	void exitState();
	StateNode* accept(event e);
	state is_in(){return Automatic;};
};

class ManualState: public StateNode{
	void entry();
	void exitState();
	StateNode* accept(event e);
	state is_in(){return Manual;};
};

class ChangeTireCircState: public StateNode{
	void entry();
	void exitState();
	StateNode* accept(event e);
	state is_in(){return Change_Circ;};
};



#endif /* STATE_H_ */
