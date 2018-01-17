#ifndef Drivebase_H
#define Drivebase_H

#include <Commands/Subsystem.h>
#include <SpeedControllerGroup.h>
#include <Drive/DifferentialDrive.h>

class Drivebase : public Subsystem {
private:
	SpeedControllerGroup rightSpeedControllers;
	SpeedControllerGroup leftSpeedControllers;
	DifferentialDrive differnetialDrive;

public:
	Drivebase();
	void InitDefaultCommand();

	void ArcadeDrive(double, double);
	void SkidDrive(double, double);

};

#endif  // Drivebase_H
