#include "State.h"
#include "Transition.h"
#include "Events.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>

extern modeEnum mode;

// SetUnitState
extern int units; //1 - km and 2 - miles
extern int tireSize;
extern bool calculateIsOn;

void SetUnitState::entry(){
	std::cout << "Set Unit State entry actions" << std::endl;
	if( units == 1){
		displayNumbers(-1,-1,-1,1);
		setMeasurementUnitLEDOff();
	}else if( units == 2){
		displayNumbers(-1,-1,-1,2);
		setMeasurementUnitLEDOn(); // on for miles
	}else{
		std::cout << "Units BROKEN!!!" << std::endl;
	}
}

void SetUnitState::exitState(){
	std::cout << "Set Unit State exit actions" << std::endl;
	clearDisplay();
}

StateNode* SetUnitState::accept(event e){
	std::cout << "Set Unit State accept actions" << std::endl;
	TranUnitToCirc tran;
	TranSetUnitModePressed tran2;
	if(tran.checkAccept(e)){
		SetUnitState::exitState();
		return tran.accept();
	}else if(tran2.checkAccept(e)){
		SetUnitState::exitState();
		return tran2.accept();
	}else if( e == Reset){
		SetUnitState::exitState();
		StateNode * returnState = new SetUnitState();
		return returnState;
	}else{
		StateNode * returnState = new SetUnitState();
		return returnState;
	}
}

// SetTireCircState
void SetTireCircState::entry(){
	std::cout << "Set Tire Circ State entry actions" << std::endl;
	int a = tireSize / 100;
	int b = tireSize % 100;
	b = b / 10;
	int c = tireSize % 10;
	displayNumbers(-1,a,b,c);
}

void SetTireCircState::exitState(){
	std::cout << "Set Tire Circ State exit actions" << std::endl;
	clearDisplay();
}

StateNode * SetTireCircState::accept(event e){
	std::cout << "Set Tire Circ State accept actions" << std::endl;
	TranSetTireIncrease tran;
		if(tran.checkAccept(e)){
			SetTireCircState::exitState();
			return tran.accept();
		}else if( e == Reset || e == Set){
			SetTireCircState::exitState();
			StateNode * returnState = new SetTireCircState();
			return returnState;
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
	setDisplayCalc(calculateIsOn);

}

void ManualState::exitState(){
	std::cout << "Manual State exit actions" << std::endl;
	setDisplayCalc(false);
	clearDisplay();
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
	else if( e == Reset){
		ManualState::exitState();
		StateNode * returnState = new ManualState();
		return returnState;
	}
	else{
		StateNode * returnState = new ManualState();
		return returnState;
	}
}


// AutomaticState
void AutomaticState::entry(){
	std::cout << "Automatic State entry actions" << std::endl;
	calculateIsOn = true;
	mode = autoMode;
	setDisplayCalc(true);
}

void AutomaticState::exitState(){
	std::cout << "Automatic State exit actions" << std::endl;
	setDisplayCalc(false);
	clearDisplay();
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
	}else if( e == Reset){
		AutomaticState::exitState();
		StateNode * returnState = new AutomaticState();
		return returnState;
	}
	else{
		StateNode * returnState = new AutomaticState();
		return returnState;
	}
}


// ChangeTireCircState
void ChangeTireCircState::entry(){
	std::cout << "Change Tire Circ State entry actions" << std::endl;
	clearDisplay();
	int a = tireSize / 100;
	int b = tireSize % 100;
	b = b / 10;
	int c = tireSize % 10;
	displayNumbers(-1,a,b,c);

}

void ChangeTireCircState::exitState(){
	std::cout << "Change Tire Circ State exit actions" << std::endl;
	clearDisplay();

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
	}else if( e == Reset){
		ChangeTireCircState::exitState();
		StateNode * returnState = new ChangeTireCircState();
		return returnState;
	}
	else{
		StateNode * returnState = new ChangeTireCircState();
		return returnState;
	}
}
