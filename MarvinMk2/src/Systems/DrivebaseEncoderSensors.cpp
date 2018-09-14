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

DrivebaseEncoderSensors::DrivebaseEncoderSensors(Drivebase* drivebasePointer,NewTalonMap* newTalonMap) :
	SystemBase("DrivebaseEncoderSensors"),
	drivebase(drivebasePointer),
	newTalonMap_(newTalonMap)
//  TODO:  Java backport cleanup
#if 0
,
	leftEncoderTalon{getTalon(drivebase, TalonMap::kLeftEncoder)},
	rightEncoderTalon{getTalon(drivebase, TalonMap::kRightEncoder)}
#endif
{
#if 0
	    leftEncoderTalon->SetSensorPhase(true);
		rightEncoderTalon->SetSensorPhase(true);
#else
		newTalonMap_->getTalonByID(TalonMap::kLeftEncoder)->SetSensorPhase(true);
		newTalonMap_->getTalonByID(TalonMap::kRightEncoder)->SetSensorPhase(true);
#endif
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
#if 0
	return drivebase->talonIndex[index-1];
#else
	return newTalonMap_->getTalonByID(index);
#endif
}

double DrivebaseEncoderSensors::getLeftEncoder(returnType type){
	if(static_cast<int>(type) == 0){
		// TODO:  Java backport cleanup
#if 0
		return leftEncoderTalon->GetSelectedSensorPosition(0);
#else
		return newTalonMap_->getTalonByID(TalonMap::kLeftEncoder)->GetSelectedSensorPosition(0);
#endif
	}
	else{
#if 0
		return leftEncoderTalon->GetSelectedSensorVelocity(0);
#else
		return newTalonMap_->getTalonByID(TalonMap::kLeftEncoder)->GetSelectedSensorVelocity(0);
#endif
	}
}

double DrivebaseEncoderSensors::getRightEncoder(returnType type){
	if(static_cast<int>(type) == 0){
		//TODO: not sure how to handle error here:
		// encoder values can be positive or negative, how do we differentiate from an error code?
		// possibly use rightEncoderTalon->GetLastError()? 0 = OKAY
		// as per: https://github.com/CrossTheRoadElec/Phoenix-frc-lib/blob/666d176a08151793044ab74e0005f13d3732ed96/libraries/driver/include/ctre/phoenix/ErrorCode.h

			// TODO:  Java backport cleanup
#if 0
			return rightEncoderTalon->GetSelectedSensorPosition(0);
#else
			return newTalonMap_->getTalonByID(TalonMap::kRightEncoder)->GetSelectedSensorPosition(0);
#endif
	}
	else{
#if 0
			return rightEncoderTalon->GetSelectedSensorVelocity(0);
#else
			return newTalonMap_->getTalonByID(TalonMap::kRightEncoder)->GetSelectedSensorVelocity(0);
#endif
	}
}

void DrivebaseEncoderSensors::setMinimumPidOutput(double minimum){
	drivebase->setMinimumPidOutput(minimum);
}

void DrivebaseEncoderSensors::resetEncoderSensors(){
#if 0
	leftEncoderTalon->SetSelectedSensorPosition(0, 0, 10);
	rightEncoderTalon->SetSelectedSensorPosition(0, 0, 10);
#else
	newTalonMap_->getTalonByID(TalonMap::kLeftEncoder)->SetSelectedSensorPosition(0, 0, 10);
	newTalonMap_->getTalonByID(TalonMap::kRightEncoder)->SetSelectedSensorPosition(0, 0, 10);
#endif
}
