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

TrackPositionCommand::TrackPositionCommand(DrivebaseEncoderSensors* encoderSensors, DrivebaseGyroSensor* gyroSensor) : CommandBase("Track Position Command"),
encoderSensors{encoderSensors},
gyroSensor{gyroSensor},
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
	initialHeading = gyroSensor->getAngleZ() * kPi/180;
	lastTheta = initialHeading;
	//lastLeftEncoder = encoderSensors->getLeftEncoder(DrivebaseEncoderSensors::returnType::kDisplacement);
	lastRightEncoder = encoderSensors->getRightEncoder(DrivebaseEncoderSensors::returnType::kDisplacement);
	xPosition = 0.0;
	yPosition = 0.0;
	std::cout << "RESET\n";
}

void TrackPositionCommand::update(){
	//double leftEncoder{encoderSensors->getLeftEncoder(DrivebaseEncoderSensors::returnType::kDisplacement)};
	double rightEncoder{encoderSensors->getRightEncoder(DrivebaseEncoderSensors::returnType::kDisplacement)};
	double theta{gyroSensor->getAngleZ()* kPi/180};

	//sdouble leftDisplacement{(leftEncoder - lastLeftEncoder) * kDistancePerTick};
	double rightDisplacement{(rightEncoder - lastRightEncoder) * kDistancePerTick};
	double angularDisplacement{theta - lastTheta};

	frc::SmartDashboard::PutNumber("Angular Displacement", angularDisplacement);
	double xDelta;
	double yDelta;

//	if(leftDisplacement != rightDisplacement){
//		double turnRadius =  (leftDisplacement+rightDisplacement)/(2*angularDisplacement);
//
//		if(std::isinf(turnRadius) || std::isnan(turnRadius)) {turnRadius = 0;}
//		frc::SmartDashboard::PutNumber("Turn Radius", turnRadius);
//
//		xDelta = turnRadius * (std::cos((theta + angularDisplacement) * kPi/180) - std::cos(theta * kPi/180));
//		yDelta = turnRadius * (std::sin((theta + angularDisplacement) * kPi/180) - std::sin(theta * kPi/180));
//	}
//	else{
//		frc::SmartDashboard::PutNumber("Turn Radius", -555);
//		xDelta = leftDisplacement * std::cos(theta * kPi/180);
//		yDelta = leftDisplacement * std::sin(theta * kPi/180);
//	}

//	xPosition += xDelta;
//	yPosition += yDelta;
//
//	frc::SmartDashboard::PutNumber("X Delta", xDelta);
//	frc::SmartDashboard::PutNumber("Y Delta", yDelta);
//	frc::SmartDashboard::PutNumber("X Position", xPosition);
//	frc::SmartDashboard::PutNumber("Y Position", yPosition);
	frc::SmartDashboard::PutNumber("Heading", theta - initialHeading);

//	lastLeftEncoder = leftEncoder;
	lastRightEncoder = rightEncoder;
	lastTheta = theta;
}

void TrackPositionCommand::finish(){
	CommandBase::finish();
}
