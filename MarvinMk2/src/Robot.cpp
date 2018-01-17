#include <iostream>
#include <memory>
#include <string>


#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SmartDashboard.h>

#include "Commands/ArcadeDriveCommand.h"
#include "Commands/JoystickElevatorCommand.h"

#include "Systems/Elevator.h"
#include "Systems/Drivebase.h"
#include "Systems/GyroSystem.h"
#include "Libraries/ADIS16448_IMU.h"


#include "OI.h"

class Robot: public frc::IterativeRobot {
	frc::LiveWindow& m_lw = *LiveWindow::GetInstance();
	Elevator elevator{};
	Drivebase drivebase{};
	GyroSystem gyroSystem{};

	OI oi{};

	ArcadeDriveCommand arcadeDrive{&drivebase, &oi};
	JoystickElevatorCommand joystickElevator{&elevator, &oi};

public:

	void RobotInit() {
	}

	void AutonomousInit() override {

	}

	void AutonomousPeriodic() override {

	}

	void TeleopInit() override {

	}

	void TeleopPeriodic() override {
		arcadeDrive.update();
		joystickElevator.update();
		SmartDashboard::PutData("IMU", gyroSystem.getIMU());
	}

	void TestPeriodic() override {

	}

};

START_ROBOT_CLASS(Robot)
