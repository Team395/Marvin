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

namespace auton {
	class ScoreLeftFromLeft: public SequenceBase {

		Drive__FeetCommand drive1;
		Turn__DegreesCommand turn1;
		Drive__FeetCommand drive2;
		TestCommand test1{0.1};
		TestCommand test2{0.1};
		AutoElevatorCommand elevatorCommand;

		SequenceBase driveAwayFromWall;
		SequenceBase turnTowardsSwitchPlate;
		SequenceBase approachSwitch;

		SequenceBase wait1;
		SequenceBase wait2;

	public:
		ScoreLeftFromLeft(Drivebase* drivebase, DrivebaseEncoderSensors* encoders, DrivebaseGyroSensor* gyro, ElevatorPositionCommand* positionCommand) :
			drive1{12.3125, drivebase, encoders, gyro},
			turn1{-90, drivebase, gyro},
			drive2{2.3333, drivebase, encoders, gyro},
			elevatorCommand{positionCommand, OI::ElevatorPreset::kSwitch}
			{
				driveAwayFromWall.setCommandsToRun(std::list<CommandBase*>{&drive1, &elevatorCommand});
				wait1.setCommandsToRun(std::list<CommandBase*>{&test1});
				turnTowardsSwitchPlate.setCommandsToRun(std::list<CommandBase*>{&turn1});
				wait2.setCommandsToRun(std::list<CommandBase*>{&test2});
				approachSwitch.setCommandsToRun(std::list<CommandBase*>{&drive2});

				std::list<SequenceBase*> sequences{
					&driveAwayFromWall
					, &wait1
					, &turnTowardsSwitchPlate
					, &wait2
					, &approachSwitch

				};
				sequenceQueue = sequences;
			}

			virtual ~ScoreLeftFromLeft(){}
	};
}
#endif /*SRC_SEQUENCES_SCORELEFTFROMLEFT_H_ */
