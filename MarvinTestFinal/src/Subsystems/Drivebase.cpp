#include "Drivebase.h"
#include "../RobotMap.h"
#include <Talon.h>
#include <SpeedControllerGroup.h>
#include <Drive/DifferentialDrive.h>
#include "../Commands/OperatorDrive.h"

Drivebase::Drivebase() : Subsystem("Drivebase") {
	//Temporary Talon Objects
	Talon rightTalon1{RobotMap::Drivebase::kRight1};
	Talon rightTalon2{RobotMap::Drivebase::kRight2};
	Talon leftTalon1{RobotMap::Drivebase::kLeft1};
	Talon leftTalon2{RobotMap::Drivebase::kLeft2};

	rightSpeedControllers{rightTalon1, rightTalon2};
	leftSpeedControllers{leftTalon1, leftTalon2};

	differentialDrive{leftSpeedControllers, rightSpeedControllers};
}

//Exposes WPILIB ArcadeDrive() for the internal DifferentialDrive object
void Drivebase::ArcadeDrive(double forward, double twist){
	differentialDrive.ArcadeDrive(forward, twist);
}

//Directly drives left and right side motors with double values
void Drivebase::SkidDrive(double left, double right){
	leftSpeedControllers.set(left);
	rightSpeedControllers.set(right);
}

void Drivebase::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());

	SetDefaultCommand(new OperatorDrive());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
