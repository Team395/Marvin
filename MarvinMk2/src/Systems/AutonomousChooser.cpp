/*
 * AutonomousChooser.cpp
 *
 *  Created on: Apr 5, 2018
 *      Author: JARVIS
 */

#include <Systems/AutonomousChooser.h>

AutonomousChooser::AutonomousChooser() : SystemBase("Auton Chooser"){

}

AutonomousChooser::~AutonomousChooser() {
	// TODO Auto-generated destructor stub
}

RobotStartPositions AutonomousChooser::getRobotStartPosition(){
	int startPosition = (!startPositionLeft.Get())*1 + (!startPositionRight.Get())*2;

	switch(startPosition){
		case 0:
			return RobotStartPositions::kCenter;
			break;
		case 1:
			return RobotStartPositions::kLeft;
			break;
		case 2:
			return RobotStartPositions::kRight;
			break;
		default:
			return RobotStartPositions::kCenter;
			break;
	}
}

AutonomousScoringStrategy AutonomousChooser::getAutonomousScoringStrategy(){
	int scoringStrategy = (!scoringStrategySwitch.Get()) * 1 + (!scoringStrategyScale.Get()) * 2;

	switch(scoringStrategy){
		case 0:
			return AutonomousScoringStrategy::kSwitch;
			break;
		case 1:
			return AutonomousScoringStrategy::kSwitch;
			break;
		case 2:
			return AutonomousScoringStrategy::kScale;
			break;
		default:
			return AutonomousScoringStrategy::kSwitch;
			break;
	}
}
