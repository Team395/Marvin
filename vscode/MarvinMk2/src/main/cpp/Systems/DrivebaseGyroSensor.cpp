/*
 * DrivebaseGyroSensor.cpp
 *
 *  Created on: Mar 11, 2018
 *      Author: JARVIS
 */

#include <Systems/DrivebaseGyroSensor.h>

#include <Libraries/GyroMap.h>


DrivebaseGyroSensor::DrivebaseGyroSensor(Drivebase* drivebasePointer) :
	SystemBase("DrivebaseGyroSensor"),
	drivebase(drivebasePointer),
	imu(getTalon(drivebase, TalonMap::kPigeon))
{
}

DrivebaseGyroSensor::~DrivebaseGyroSensor() {
	// TODO Auto-generated destructor stub
}

double DrivebaseGyroSensor::getAngleZ() {
#if 1
	static double lastResponse = 0;
	double returnArray[3] = {0,0,0};
	int errorResponse = imu.GetAccumGyro(returnArray);
	if (errorResponse == 0) {
		lastResponse = returnArray[gyroMap::GyroIndex::kZIndex];
	}

	return lastResponse;
#else
	static double returnArray[3] = {0,0,0};
	double lastResponse = returnArray[gyroMap::GyroIndex::kZIndex];
	int errorResponse = imu.GetAccumGyro(returnArray);
	if (errorResponse == -3) {
		return lastResponse;
	}

	return returnArray[gyroMap::GyroIndex::kZIndex];
#endif
}

frc::PIDSourceType DrivebaseGyroSensor::GetPIDSourceType() {
	return frc::PIDSourceType::kDisplacement;
}

double DrivebaseGyroSensor::PIDGet() {
	//Pretty sure its in degrees
	return getAngleZ();
}

WPI_TalonSRX* DrivebaseGyroSensor::getTalon(Drivebase* drivebase, int index){
	return drivebase->talonIndex[index-1];
}

void DrivebaseGyroSensor::setMinimumPidOutput(double minimum){
	drivebase->setMinimumPidOutput(minimum);
}
