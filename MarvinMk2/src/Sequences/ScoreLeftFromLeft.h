/*
 * Drive10Turn90Drive5.h
 *
 *  Created on: Mar 15, 2018
 *      Author: JARVIS
 */

#ifndef SRC_SEQUENCES_SCORELEFTFROMLEFT_H_
#define SRC_SEQUENCES_SCORELEFTFROMLEFT_H_

#include <Sequences/SequenceBase.h>
#include <Commands/DriveFeetCommand.h>
#include <Commands/Turn__DegreesCommand.h>
#include <Systems/DrivebaseEncoderSensors.h>
#include <Systems/DrivebaseGyroSensor.h>
#include <Systems/Drivebase.h>
#include <Systems/FieldData.h>
#include <Commands/TestCommand.h>
#include <Commands/AutoElevatorCommand.h>
#include <OI.h>
#include <Commands/ElevatorPositionCommand.h>
#include <Commands/AutoScoreCommand.h>

namespace auton {
	class ScoreLeftFromLeft: public SequenceBase {

		Drive__FeetCommand drive1;
		Turn__DegreesCommand turn1;
		Drive__FeetCommand drive2;
		TestCommand test1{0.1};
		TestCommand test2{0.1};
		AutoElevatorCommand releaseCommand;
		AutoElevatorCommand elevatorCommand;
		AutoScoreCommand autoscoreCommand;

		SequenceBase driveAwayFromWall;
		SequenceBase turnTowardsSwitchPlate;
		SequenceBase approachSwitch;
		SequenceBase score;
		SequenceBase wait1;
		SequenceBase wait2;

	public:
		ScoreLeftFromLeft(Drivebase* drivebase, DrivebaseEncoderSensors* encoders,
				DrivebaseGyroSensor* gyro, ElevatorPositionCommand* positionCommand,
				PneumaticGripperCommand* pneumaticGripperCommand, bool startLeft) :
			drive1{12.3125, drivebase, encoders, gyro},
			turn1{startLeft ? -90.0 : 90.0, drivebase, gyro},
//			drive2{2.3333, drivebase, encoders, gyro},
			drive2{1, drivebase, encoders, gyro},
			releaseCommand{positionCommand, OI::ElevatorPreset::kDeploy},
			elevatorCommand{positionCommand, OI::ElevatorPreset::kSwitch},
			autoscoreCommand{pneumaticGripperCommand}
			{
				driveAwayFromWall.setCommandsToRun(std::list<CommandBase*>{&drive1, &releaseCommand});
//				driveAwayFromWall.setCommandsToRun(std::list<CommandBase*>{&drive1});
				wait1.setCommandsToRun(std::list<CommandBase*>{&test1});
				turnTowardsSwitchPlate.setCommandsToRun(std::list<CommandBase*>{&turn1});
				wait2.setCommandsToRun(std::list<CommandBase*>{&test2, &elevatorCommand});
				approachSwitch.setCommandsToRun(std::list<CommandBase*>{&drive2});
				score.setCommandsToRun(std::list<CommandBase*>{&autoscoreCommand});
				std::list<SequenceBase*> sequences{
					&driveAwayFromWall
					, &wait1
					, &turnTowardsSwitchPlate
					, &wait2
					, &approachSwitch
					, &score

				};
				sequenceQueue = sequences;
			}

			void execute() {
				switch(currentStep) {
				case 0: {
					bool success = processCommand(&drive1);
					bool success2 = processCommand(&elevatorCommand);
					if(success && success2) currentStep++;
				} break;
				case 1: {
					bool success = processCommand(&turn1);
					if(success) currentStep++;
				} break;
				case 2: {
					bool success = processCommand(&drive2);
					if(success) currentStep++;
				} break;
				case 4: {
					bool success = processCommand(&autoscoreCommand);
					if(success) currentStep++;
				} break;
				case 5: {
					sequenceState = CommandState::kFinished;
				} break;
				}
			}

			void disable() {
				drive1.disable();
				turn1.disable();
				drive2.disable();
				score.disable();
			}

			virtual ~ScoreLeftFromLeft(){}
	};
}
#endif /*SRC_SEQUENCES_SCORELEFTFROMLEFT_H_ */
