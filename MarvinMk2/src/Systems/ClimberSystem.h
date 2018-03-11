/*
 * ClimberSystem.h
 *
 *  Created on: Mar 11, 2018
 *      Author: JARVIS
 */

#ifndef SRC_SYSTEMS_CLIMBERSYSTEM_H_
#define SRC_SYSTEMS_CLIMBERSYSTEM_H_

#include <Systems/SystemBase.h>

#include <RobotMap.h>
#include <Talon.h>
#include <Servo.h>

class ClimberSystem: public SystemBase {
	Talon winchController{ClimberMap::kWinch};
	Talon telescopeController{ClimberMap::kTelescope};
	Servo tiltController{ClimberMap::kTilt};
public:
	ClimberSystem();
	virtual ~ClimberSystem();

	// winch actions
	void startClimbing();
	void stopClimbing();

	// telescope actions
	void extendClimber();
	void retractClimber();
	void stopTelescopingClimber();

	// tilt actions
	void releaseClimber();
};

#endif /* SRC_SYSTEMS_CLIMBERSYSTEM_H_ */
