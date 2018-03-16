/*
 * Drive10Turn90Drive5.h
 *
 *  Created on: Mar 15, 2018
 *      Author: JARVIS
 */

#ifndef SRC_SEQUENCES_DRIVE10TURN90DRIVE5_H_
#define SRC_SEQUENCES_DRIVE10TURN90DRIVE5_H_

#include <Sequences/SequenceBase.h>
#include <Commands/DriveFeetCommand.h>
#include <Commands/Turn__DegreesCommand.h>
#include <Systems/DrivebaseEncoderSensors.h>
#include <Systems/DrivebaseGyroSensor.h>
#include <Systems/Drivebase.h>

namespace auton{
class Drive10Turn90Drive5: public auton::SequenceBase {

	Drive__FeetCommand drive10;
	Turn__DegreesCommand turn90;
	Drive__FeetCommand drive5;

	std::list<CommandBase*> commandQueue = {
				&drive10
				, &turn90
				, &drive5
	};

public:
	Drive10Turn90Drive5(Drivebase* drivebase, DrivebaseEncoderSensors* encoders, DrivebaseGyroSensor* gyro) :
		drive10{10, drivebase, encoders, gyro},
		turn90{drivebase, gyro},
		drive5{5, drivebase, encoders, gyro} {
	}

	virtual ~Drive10Turn90Drive5(){

	}

	std::list<CommandBase*> getCommandQueue() override {
		return commandQueue;
	}
};
}
#endif /* SRC_SEQUENCES_DRIVE10TURN90DRIVE5_H_ */
