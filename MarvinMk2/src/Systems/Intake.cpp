/*
 * Intake.cpp
 *
 *  Created on: Jan 24, 2018
 *      Author: hlewi
 */

#include <Systems/Intake.h>

Intake::Intake() : SystemBase("Intake"){
	// TODO Auto-generated constructor stub

}

Intake::~Intake() {
	// TODO Auto-generated destructor stub
}

void Intake::driveLeft(double speed){
	leftIntake.Set(speed);
}

void Intake::driveRight(double speed){
	rightIntake.Set(speed);
}
