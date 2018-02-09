/*
 * DrivebaseSensors.cpp
 *
 *  Created on: Jan 16, 2018
 *      Author: JARVIS
 */
#include <cassert>
#include <iostream>
#include <Libraries/GyroMap.h>
#include <Systems/DrivebaseSensors.h>
#include <RobotMap.h>
#include <Systems/Drivebase.h>

DrivebaseSensors::DrivebaseSensors(Drivebase* drivebasePointer) :
	SystemBase("DrivebaseSensors"),
	drivebase(drivebasePointer),
	imu(getTalon(drivebase, TalonMap::kPigeon)),
	leftEncoderTalon{getTalon(drivebase, TalonMap::kLeftEncoder)},
	rightEncoderTalon{getTalon(drivebase, TalonMap::kRightEncoder)} {

}

DrivebaseSensors::~DrivebaseSensors() {

}

double DrivebaseSensors::getAngleZ() {
	double* returnArray = new double[3];
	imu.GetAccumGyro(returnArray);
	return returnArray[gyroMap::GyroIndex::kZIndex];
}

frc::PIDSourceType DrivebaseSensors::GetPIDSourceType() {
	return frc::PIDSourceType::kDisplacement;
}

double DrivebaseSensors::PIDGet() {
	//Pretty sure its in degrees
	return getAngleZ();
}

WPI_TalonSRX* DrivebaseSensors::getTalon(Drivebase* drivebase, int index){
	return drivebase->talonIndex[index];
}
