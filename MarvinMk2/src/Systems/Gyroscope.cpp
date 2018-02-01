/*
 * Gyroscope.cpp
 *
 *  Created on: Jan 16, 2018
 *      Author: JARVIS
 */
#include <cassert>
#include <iostream>
#include "Gyroscope.h"
#include <Libraries/GyroMap.h>

Gyroscope::Gyroscope(Elevator* elevator) : SystemBase("Gyroscope"), imu(getGyroTalon(elevator)){

}

Gyroscope::~Gyroscope() {

}

PigeonIMU* Gyroscope::getIMU() {
	return &imu;
}

double Gyroscope::getAngleZ() {
	double* returnArray = new double[3];
	imu.GetAccumGyro(returnArray);
	return returnArray[gyroMap::GyroIndex::kZIndex];
}

frc::PIDSourceType Gyroscope::GetPIDSourceType() {
	return frc::PIDSourceType::kDisplacement;
}

double Gyroscope::PIDGet() {
	//Pretty sure its in degrees
	return getAngleZ();
}

WPI_TalonSRX* Gyroscope::getGyroTalon(Elevator* elevator){
	return &(elevator->winchController);
}
