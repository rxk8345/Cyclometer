/*
 * Transition.h
 *
 *  Created on: Mar 16, 2015
 *      Author: rdl8212
 */

#ifndef TRANSITION_H_
#define TRANSITION_H_

#include "Events.h"

class StateNode;

//***************Prototype Class************
class Transition{
public:
	Transition(){};
	virtual ~Transition(){};
	virtual bool checkAccept(event e){};
	virtual StateNode* accept(){};
};

// initial transition
class ResetDefaultTran: public Transition{
public:
	bool checkAccept(event e);
	StateNode* accept();
};

// Calculation super state initial transition
class CalDefaultTran: public Transition{
public:
	bool checkAccept(event e);
	StateNode* accept();
};

// mode button pressed to toggle between measurement units
class TranSetUnitModePressed: public Transition{
public:
	bool checkAccept(event e);
	StateNode* accept();
};

// transition from set unit state to set tire circ with SetTire event
class TranUnitToCirc: public Transition{
public:
	bool checkAccept(event e);
	StateNode* accept();
};

// increase tire circ transition
class TranSetTireIncrease: public Transition{
public:
	bool checkAccept(event e);
	StateNode* accept();
};

// reset calculation transition
class TranResetCalc: public Transition{
public:
	bool checkAccept(event e);
	StateNode* accept();
};

// reset Cyclometer transition
class TranResetCyclometer: public Transition{
public:
	bool checkAccept(event e);
	StateNode* accept();
};

// Start/stop manual transition
class TranManualStartStop: public Transition{
public:
	bool checkAccept(event e);
	StateNode* accept();
};

// Manual to auto mode transition
class TranManualToAuto: public Transition{
public:
	bool checkAccept(event e);
	StateNode* accept();
};

// Auto to manual mode transition
class TranAutoToManual: public Transition{
public:
	bool checkAccept(event e);
	StateNode* accept();
};

// Set tire circ from manual mode transition
class TranChangeTireManual: public Transition{
public:
	bool checkAccept(event e);
	StateNode* accept();
};

// Set tire circ from auto mode transition
class TranChangeTireAuto: public Transition{
public:
	bool checkAccept(event e);
	StateNode* accept();
};

// return change tire circ to manual mode transition
class TranReturnToManual: public Transition{
public:
	bool checkAccept(event e);
	StateNode* accept();
};

// return change tire circ to auto mode transition
class TranReturnToAuto: public Transition{
public:
	bool checkAccept(event e);
	StateNode* accept();
};

// increase tire circ transition in change circ state
class TranChangeTireIncrease: public Transition{
public:
	bool checkAccept(event e);
	StateNode* accept();
};

#endif /* TRANSITION_H_ */
