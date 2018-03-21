/*
 * Drive5.h
 *
 *  Created on: Mar 15, 2018
 *      Author: JARVIS
 */

#ifndef SRC_SEQUENCES_CROSSAUTONLINE_H_
#define SRC_SEQUENCES_CROSSAUTONLINE_H_

#include <Sequences/SequenceBase.h>
#include <Commands/DriveFeetCommand.h>
#include <Commands/AutoIntakeCommand.h>
#include <Systems/DrivebaseEncoderSensors.h>
#include <Systems/DrivebaseGyroSensor.h>
#include <Systems/Drivebase.h>

namespace auton {
	class CrossAutonLine: public SequenceBase {

		Drive__FeetCommand drive5;
		AutoIntakeCommand intake;
		SequenceBase crossAutonLine{};
	public:
		CrossAutonLine(Drivebase* drivebase, DrivebaseEncoderSensors* encoders, DrivebaseGyroSensor* gyro, PneumaticGripperCommand* gripperCommand) :
			drive5{5, drivebase, encoders, gyro},
			intake{gripperCommand}
			{
				std::list<CommandBase*> sequenceOneCommands{
					&drive5,
					&intake
				};
				crossAutonLine.setCommandsToRun(sequenceOneCommands);

				std::list<SequenceBase*> sequences{
					&crossAutonLine
				};

				sequenceQueue = sequences;
			}

			virtual ~CrossAutonLine(){}
	};
}
#endif /* SRC_SEQUENCES_CROSSAUTONLINE_H_ */
