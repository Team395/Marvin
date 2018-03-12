/*
 * DriveFeetCommand.h
 *
 *  Created on: Feb 17, 2018
 *      Author: JARVIS
 */

#ifndef SRC_COMMANDS_DRIVEFEETCOMMAND_H_
#define SRC_COMMANDS_DRIVEFEETCOMMAND_H_

#include <Commands/CommandBase.h>
#include <PIDController.h>
#include <Systems/DrivebaseEncoderSensors.h>
#include <Systems/DrivebaseGyroSensor.h>

class Drive__FeetCommand: public CommandBase{

	class PIDGetter : PIDOutput{
		double pidValue;
	public:
		PIDGetter();
		void PIDWrite(double);
		double getPIDValue();
	};

	PIDController linearPID;
	PIDController rotationalPID;
	PIDGetter linearGetter{};
	PIDGetter rotationalGetter{};

	DrivebaseEncoderSensors* encoderSensors;
	DrivebaseGyroSensor* gyroSensor;

	Drivebase* drivebase;
	bool movementFinished = true;
	double requestedMovementFeet = 0;
	double kAcceptableError=651.9; //actually two inches

public:
	Drive__FeetCommand(double, Drivebase*, DrivebaseEncoderSensors*, DrivebaseGyroSensor*);
	virtual ~Drive__FeetCommand();

	void init() override;
	void update() override;
	void finish() override;

	void disable();
	void startNewMovement();
};

#endif /* SRC_COMMANDS_DRIVEFEETCOMMAND_H_ */
