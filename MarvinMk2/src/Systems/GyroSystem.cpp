/*
 * GyroSystem.cpp
 *
 *  Created on: Jan 16, 2018
 *      Author: JARVIS
 */

#include <Systems/GyroSystem.h>

GyroSystem::GyroSystem() {
	// TODO Auto-generated constructor stub

}

GyroSystem::~GyroSystem() {
	// TODO Auto-generated destructor stub
}

ADIS16448_IMU* GyroSystem::getIMU() {
	return &imu;
}
