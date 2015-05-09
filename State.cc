#include "State.h"
#include "Transition.h"
#include "Events.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>

extern modeEnum mode;

// SetUnitState

void SetUnitState::entry(){
	std::cout << "Set Unit State entry actions" << std::endl;
}

void SetUnitState::exitState(){
	std::cout << "Set Unit State exit actions" << std::endl;
}

StateNode* SetUnitState::accept(event e){
	std::cout << "Set Unit State accept actions" << std::endl;
	TranUnitToCirc tran;
	if(tran.checkAccept(e)){
		SetUnitState::exitState();
		return tran.accept();
	}
	else{
		StateNode * returnState = new SetUnitState();
		return returnState;
	}
}

// SetTireCircState
void SetTireCircState::entry(){
	std::cout << "Set Tire Circ State entry actions" << std::endl;
}

void SetTireCircState::exitState(){
	std::cout << "Set Tire Circ State exit actions" << std::endl;
}

StateNode * SetTireCircState::accept(event e){
	std::cout << "Set Tire Circ State accept actions" << std::endl;
	TranSetTireIncrease tran;
		if(tran.checkAccept(e)){
			SetTireCircState::exitState();
			return tran.accept();
		}
		else{
			StateNode * returnState = new SetTireCircState();
			return returnState;
		}
}

// ManualState
void ManualState::entry(){
	std::cout << "Manual State entry actions" << std::endl;
	mode = manualMode;
}

void ManualState::exitState(){
	std::cout << "Manual State exit actions" << std::endl;
}

StateNode * ManualState::accept(event e){
	std::cout << "Manual State accept actions" << std::endl;
	TranManualStartStop tran1;
	TranManualToAuto tran2;
	TranChangeTireManual tran3;
	if(tran1.checkAccept(e)){
		ManualState::exitState();
		return tran1.accept();
	}
	else if (tran2.checkAccept(e)){
		ManualState::exitState();
		return tran2.accept();
	}
	else if(tran3.checkAccept(e)){
		ManualState::exitState();
		return tran3.accept();
	}
	else{
		StateNode * returnState = new ManualState();
		return returnState;
	}
}


// AutomaticState
void AutomaticState::entry(){
	std::cout << "Automatic State entry actions" << std::endl;
	mode = autoMode;
}

void AutomaticState::exitState(){
	std::cout << "Automatic State exit actions" << std::endl;
}

StateNode * AutomaticState::accept(event e){
	std::cout << "Automatic State accept actions" << std::endl;
	TranAutoToManual tran1;
	TranChangeTireAuto tran2;
	if(tran1.checkAccept(e)){
		AutomaticState::exitState();
		return tran1.accept();
	}
	else if (tran2.checkAccept(e)){
		AutomaticState::exitState();
		return tran2.accept();
	}
	else{
		StateNode * returnState = new AutomaticState();
		return returnState;
	}
}


// ChangeTireCircState
void ChangeTireCircState::entry(){
	std::cout << "Change Tire Circ State entry actions" << std::endl;
}

void ChangeTireCircState::exitState(){
	std::cout << "Change Tire Circ State exit actions" << std::endl;

}

StateNode * ChangeTireCircState::accept(event e){
	std::cout << "Change Tire Circ State accept actions" << std::endl;
	TranReturnToManual tran1;
	TranReturnToAuto tran2;
	TranChangeTireIncrease tran3;
	if(tran1.checkAccept(e)){
		ChangeTireCircState::exitState();
		return tran1.accept();
	}
	else if (tran2.checkAccept(e)){
		ChangeTireCircState::exitState();
		return tran2.accept();
	}
	else if (tran3.checkAccept(e)){
			ChangeTireCircState::exitState();
			return tran3.accept();
		}
	else{
		StateNode * returnState = new ChangeTireCircState();
		return returnState;
	}
}
