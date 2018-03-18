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

	public:
		ScoreSwitchFromCenter(Drivebase* drivebase, DrivebaseEncoderSensors* encoders, DrivebaseGyroSensor* gyro, SwitchScalePositions switchPosition) :
			drive5{5, drivebase, encoders, gyro},
			turn45{((switchPosition==SwitchScalePositions::kLeft)? 1:-1)*45.0, drivebase, gyro},
			drive5_2{5, drivebase, encoders, gyro},
			turnNegative45{((switchPosition==SwitchScalePositions::kLeft)? 1:-1)*-45.0, drivebase, gyro},
			drive5_3{5, drivebase, encoders, gyro},
			switchPosition{switchPosition}
			{
				std::list<CommandBase*> commands{
					&drive5
					, &turn45
					, &drive5_2
					, &turnNegative45
					, &drive5_3

				};
				commandQueue = commands;
			}

			virtual ~ScoreSwitchFromCenter(){}
	};
}
#endif /*SRC_SEQUENCES_SCORESWITCHFROMCENTER_H_ */
