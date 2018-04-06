/*
 * AutonomousChooser.h
 *
 *  Created on: Apr 5, 2018
 *      Author: JARVIS
 */

#ifndef SRC_SYSTEMS_AUTONOMOUSCHOOSER_H_
#define SRC_SYSTEMS_AUTONOMOUSCHOOSER_H_

#include <Systems/SystemBase.h>
#include <AutonomousEnums.h>
#include <DigitalInput.h>
#include <RobotMap.h>

class AutonomousChooser: public SystemBase {

	DigitalInput startPositionLeft{ChooserMap::kLeft};
	DigitalInput startPositionRight{ChooserMap::kRight};
	DigitalInput scoringStrategyNone{ChooserMap::kNone};
	DigitalInput scoringStrategyScale{ChooserMap::kScale};

public:
	AutonomousChooser();
	virtual ~AutonomousChooser();

	RobotStartPositions getRobotStartPosition();
	AutonomousScoringStrategy getAutonomousScoringStrategy();

};

#endif /* SRC_SYSTEMS_AUTONOMOUSCHOOSER_H_ */
