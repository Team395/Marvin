/*
 * Drive10Turn90Drive5.h
 *
 *  Created on: Mar 15, 2018
 *      Author: JARVIS
 */

#ifndef SRC_SEQUENCES_SCORESWITCHFROMCENTER_H_
#define SRC_SEQUENCES_SCORESWITCHFROMCENTER_H_

#include <Sequences/SequenceBase.h>
#include <Commands/DriveFeetCommand.h>
#include <Commands/Turn__DegreesCommand.h>
#include <Systems/DrivebaseEncoderSensors.h>
#include <Systems/DrivebaseGyroSensor.h>
#include <Systems/Drivebase.h>
#include <Systems/FieldData.h>
#include <Commands/TestCommand.h>
#include <Commands/AutoElevatorCommand.h>
#include <Commands/AutoScoreCommand.h>

namespace auton {
	class ScoreSwitchFromCenter: public SequenceBase {

		Drive__FeetCommand drive1;
		AutoElevatorCommand releaseCommand;
		Turn__DegreesCommand turn45;
		Drive__FeetCommand drive2;
		Turn__DegreesCommand turnNegative45;
		Drive__FeetCommand drive3;
		AutoElevatorCommand autoElevatorCommand;
		AutoScoreCommand autoscoreCommand;

		SwitchScalePositions switchPosition;
		TestCommand test1{0.1};
		TestCommand test2{0.1};
		TestCommand test3{0.1};
		TestCommand test4{0.1};

		SequenceBase driveAwayFromWall;
		SequenceBase turnTowardsSwitchPlate;
		SequenceBase driveTowardsSwitchPlate;
		SequenceBase alignWithSwitch;
		SequenceBase approachSwitch;
		SequenceBase score;

		SequenceBase wait1;
		SequenceBase wait2;
		SequenceBase wait3;
		SequenceBase wait4;

	public:
		ScoreSwitchFromCenter(Drivebase* drivebase, DrivebaseEncoderSensors* encoders, DrivebaseGyroSensor* gyro,
				SwitchScalePositions switchPosition, ElevatorPositionCommand* elevatorPositionCommand,
				PneumaticGripperCommand* pneumaticGripperCommand) :
			drive1{(switchPosition==SwitchScalePositions::kLeft) ? 2.7396 : 3.1771, drivebase, encoders, gyro},
			releaseCommand{elevatorPositionCommand, OI::ElevatorPreset::kDeploy},
			turn45{((switchPosition==SwitchScalePositions::kLeft)? 1:-1)*45.0, drivebase, gyro},
			drive2{(switchPosition==SwitchScalePositions::kLeft) ? 4.0953 : 2.8579, drivebase, encoders, gyro},
			turnNegative45{((switchPosition==SwitchScalePositions::kLeft)? 1:-1)*-45.0, drivebase, gyro},
			drive3{(switchPosition==SwitchScalePositions::kLeft) ? 2.7396 : 3.1771, drivebase, encoders, gyro},
			autoElevatorCommand{elevatorPositionCommand, OI::ElevatorPreset::kSwitch},
			autoscoreCommand{pneumaticGripperCommand},
			switchPosition{switchPosition}
			{
				driveAwayFromWall.setCommandsToRun(std::list<CommandBase*>{&drive1, &releaseCommand});
				wait1.setCommandsToRun(std::list<CommandBase*>{&test1});
				turnTowardsSwitchPlate.setCommandsToRun(std::list<CommandBase*>{&turn45});
				wait2.setCommandsToRun(std::list<CommandBase*>{&test2});
				driveTowardsSwitchPlate.setCommandsToRun(std::list<CommandBase*>{&drive2});
				wait3.setCommandsToRun(std::list<CommandBase*>{&test3});
				alignWithSwitch.setCommandsToRun(std::list<CommandBase*>{&turnNegative45});
				wait4.setCommandsToRun(std::list<CommandBase*>{&test4, &autoElevatorCommand});
				approachSwitch.setCommandsToRun(std::list<CommandBase*>{&drive3});
				score.setCommandsToRun(std::list<CommandBase*>{&autoscoreCommand});

				std::list<SequenceBase*> sequences{
					&driveAwayFromWall
					, &wait1
					, &turnTowardsSwitchPlate
					, &wait2
					, &driveTowardsSwitchPlate
					, &wait3
					, &alignWithSwitch
					, &wait4
					, &approachSwitch
					, &score
				};
				sequenceQueue = sequences;
			}

			void disable() {
				drive1.disable();
				turn45.disable();
				drive2.disable();
				turnNegative45.disable();
				drive3.disable();
			}

			virtual ~ScoreSwitchFromCenter(){}
	};
}
#endif /*SRC_SEQUENCES_SCORESWITCHFROMCENTER_H_ */
