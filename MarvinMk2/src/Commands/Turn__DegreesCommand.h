/*
 * Turn90Command.h
 *
 *  Created on: Jan 18, 2018
 *      Author: JARVIS
 */

#ifndef SRC_COMMANDS_TURN__DEGREESCOMMAND_H_
#define SRC_COMMANDS_TURN__DEGREESCOMMAND_H_
#include <PIDController.h>

#include <Commands/CommandBase.h>
#include <OI.h>
#include <Systems/Drivebase.h>
#include <Systems/DrivebaseGyroSensor.h>
#include <iostream>

class Turn__DegreesCommand : public CommandBase {
	const double PI  =3.141592653589793238463;

	PIDController pidController;
	DrivebaseGyroSensor* gyroSensor;

	double turnDegrees{0};
	double kAcceptableError{0.25};
	bool turnFinished{false};

	double timeout;
	double commandStartedTime;
public:
	Turn__DegreesCommand(double, Drivebase*, DrivebaseGyroSensor*, double);
	virtual ~Turn__DegreesCommand();

	void init() override;
	void update() override;
	void finish() override;
	void disable() override;

	void startNewturn();
};

#endif /* SRC_COMMANDS_TURN__DEGREESCOMMAND_H_ */
