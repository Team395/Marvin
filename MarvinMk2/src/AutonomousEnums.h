/*
 * AutonomousEnums.h
 *
 *  Created on: Mar 30, 2018
 *      Author: dhoizner
 */

#ifndef SRC_AUTONOMOUSENUMS_H_
#define SRC_AUTONOMOUSENUMS_H_

enum class RobotStartPositions {
	kLeft
	, kRight
	, kCenter
};

enum class AutonomousScoringStrategy {
	kNone
	, kSwitch
	, kScale
	, kSwitchAndScale
};

#endif /* SRC_AUTONOMOUSENUMS_H_ */
