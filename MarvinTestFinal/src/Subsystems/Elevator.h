#ifndef Elevator_H
#define Elevator_H

#include <Commands/Subsystem.h>
#include "ctre/Phoenix.h"

class Elevator : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	WPI_TalonSRX winchController;

public:
	Elevator();
	void InitDefaultCommand();
	void driveWinch(double);
};

#endif  // Elevator_H
