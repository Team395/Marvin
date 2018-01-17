#include <iostream>
#include <memory>
#include <string>


#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <Talon.h>
#include <Joystick.h>
#include <DifferentialDrive.h>

class Robot: public frc::IterativeRobot {
	frc::LiveWindow* lw = LiveWindow::GetInstance();
	DifferentialDrive drivetrain;

	Joystick joystick;

public:
	Robot() : drivetrain(0,1,2,3), joystick(0){

	}

	void RobotInit() {
	}

	void AutonomousInit() override {

	}

	void AutonomousPeriodic() {

	}

	void TeleopInit() {

	}

	void TeleopPeriodic() {
		drivetrain.ArcadeDrive(joystick);
	}

	void TestPeriodic() {

	}

};

START_ROBOT_CLASS(Robot)
