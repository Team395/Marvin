/*
 * Gyroscope.cpp
 *
 *  Created on: Jan 16, 2018
 *      Author: JARVIS
 */
#include <cassert>
#include "Gyroscope.h"

Gyroscope::Gyroscope() : SystemBase("gyroscope"){
	// TODO Auto-generated constructor stub

}

Gyroscope::~Gyroscope() {
	// TODO Auto-generated destructor stub
}

PigeonIMU* Gyroscope::getIMU() {
	return &imu;
}

double Gyroscope::getAngleX() {
	double *returnArray{nullptr};
	imu.GetAccumGyro(returnArray);
	assert(returnArray && "Gyro not returning angles properly");
	return returnArray[0];
}

frc::PIDSourceType Gyroscope::GetPIDSourceType() {
	return frc::PIDSourceType::kDisplacement;
}

double Gyroscope::PIDGet() {
	//Pretty sure its in degrees
	return getAngleX();
}
