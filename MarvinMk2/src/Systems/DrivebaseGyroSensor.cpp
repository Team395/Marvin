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
	double* returnArray = new double[3];
	int errorResponse = imu.GetAccumGyro(returnArray);
	//TODO: what to do with errorResponse?
	return returnArray[gyroMap::GyroIndex::kZIndex];
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
