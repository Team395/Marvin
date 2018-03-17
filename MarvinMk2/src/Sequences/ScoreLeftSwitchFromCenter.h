/*
 * Drive10Turn90Drive5.h
 *
 *  Created on: Mar 15, 2018
 *      Author: JARVIS
 */

#ifndef SRC_SEQUENCES_SCORELEFTSWITCHFROMCENTER_H_
#define SRC_SEQUENCES_SCORELEFTSWITCHFROMCENTER_H_

#include <Sequences/SequenceBase.h>
#include <Commands/DriveFeetCommand.h>
#include <Commands/Turn__DegreesCommand.h>
#include <Systems/DrivebaseEncoderSensors.h>
#include <Systems/DrivebaseGyroSensor.h>
#include <Systems/Drivebase.h>

namespace auton {
	class ScoreLeftSwitchFromCenter: public SequenceBase {

		Drive__FeetCommand drive5;
		Turn__DegreesCommand turn45;
		Drive__FeetCommand drive5_2;
		Turn__DegreesCommand turnNegative45;
		Drive__FeetCommand drive5_3;

	public:
		ScoreLeftSwitchFromCenter(Drivebase* drivebase, DrivebaseEncoderSensors* encoders, DrivebaseGyroSensor* gyro) :
			drive5{5, drivebase, encoders, gyro},
			turn45{drivebase, gyro},
			drive5_2{5, drivebase, encoders, gyro},
			turnNegative45{drivebase, gyro},
			drive5_3{5, drivebase, encoders, gyro}
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

			virtual ~ScoreLeftSwitchFromCenter(){}
	};
}
#endif /* SRC_SEQUENCES_SCORELEFTSWITCHFROMCENTER_H_ */
