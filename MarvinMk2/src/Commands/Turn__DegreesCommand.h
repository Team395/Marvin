/*
 * Turn90Command.h
 *
 *  Created on: Jan 18, 2018
 *      Author: JARVIS
 */

#ifndef SRC_COMMANDS_TURN__DEGREESCOMMAND_H_
#define SRC_COMMANDS_TURN__DEGREESCOMMAND_H_

#include "../Systems/Drivebase.h"
#include "../Systems/GyroSystem.h"
#include "../OI.h"

#include <PIDController.h>

class Turn__DegreesCommand {
	const double PI  =3.141592653589793238463;

	PIDController pidController;
	GyroSystem* gyroSystem;
	OI* oi;

	double kTurnRadians{PI/2};
	double kAcceptableError{0.01};
	bool turnFinished{false};

public:
	Turn__DegreesCommand(Drivebase*, GyroSystem*, OI*);
	virtual ~Turn__DegreesCommand();

	void update();
	void disable();
	void startNewturn();
};

#endif /* SRC_COMMANDS_TURN__DEGREESCOMMAND_H_ */
