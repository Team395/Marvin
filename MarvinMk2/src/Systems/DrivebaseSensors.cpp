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

DrivebaseSensors::DrivebaseSensors(Elevator* elevator) : SystemBase("DrivebaseSensors"), imu(getGyroTalon(elevator)){

}

DrivebaseSensors::~DrivebaseSensors() {

}

PigeonIMU* DrivebaseSensors::getIMU() {
	return &imu;
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

WPI_TalonSRX* DrivebaseSensors::getGyroTalon(Elevator* elevator){
	return &(elevator->winchController);
}
