#include <iostream>
#include <memory>
#include <string>


#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Systems/Gyroscope.h>

#include "Commands/ArcadeDriveCommand.h"
#include "Commands/JoystickElevatorCommand.h"
#include "Commands/Turn__DegreesCommand.h"

#include "Systems/Elevator.h"
#include "Systems/Drivebase.h"
#include "Libraries/ADIS16448_IMU.h"


#include "OI.h"

class Robot: public frc::IterativeRobot {
	frc::LiveWindow& m_lw = *LiveWindow::GetInstance();
	Elevator elevator{};
	Drivebase drivebase{};
	Gyroscope gyroscope{};

	OI oi{};

	ArcadeDriveCommand arcadeDrive{&drivebase, &oi};
	JoystickElevatorCommand joystickElevator{&elevator, &oi};
	Turn__DegreesCommand turn__DegreesCommand{&drivebase, &gyroscope, &oi};

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
		if(!oi.GetTurnButton()){
			//turn__DegreesCommand.disable();
			//turn__DegreesCommand.startNewturn();
			//arcadeDrive.update();
		}
		else{
			//turn__DegreesCommand.update();
		}

		joystickElevator.update();
		SmartDashboard::PutData("IMU", gyroscope.getIMU());
		SmartDashboard::PutBoolean("topLimit", elevator.topPressed());
		SmartDashboard::PutBoolean("bottomLimit", elevator.bottomPressed());
	}

	void TestPeriodic() override {

	}

};

START_ROBOT_CLASS(Robot)
