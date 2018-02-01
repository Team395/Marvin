/*
 * Intake.cpp
 *
 *  Created on: Jan 24, 2018
 *      Author: hlewi
 */

#include "Intake.h"

Intake::Intake() : SystemBase("Intake"){

}

Intake::~Intake() {

}

/*
void Intake::driveLeft(double speed){
	leftIntake.Set(speed);
}

void Intake::driveRight(double speed){
	rightIntake.Set(speed);
}
*/

void Intake::actuateClaw(bool open){
	if(open){
		clawOpen.Set(true);
		clawClose.Set(false);
	}
	else{
		clawOpen.Set(false);
		clawClose.Set(true);
	}
}

void Intake::disable(){
	clawOpen.Set(false);
	clawClose.Set(false);
}
