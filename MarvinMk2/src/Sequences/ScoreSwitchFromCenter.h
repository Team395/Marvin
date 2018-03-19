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

namespace auton {
	class ScoreSwitchFromCenter: public SequenceBase {

		Drive__FeetCommand drive5;
		Turn__DegreesCommand turn45;
		Drive__FeetCommand drive5_2;
		Turn__DegreesCommand turnNegative45;
		Drive__FeetCommand drive5_3;
		SwitchScalePositions switchPosition;

		SequenceBase driveAwayFromWall;
		SequenceBase turnTowardsSwitchPlate;
		SequenceBase driveTowardsSwitchPlate;
		SequenceBase alignWithSwitch;
		SequenceBase approachSwitch;

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
				turnTowardsSwitchPlate.setCommandsToRun(std::list<CommandBase*>{&turn45});
				driveTowardsSwitchPlate.setCommandsToRun(std::list<CommandBase*>{&drive5_2});
				alignWithSwitch.setCommandsToRun(std::list<CommandBase*>{&turnNegative45});
				approachSwitch.setCommandsToRun(std::list<CommandBase*>{&drive5_3});

				std::list<SequenceBase*> sequences{
					&driveAwayFromWall
					, &turnTowardsSwitchPlate
					, &driveTowardsSwitchPlate
					, &alignWithSwitch
					, &approachSwitch

				};
				sequenceQueue = sequences;
			}

			virtual ~ScoreSwitchFromCenter(){}
	};
}
#endif /*SRC_SEQUENCES_SCORESWITCHFROMCENTER_H_ */
