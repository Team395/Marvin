/*
 * ElevatorProfile.h
 *
 *  Created on: Feb 6, 2018
 *      Author: JARVIS
 */

#ifndef SRC_MOTIONPROFILES_ELEVATORPROFILE_H_
#define SRC_MOTIONPROFILES_ELEVATORPROFILE_H_
#include <cassert>

class ElevatorProfile {
	namespace constants{
		constexpr double inchesPerTick = 0;
		constexpr double elevatorTravel = 0;
		constexpr double maxInchesPerSecond = 0;
		constexpr double maxInchesPerSecondPerSecond = 0;
		constexpr double p = 0;
		constexpr double i = 0;
		constexpr double d = 0;
		constexpr double f = 0;
		constexpr double timePerPoint = 0;
	}
	double startingPosition;
	double endingPosition;
	double cruiseVelocity;
	double movementTime;

public:
	ElevatorProfile(double starting, double ending, double cruiseVel);
	virtual ~ElevatorProfile();
};

#endif /* SRC_MOTIONPROFILES_ELEVATORPROFILE_H_ */
