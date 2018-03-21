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

namespace auton {
	class ScoreSwitchFromCenter: public SequenceBase {

		Drive__FeetCommand drive5;
		Turn__DegreesCommand turn45;
		Drive__FeetCommand drive5_2;
		Turn__DegreesCommand turnNegative45;
		Drive__FeetCommand drive5_3;
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

		SequenceBase wait1;
		SequenceBase wait2;
		SequenceBase wait3;
		SequenceBase wait4;

	public:
		ScoreSwitchFromCenter(Drivebase* drivebase, DrivebaseEncoderSensors* encoders, DrivebaseGyroSensor* gyro, SwitchScalePositions switchPosition) :
			drive5{5, drivebase, encoders, gyro},
			turn45{((switchPosition==SwitchScalePositions::kLeft)? 1:-1)*45.0, drivebase, gyro},
			drive5_2{5, drivebase, encoders, gyro},
			turnNegative45{((switchPosition==SwitchScalePositions::kLeft)? 1:-1)*-45.0, drivebase, gyro},
			drive5_3{5, drivebase, encoders, gyro},
			switchPosition{switchPosition}
			{
				driveAwayFromWall.setCommandsToRun(std::list<CommandBase*>{&drive5});
				wait1.setCommandsToRun(std::list<CommandBase*>{&test1});
				turnTowardsSwitchPlate.setCommandsToRun(std::list<CommandBase*>{&turn45});
				wait2.setCommandsToRun(std::list<CommandBase*>{&test2});
				driveTowardsSwitchPlate.setCommandsToRun(std::list<CommandBase*>{&drive5_2});
				wait3.setCommandsToRun(std::list<CommandBase*>{&test3});
				alignWithSwitch.setCommandsToRun(std::list<CommandBase*>{&turnNegative45});
				wait4.setCommandsToRun(std::list<CommandBase*>{&test4});
				approachSwitch.setCommandsToRun(std::list<CommandBase*>{&drive5_3});

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

				};
				sequenceQueue = sequences;
			}

			virtual ~ScoreSwitchFromCenter(){}
	};
}
#endif /*SRC_SEQUENCES_SCORESWITCHFROMCENTER_H_ */
