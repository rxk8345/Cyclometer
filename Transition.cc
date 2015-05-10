#include "Transition.h"
#include "State.h"
#include "Events.h"

#include <cstdlib>
#include <cstdio>
#include <iostream>

//class State1;
extern modeEnum mode;

// default reset super state transition
bool ResetDefaultTran::checkAccept(event e){
	return false;
}

StateNode* ResetDefaultTran::accept(){
	StateNode* returnState = new SetUnitState();
//	SetUnitState state;
//	returnState = &state;

	// action list happens here
	if( returnState != NULL){
		returnState->entry();
	}else{
		std::cout << "oh crap " << std::endl;
	}

	return returnState;
}


// default calculation super state transition
bool CalDefaultTran::checkAccept(event e){
	return false;
}

StateNode* CalDefaultTran::accept(){
	StateNode* returnState = new ManualState();
	//ManualState state;
	//returnState = &state;

	// action list happens here
	if( returnState != NULL){
		returnState->entry();
	}else{
		std::cout << "oh crap " << std::endl;
	}

	return returnState;
}



bool TranSetUnitModePressed::checkAccept(event e){
	return e == Mode;
}

StateNode* TranSetUnitModePressed::accept(){
	StateNode* returnState = new SetUnitState();
	// action list happens here
	if( returnState != NULL){
		returnState->entry();
	}else{
		std::cout << "oh crap " << std::endl;
	}
	return returnState;
}



bool TranUnitToCirc::checkAccept(event e){
	return e == SetTire;
}

StateNode* TranUnitToCirc::accept(){
	StateNode* returnState = new SetTireCircState();
	//SetTireCircState state;
	//returnState = &state;

	// action list happens here
	if( returnState != NULL){
		returnState->entry();
	}else{
		std::cout << "oh crap " << std::endl;
	}


	return returnState;
}


bool TranSetTireIncrease::checkAccept(event e){
	return e == Increase;
}

StateNode * TranSetTireIncrease::accept(){
	StateNode * returnState = new SetTireCircState();
	//SetTireCircState state;
	//returnState = &state;

	// action list happens here
	if( returnState != NULL){
		returnState->entry();
	}else{
		std::cout << "oh crap " << std::endl;
	}


	return returnState;
}



// skip set and reset between super states


bool TranManualStartStop::checkAccept(event e){
	return e == Start_Stop;
}

StateNode * TranManualStartStop::accept(){
	StateNode * returnState = new ManualState();
	//ManualState state;
	//returnState = &state;

	// action list happens here
	if( returnState != NULL){
		returnState->entry();
	}else{
		std::cout << "oh crap " << std::endl;
	}


	return returnState;
}


bool TranManualToAuto::checkAccept(event e){
	return e == Mode;
}

StateNode * TranManualToAuto::accept(){
	StateNode * returnState = new AutomaticState();
	//AutomaticState state;
	//returnState = &state;

	// action list happens here
	if( returnState != NULL){
		returnState->entry();
	}else{
		std::cout << "oh crap " << std::endl;
	}

	return returnState;
}


bool TranAutoToManual::checkAccept(event e){
	return e == Mode;
}

StateNode * TranAutoToManual::accept(){
	StateNode * returnState = new ManualState();
	//ManualState state;
	//returnState = &state;

	// action list happens here
	if( returnState != NULL){
		returnState->entry();
	}else{
		std::cout << "oh crap " << std::endl;
	}


	return returnState;
}


bool TranChangeTireManual::checkAccept(event e){
	return e == SetTire;
}

StateNode * TranChangeTireManual::accept(){
	StateNode * returnState= new ChangeTireCircState();

	// action list happens here
	if( returnState != NULL){
		returnState->entry();
	}else{
		std::cout << "oh crap " << std::endl;
	}


	return returnState;
}


bool TranChangeTireAuto::checkAccept(event e){
	return e == SetTire;
}

StateNode * TranChangeTireAuto::accept(){
	StateNode * returnState = new ChangeTireCircState;

	// action list happens here
	if( returnState != NULL){
		returnState->entry();
	}else{
		std::cout << "oh crap " << std::endl;
	}


	return returnState;
}


bool TranReturnToManual::checkAccept(event e){
	return e == Set && mode == manualMode;
}

StateNode * TranReturnToManual::accept(){
	StateNode * returnState = new ManualState;

	// action list happens here
	if( returnState != NULL){
		returnState->entry();
	}else{
		std::cout << "oh crap " << std::endl;
	}


	return returnState;
}


bool TranReturnToAuto::checkAccept(event e){
	return e == Set && mode == autoMode;
}

StateNode * TranReturnToAuto::accept(){
	StateNode * returnState = new AutomaticState;
	// action list happens here
	if( returnState != NULL){
		returnState->entry();
	}else{
		std::cout << "oh crap " << std::endl;
	}


	return returnState;
}


bool TranChangeTireIncrease::checkAccept(event e){
	return e == Increase;
}

StateNode * TranChangeTireIncrease::accept(){
	StateNode * returnState = new ChangeTireCircState;
	// action list happens here
	if( returnState != NULL){
		returnState->entry();
	}else{
		std::cout << "oh crap " << std::endl;
	}


	return returnState;
}
