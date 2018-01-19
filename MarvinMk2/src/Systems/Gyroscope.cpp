/*
 * Gyroscope.cpp
 *
 *  Created on: Jan 16, 2018
 *      Author: JARVIS
 */

#include <Systems/Gyroscope.h>

Gyroscope::Gyroscope() : SubsystemBase("gyroscope"){
	// TODO Auto-generated constructor stub

}

Gyroscope::~Gyroscope() {
	// TODO Auto-generated destructor stub
}

ADIS16448_IMU* Gyroscope::getIMU() {
	return &imu;
}

double Gyroscope::getAngleX() {
	return imu.GetAngleX();

}

frc::PIDSourceType Gyroscope::GetPIDSourceType() {
	return frc::PIDSourceType::kDisplacement;
}

double Gyroscope::PIDGet() {
	//Pretty sure its in degrees
	return getAngleX();
}
