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

namespace auton {
	class Drive10Turn90Drive5: public SequenceBase {

		Drive__FeetCommand drive10;
		Turn__DegreesCommand turn90;
		Drive__FeetCommand drive5;

		SequenceBase drive10sequence;
		SequenceBase turn90sequence;
		SequenceBase drive5sequence;

	public:
		Drive10Turn90Drive5(Drivebase* drivebase, DrivebaseEncoderSensors* encoders, DrivebaseGyroSensor* gyro) :
			drive10{10, drivebase, encoders, gyro, 0},
			turn90{90, drivebase, gyro, 0},
			drive5{5, drivebase, encoders, gyro, 0}
			{
				drive10sequence.setCommandsToRun(std::list<CommandBase*>{&drive10});
				turn90sequence.setCommandsToRun(std::list<CommandBase*>{&turn90});
				drive5sequence.setCommandsToRun(std::list<CommandBase*>{&drive5});

				std::list<SequenceBase*> sequences{
					&drive10sequence,
					&turn90sequence,
					&drive5sequence
				};
				sequenceQueue = sequences;
			}

			virtual ~Drive10Turn90Drive5(){}
	};
}
#endif /* SRC_SEQUENCES_DRIVE10TURN90DRIVE5_H_ */
