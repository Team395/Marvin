#include "JoystickElevator.h"

JoystickElevator::JoystickElevator() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::elevator.get());
}

// Called just before this Command runs the first time
void JoystickElevator::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void JoystickElevator::Execute() {
	//Robot::elevator.
}

// Make this return true when this Command no longer needs to run execute()
bool JoystickElevator::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void JoystickElevator::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void JoystickElevator::Interrupted() {

}
