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
#include <Systems/DrivebaseEncoderSensors.h>
#include <Systems/DrivebaseGyroSensor.h>
#include <Systems/Drivebase.h>

namespace auton {
	class CrossAutonLine: public SequenceBase {

		Drive__FeetCommand drive5;

	public:
		CrossAutonLine(Drivebase* drivebase, DrivebaseEncoderSensors* encoders, DrivebaseGyroSensor* gyro) :
			drive5{5, drivebase, encoders, gyro}
			{
				std::list<CommandBase*> commands{
					&drive5
				};
				commandQueue = commands;
			}

			virtual ~CrossAutonLine(){}
	};
}
#endif /* SRC_SEQUENCES_CROSSAUTONLINE_H_ */
