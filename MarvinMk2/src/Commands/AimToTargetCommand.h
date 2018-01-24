/*
 * AimToTarget.h
 *
 *  Created on: Jan 20, 2018
 *      Author: JARVIS
 */

#ifndef SRC_COMMANDS_AIMTOTARGETCOMMAND_H_
#define SRC_COMMANDS_AIMTOTARGETCOMMAND_H_

#include <PIDController.h>

#include <Commands/CommandBase.h>
#include <Libraries/LimelightMap.h>
#include <Systems/Limelight.h>
#include <Systems/Drivebase.h>



class AimToTargetCommand : public CommandBase {
	Drivebase* drivebase;
	Limelight* limelight;
	PIDController pidController;

	bool turnFinished{false};
public:
	AimToTargetCommand(Drivebase*, Limelight*, limelightMap::PipeLine);
	virtual ~AimToTargetCommand();

	void init() override;
	void update() override;
	void finish() override;

	void disable();
	void startNewTurn();
};



#endif /* SRC_COMMANDS_AIMTOTARGETCOMMAND_H_ */
