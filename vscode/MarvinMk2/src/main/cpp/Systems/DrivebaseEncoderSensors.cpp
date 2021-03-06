/*
 * DrivebaseEncoderSensors.cpp
 *
 *  Created on: Jan 16, 2018
 *      Author: JARVIS
 */
#include <cassert>
#include <iostream>
#include <Libraries/GyroMap.h>
#include <RobotMap.h>
#include <Systems/Drivebase.h>
#include <Systems/DrivebaseEncoderSensors.h>

DrivebaseEncoderSensors::DrivebaseEncoderSensors(Drivebase* drivebasePointer) :
	SystemBase("DrivebaseEncoderSensors"),
	drivebase(drivebasePointer),
	leftEncoderTalon{getTalon(drivebase, TalonMap::kLeftEncoder)},
	rightEncoderTalon{getTalon(drivebase, TalonMap::kRightEncoder)} {
		leftEncoderTalon->SetSensorPhase(true);
		rightEncoderTalon->SetSensorPhase(true);
}

DrivebaseEncoderSensors::~DrivebaseEncoderSensors() {

}

frc::PIDSourceType DrivebaseEncoderSensors::GetPIDSourceType() {
	return frc::PIDSourceType::kDisplacement;
}

double DrivebaseEncoderSensors::PIDGet() {
	return getAveragedEncoderPositions();
}
double DrivebaseEncoderSensors::getAveragedEncoderPositions() {
	return (getLeftEncoder(DrivebaseEncoderSensors::returnType::kDisplacement) +
			getRightEncoder(DrivebaseEncoderSensors::returnType::kDisplacement)) / 2;
}
double DrivebaseEncoderSensors::convertToNativeUnits(double feet) {
	return (feet*INCHES_PER_FOOT*UNITS_PER_ROTATION/PI/WHEEL_DIAMETER_INCHES);
}

WPI_TalonSRX* DrivebaseEncoderSensors::getTalon(Drivebase* drivebase, int index){
	return drivebase->talonIndex[index-1];
}

double DrivebaseEncoderSensors::getLeftEncoder(returnType type){
	if(static_cast<int>(type) == 0){
		return leftEncoderTalon->GetSelectedSensorPosition(0);
	}
	else{
		return leftEncoderTalon->GetSelectedSensorVelocity(0);
	}
}

double DrivebaseEncoderSensors::getRightEncoder(returnType type){
	if(static_cast<int>(type) == 0){
		//TODO: not sure how to handle error here:
		// encoder values can be positive or negative, how do we differentiate from an error code?
		// possibly use rightEncoderTalon->GetLastError()? 0 = OKAY
		// as per: https://github.com/CrossTheRoadElec/Phoenix-frc-lib/blob/666d176a08151793044ab74e0005f13d3732ed96/libraries/driver/include/ctre/phoenix/ErrorCode.h

			return rightEncoderTalon->GetSelectedSensorPosition(0);
		}
		else{
			return rightEncoderTalon->GetSelectedSensorVelocity(0);
		}
}

void DrivebaseEncoderSensors::setMinimumPidOutput(double minimum){
	drivebase->setMinimumPidOutput(minimum);
}

void DrivebaseEncoderSensors::resetEncoderSensors(){
	leftEncoderTalon->SetSelectedSensorPosition(0, 0, 10);
	rightEncoderTalon->SetSelectedSensorPosition(0, 0, 10);
}
