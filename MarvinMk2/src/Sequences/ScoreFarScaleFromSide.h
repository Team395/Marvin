/*
 * ScoreFarScaleFromSide.h
 *
 *  Created on: Mar 30, 2018
 *      Author: dhoizner
 */

#ifndef SRC_SEQUENCES_SCOREFARSCALEFROMSIDE_H_
#define SRC_SEQUENCES_SCOREFARSCALEFROMSIDE_H_

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
	class ScoreFarScaleFromSide: public SequenceBase {
		Drive__FeetCommand driveToPlatformZone;
		Turn__DegreesCommand rotateToPlatformZone;
		Drive__FeetCommand driveAcrossPlatformZone;
		Turn__DegreesCommand rotateToScale;
		Turn__DegreesCommand rotateAwayFromScale;

		AutoElevatorCommand releaseIntake;
		AutoElevatorCommand raiseElevatorToScaleHeight;
		AutoElevatorCommand lowerElevatorToBottom;
		AutoScoreCommand autoscoreCommand;

		TestCommand test1{0.1};
		TestCommand test2{0.1};
		TestCommand test3{1.5};

		SequenceBase approachPlatformZone;
		SequenceBase alignWithPlatformZone;
		SequenceBase crossPlatformZone;
		SequenceBase alignWithScale;
		SequenceBase turnAwayFromScale;

		SequenceBase raiseElevator;
		SequenceBase score;
		SequenceBase lowerElevator;

		SequenceBase wait1;
		SequenceBase wait2;
		SequenceBase wait3;

	public:
		ScoreFarScaleFromSide(Drivebase* drivebase, DrivebaseEncoderSensors* encoders,
						DrivebaseGyroSensor* gyro, ElevatorPositionCommand* positionCommand,
						PneumaticGripperCommand* pneumaticGripperCommand, SwitchScalePositions scalePosition) :
				driveToPlatformZone{0, drivebase, encoders, gyro},
				rotateToPlatformZone{(scalePosition == SwitchScalePositions::kRight ? -90.0 : 90.0), drivebase, gyro},
				driveAcrossPlatformZone{0, drivebase, encoders, gyro},
				rotateToScale{(scalePosition == SwitchScalePositions::kRight ? 90.0 : -90.0), drivebase, gyro},
				rotateAwayFromScale{(scalePosition == SwitchScalePositions::kRight ? -180.0 : 180.0), drivebase, gyro},
				releaseIntake{positionCommand, OI::ElevatorPreset::kDeploy},
				raiseElevatorToScaleHeight{positionCommand, OI::ElevatorPreset::kHighScale},
				lowerElevatorToBottom{positionCommand, OI::ElevatorPreset::kBottom},
				autoscoreCommand{pneumaticGripperCommand}
			{
			approachPlatformZone.setCommandsToRun(std::list<CommandBase*>{&driveToPlatformZone, &releaseIntake});
			alignWithPlatformZone.setCommandsToRun(std::list<CommandBase*>{&rotateToPlatformZone});
			crossPlatformZone.setCommandsToRun(std::list<CommandBase*>{&driveAcrossPlatformZone});
			alignWithScale.setCommandsToRun(std::list<CommandBase*>{&rotateToScale});
			turnAwayFromScale.setCommandsToRun(std::list<CommandBase*>{&rotateAwayFromScale});

			raiseElevator.setCommandsToRun(std::list<CommandBase*>{&raiseElevatorToScaleHeight});
			score.setCommandsToRun(std::list<CommandBase*>{&autoscoreCommand});
			lowerElevator.setCommandsToRun(std::list<CommandBase*>{&lowerElevatorToBottom});

			wait1.setCommandsToRun(std::list<CommandBase*>{&test1});
			wait2.setCommandsToRun(std::list<CommandBase*>{&test1});
			wait3.setCommandsToRun(std::list<CommandBase*>{&test1});

			std::list<SequenceBase*> sequences{
				&approachPlatformZone
				, &wait1
				, &alignWithPlatformZone
				, &wait2
				, &crossPlatformZone
				, &raiseElevator
				, &wait3
				, &alignWithScale
				, &score
				, &turnAwayFromScale
				, &lowerElevator
			};

			sequenceQueue = sequences;
		}

		void disable() {

		}

		virtual ~ScoreFarScaleFromSide(){}
	};
}

#endif /* SRC_SEQUENCES_SCOREFARSCALEFROMSIDE_H_ */
