/*
 * TrackPositionCommand.cpp
 *
 *  Created on: Feb 9, 2018
 *      Author: JARVIS
 */

#include <Commands/TrackPositionCommand.h>
#include <cmath>
#include <SmartDashboard/SmartDashboard.h>
#include <iostream>

TrackPositionCommand::TrackPositionCommand(DrivebaseSensors* sensors) : CommandBase("Track Position Command"),
drivebaseSensors{sensors},
xPosition{0},
yPosition{0},
initialHeading{0},
lastTheta{0},
lastLeftEncoder{0},
lastRightEncoder{0} {

}

TrackPositionCommand::~TrackPositionCommand() {
	// TODO Auto-generated destructor stusb
}

void TrackPositionCommand::init(){
	CommandBase::init();
	initialHeading = drivebaseSensors->getAngleZ() * kPi/180;
	lastTheta = initialHeading;
	lastLeftEncoder = drivebaseSensors->getLeftEncoder(DrivebaseSensors::returnType::kDisplacement);
	lastRightEncoder = drivebaseSensors->getRightEncoder(DrivebaseSensors::returnType::kDisplacement);
	xPosition = 0.0;
	yPosition = 0.0;
	std::cout << "RESET\n";
}

void TrackPositionCommand::update(){
	double leftEncoder{drivebaseSensors->getLeftEncoder(DrivebaseSensors::returnType::kDisplacement)};
	double rightEncoder{drivebaseSensors->getRightEncoder(DrivebaseSensors::returnType::kDisplacement)};
	double theta{drivebaseSensors->getAngleZ()* kPi/180};

	double leftDisplacement{(leftEncoder - lastLeftEncoder) * kDistancePerTick};
	double rightDisplacement{(rightEncoder - lastRightEncoder) * kDistancePerTick};
	double angularDisplacement{theta - lastTheta};

	SmartDashboard::PutNumber("Angular Displacement", angularDisplacement);
	double xDelta;
	double yDelta;

	if(leftDisplacement != rightDisplacement){
		double turnRadius =  (leftDisplacement+rightDisplacement)/(2*angularDisplacement);

		if(std::isinf(turnRadius) || std::isnan(turnRadius)) {turnRadius = 0;}
		SmartDashboard::PutNumber("Turn Radius", turnRadius);

		xDelta = turnRadius * (std::cos((theta + angularDisplacement) * kPi/180) - std::cos(theta * kPi/180));
		yDelta = turnRadius * (std::sin((theta + angularDisplacement) * kPi/180) - std::sin(theta * kPi/180));
	}
	else{
		SmartDashboard::PutNumber("Turn Radius", -555);
		xDelta = leftDisplacement * std::cos(theta * kPi/180);
		yDelta = leftDisplacement * std::sin(theta * kPi/180);
	}

	xPosition += xDelta;
	yPosition += yDelta;

	SmartDashboard::PutNumber("X Delta", xDelta);
	SmartDashboard::PutNumber("Y Delta", yDelta);
	SmartDashboard::PutNumber("X Position", xPosition);
	SmartDashboard::PutNumber("Y Position", yPosition);
	SmartDashboard::PutNumber("Heading", theta - initialHeading);

	lastLeftEncoder = leftEncoder;
	lastRightEncoder = rightEncoder;
	lastTheta = theta;
}

void TrackPositionCommand::finish(){
	CommandBase::finish();
}
