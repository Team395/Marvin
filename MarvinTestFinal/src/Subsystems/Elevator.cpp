#include "Elevator.h"
#include "../RobotMap.h"
#include "ctre/Phoenix.h"
#include "../Commands/JoystickElevator.h"

Elevator::Elevator() : Subsystem("ExampleSubsystem") {
	winchTalon = WPI_TalonSRX(RobotMap::Elevator::kWinch);
}

void Elevator::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());

	SetDefaultCommand(new JoystickElevator());
}

void Elevator::driveWinch(double speed){
	winchTalon.Set(speed);
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
