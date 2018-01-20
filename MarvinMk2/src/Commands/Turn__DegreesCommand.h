/*
 * Turn90Command.h
 *
 *  Created on: Jan 18, 2018
 *      Author: JARVIS
 */

#ifndef SRC_COMMANDS_TURN__DEGREESCOMMAND_H_
#define SRC_COMMANDS_TURN__DEGREESCOMMAND_H_

#include "../Systems/Drivebase.h"
#include "../OI.h"
#include "CommandBase.h"

#include <PIDController.h>
#include <Systems/Gyroscope.h>

class Turn__DegreesCommand : CommandBase {
	const double PI  =3.141592653589793238463;

	PIDController pidController;
	Gyroscope* gyroscope;
	OI* oi;

	double kTurnRadians{PI/2};
	double kAcceptableError{0.01};
	bool turnFinished{false};

public:
	Turn__DegreesCommand(Drivebase*, Gyroscope*, OI*);
	virtual ~Turn__DegreesCommand();

	void init() override;
	void update() override;
	void finish() override;
	bool isFinished() override;

/*	void update();
	void disable();
	void startNewturn(); */
};

#endif /* SRC_COMMANDS_TURN__DEGREESCOMMAND_H_ */
