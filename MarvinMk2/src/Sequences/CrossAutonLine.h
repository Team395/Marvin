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

		Drive__FeetCommand drive15;
		SequenceBase crossAutonLine{};
	public:
		CrossAutonLine(Drivebase* drivebase, DrivebaseEncoderSensors* encoders, DrivebaseGyroSensor* gyro, PneumaticGripperCommand* gripperCommand) :
			drive15{15, drivebase, encoders, gyro}
			{
				std::list<CommandBase*> sequenceOneCommands{
					&drive15
				};
				crossAutonLine.setCommandsToRun(sequenceOneCommands);

				std::list<SequenceBase*> sequences{
					&crossAutonLine
				};

				sequenceQueue = sequences;
			}

		void execute() {
			switch(currentStep) {
			case 0: {
				bool success = processCommand(&drive15);
				if(success) currentStep++;
			} break;
			case 1: {
				sequenceState = CommandState::kFinished;
			} break;
			}
		}

		void disable() {
			drive15.disable();
		}

			virtual ~CrossAutonLine(){}
	};
}
#endif /* SRC_SEQUENCES_CROSSAUTONLINE_H_ */
