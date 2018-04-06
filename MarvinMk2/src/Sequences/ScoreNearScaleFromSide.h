/*
 * Drive10Turn90Drive5.h
 *
 *  Created on: Mar 15, 2018
 *      Author: JARVIS
 */

#ifndef SRC_SEQUENCES_SCORENEARSCALEFROMSIDE_H_
#define SRC_SEQUENCES_SCORENEARSCALEFROMSIDE_H_

#include <Sequences/SequenceBase.h>

#include <OI.h>

#include <Systems/DrivebaseEncoderSensors.h>
#include <Systems/DrivebaseGyroSensor.h>
#include <Systems/Drivebase.h>
#include <Systems/FieldData.h>

#include <Commands/TestCommand.h>
#include <Commands/AutoElevatorCommand.h>
#include <Commands/DriveFeetCommand.h>
#include <Commands/Turn__DegreesCommand.h>
#include <Commands/ElevatorPositionCommand.h>
#include <Commands/AutoScoreCommand.h>

namespace auton {
	class ScoreNearScaleFromSide: public SequenceBase {

		Drive__FeetCommand drive1;
		Turn__DegreesCommand turn1;
		TestCommand test1{0.1};
		TestCommand test2{0.1};
		TestCommand test3{1.5};
		AutoElevatorCommand releaseCommand;
		AutoElevatorCommand elevatorCommand;
		AutoScoreCommand autoscoreCommand;
		Drive__FeetCommand drive2;
		AutoElevatorCommand zeroCommand;

		SequenceBase driveAwayFromWall;
		SequenceBase turnTowardsScalePlate;
		SequenceBase score;
		SequenceBase wait1;
		SequenceBase wait2;
		SequenceBase wait3;
		SequenceBase raiseElevator;

		SequenceBase driveBackFromScale;
		SequenceBase lowerElevator;

	public:
		ScoreNearScaleFromSide(Drivebase* drivebase, DrivebaseEncoderSensors* encoders,
				DrivebaseGyroSensor* gyro, ElevatorPositionCommand* positionCommand,
				PneumaticGripperCommand* pneumaticGripperCommand, SwitchScalePositions scalePosition) :
			drive1{21.3016, drivebase, encoders, gyro},
			turn1{(scalePosition == SwitchScalePositions::kLeft ? -45.0 : 45.0), drivebase, gyro},
			releaseCommand{positionCommand, OI::ElevatorPreset::kDeploy},
			elevatorCommand{positionCommand, OI::ElevatorPreset::kHighScale},
			autoscoreCommand{pneumaticGripperCommand},
			drive2{-2, drivebase, encoders, gyro},
			zeroCommand{positionCommand, OI::ElevatorPreset::kBottom}
			{
				driveAwayFromWall.setCommandsToRun(std::list<CommandBase*>{&drive1, &releaseCommand});
				wait1.setCommandsToRun(std::list<CommandBase*>{&test1});
				raiseElevator.setCommandsToRun(std::list<CommandBase*>{&elevatorCommand});
				wait3.setCommandsToRun(std::list<CommandBase*>{&test3});
				turnTowardsScalePlate.setCommandsToRun(std::list<CommandBase*>{&turn1});
				wait2.setCommandsToRun(std::list<CommandBase*>{&test2});
				score.setCommandsToRun(std::list<CommandBase*>{&autoscoreCommand});
				driveBackFromScale.setCommandsToRun(std::list<CommandBase*>{&drive2});
				lowerElevator.setCommandsToRun(std::list<CommandBase*>{&zeroCommand});

				std::list<SequenceBase*> sequences{
					&driveAwayFromWall
					, &wait1
					, &raiseElevator
					, &wait3
					, &turnTowardsScalePlate
					, &wait2
					, &score
					, &driveBackFromScale
					, &lowerElevator
				};

				sequenceQueue = sequences;
			}

			void disable() {
				driveAwayFromWall.disable();
				raiseElevator.disable();
				turnTowardsScalePlate.disable();
				score.disable();
				driveBackFromScale.disable();
				lowerElevator.disable();
			}

			virtual ~ScoreNearScaleFromSide(){}
	};
}
#endif /*SRC_SEQUENCES_SCORENEARSCALEFROMSIDE_H_ */
