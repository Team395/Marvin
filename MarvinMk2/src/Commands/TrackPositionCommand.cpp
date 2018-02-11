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
	this->xPosition = 0;
	this->yPosition = 0;
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
//	double xDelta;
//	double yDelta;

	if(leftDisplacement != rightDisplacement){
		double turnRadius =  (leftDisplacement+rightDisplacement)/(2*angularDisplacement);
		SmartDashboard::PutNumber("Turn Radius", turnRadius);

		this->xPosition += turnRadius * (std::cos(theta * kPi/180) - 1);
		this->yPosition += turnRadius * std::sin(theta * kPi/180);
	}
	else{
		SmartDashboard::PutNumber("Turn Radius", -555);
		this->xPosition += leftDisplacement * std::cos(theta * kPi/180);
		this->yPosition += leftDisplacement * std::sin(theta * kPi/180);
	}

//	SmartDashboard::PutNumber("X Delta", xDelta);
//	SmartDashboard::PutNumber("Y Delta", yDelta);
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
