/*
 * TrackPositionCommand.h
 *
 *  Created on: Feb 9, 2018
 *      Author: JARVIS
 */

#ifndef SRC_COMMANDS_TRACKPOSITIONCOMMAND_H_
#define SRC_COMMANDS_TRACKPOSITIONCOMMAND_H_

#include <Commands/CommandBase.h>
#include <Systems/DrivebaseEncoderSensors.h>
#include <Systems/DrivebaseGyroSensor.h>

class TrackPositionCommand: public CommandBase {
	static constexpr double kPi = 3.14159265358979323846;
	// 4*PI = distance per wheel rotation
	// 34/50 = output shaft to wheel. 3/1 = output shaft to encoder
	// number of ticks per rotation = 128
	static constexpr double kDistancePerTick = 4 * kPi * 34 / (128*3*54) ;
	DrivebaseEncoderSensors* encoderSensors;
	DrivebaseGyroSensor* gyroSensor;
	double xPosition;
	double yPosition;
	double initialHeading;

	double lastTheta;
	double lastLeftEncoder;
	double lastRightEncoder;

public:
	TrackPositionCommand(DrivebaseEncoderSensors*, DrivebaseGyroSensor*);
	virtual ~TrackPositionCommand();

	void init() override;
	void update() override;
	void finish() override;
};

#endif /* SRC_COMMANDS_TRACKPOSITIONCOMMAND_H_ */
