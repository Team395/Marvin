/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <iostream>
#include <string>

#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <TimedRobot.h>
#include <XboxController.h>
#include <Timer.h>

enum ElevatorStates{
	kSwitch = 0
	, kScaleLow
	, kScaleNormal
	, kScaleHigh
	, kDrivingUp
	, kDrivingDown
	, kHolding
	, kZero
};

enum IntakeStates{
	kAutomatic,
	kManual,
	kAutoscore
};

class Robot : public frc::TimedRobot {
	frc::XboxController xboxController{2};
	bool intakeOpen = true;
	bool intakeOut = false;
	bool intakeIn = false;
	ElevatorStates elevatorState = kZero;
	IntakeStates intakeState = kAutomatic;
	IntakeStates lastIntakeState = kAutomatic;

	bool scoreTimerStarted = false;
	double scoreTimerStartedTime = 0;
public:
	void RobotInit() {
		m_chooser.AddDefault(kAutoNameDefault, kAutoNameDefault);
		m_chooser.AddObject(kAutoNameCustom, kAutoNameCustom);
		frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
	}

	/*
	 * This autonomous (along with the chooser code above) shows how to
	 * select between different autonomous modes using the dashboard. The
	 * sendable chooser code works with the Java SmartDashboard. If you
	 * prefer the LabVIEW Dashboard, remove all of the chooser code and
	 * uncomment the GetString line to get the auto name from the text box
	 * below the Gyro.
	 *
	 * You can add additional auto modes by adding additional comparisons to
	 * the if-else structure below with additional strings. If using the
	 * SendableChooser make sure to add them to the chooser code above as
	 * well.
	 */
	void AutonomousInit() override {
		m_autoSelected = m_chooser.GetSelected();
		// m_autoSelected = SmartDashboard::GetString("Auto Selector",
		//		 kAutoNameDefault);
		std::cout << "Auto selected: " << m_autoSelected << std::endl;

		if (m_autoSelected == kAutoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}
	}

	void AutonomousPeriodic() {
		if (m_autoSelected == kAutoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}
	}

	void TeleopInit() {}

	void TeleopPeriodic() {
		//intake
		double deadband = 0.15;
		double intakeThrottle = xboxController.GetY(frc::GenericHID::JoystickHand::kRightHand);
		if(std::abs(intakeThrottle) < deadband){
			intakeThrottle = 0;
		}
		intakeOut = intakeOut || intakeThrottle < 0;
		intakeIn = intakeThrottle > 0;
		frc::SmartDashboard::PutBoolean("Intake Out", intakeOut);
		frc::SmartDashboard::PutBoolean("Intake In", intakeIn);

		bool actuateGripper = false;
		if(xboxController.GetTriggerAxis(frc::GenericHID::JoystickHand::kRightHand) > 0.5){
			intakeOpen = false;
			actuateGripper = true;
		}
		if(xboxController.GetTriggerAxis(frc::GenericHID::JoystickHand::kLeftHand) > 0.5){
			intakeOpen = true;
			actuateGripper = true;
		}
		frc::SmartDashboard::PutBoolean("Intake Open", intakeOpen);
		frc::SmartDashboard::PutBoolean("Intake Open2", intakeOpen);
		frc::SmartDashboard::PutBoolean("Intake Closed", !intakeOpen);

		bool autoscore = xboxController.GetStickButton(frc::GenericHID::JoystickHand::kRightHand);
		bool toggleIntakeMode = xboxController.GetBackButton();
		if(toggleIntakeMode){
			if(intakeState == IntakeStates::kAutomatic) intakeState = IntakeStates::kManual;
			else if(intakeState == IntakeStates::kManual) intakeState = IntakeStates::kAutomatic;
		}
		else if(actuateGripper && intakeOpen){
			intakeState = IntakeStates::kAutomatic;
		}
		else if(actuateGripper){
			intakeState = IntakeStates::kManual;
		}
		if(!intakeOpen && autoscore){
			intakeState = IntakeStates::kAutoscore;
			if(!scoreTimerStarted) {
				scoreTimerStarted = true;
				scoreTimerStartedTime = Timer::GetFPGATimestamp();
				intakeOut = true;
			}
		}
		if(scoreTimerStarted && Timer::GetFPGATimestamp() - scoreTimerStartedTime > 3){
			intakeOut = false;
			intakeOpen = true;
			intakeState = IntakeStates::kAutomatic;
			scoreTimerStarted = false;
		}

		frc::SmartDashboard::PutBoolean("IntakeAutomaticMode", intakeState == IntakeStates::kAutomatic);
		frc::SmartDashboard::PutBoolean("IntakeManualMode", intakeState == IntakeStates::kManual);
		frc::SmartDashboard::PutBoolean("IntakeAutoscore", intakeState == IntakeStates::kAutoscore);

		// Elevator Presets
		double elevatorThrottle = xboxController.GetY(frc::GenericHID::JoystickHand::kLeftHand);
		if(std::abs(elevatorThrottle) < deadband){
			elevatorThrottle = 0;
		}
		bool elevatorUp = elevatorThrottle < 0;
		bool elevatorDown = elevatorThrottle > 0;
		if(elevatorUp) elevatorState = kDrivingUp;
		else if(elevatorDown) elevatorState = kDrivingDown;
		else if(elevatorState != kZero
				&& elevatorState != kSwitch
				&& elevatorState != kScaleLow
				&& elevatorState != kScaleNormal
				&& elevatorState != kScaleHigh) {
			elevatorState = kHolding;
		}

		if(xboxController.GetXButton()) elevatorState = kSwitch;
		if(xboxController.GetAButton()) elevatorState = kScaleLow;
		if(xboxController.GetBButton()) elevatorState = kScaleNormal;
		if(xboxController.GetYButton()) elevatorState = kScaleHigh;
		if(xboxController.GetStickButton(frc::GenericHID::JoystickHand::kLeftHand)) elevatorState = kZero;

		frc::SmartDashboard::PutBoolean("SwitchPosition", elevatorState == kSwitch);
		frc::SmartDashboard::PutBoolean("ScaleLowPosition", elevatorState == kScaleLow);
		frc::SmartDashboard::PutBoolean("ScaleNormalPosition", elevatorState == kScaleNormal);
		frc::SmartDashboard::PutBoolean("ScaleHighPosition", elevatorState == kScaleHigh);
		frc::SmartDashboard::PutBoolean("Zero", elevatorState == kZero);
		frc::SmartDashboard::PutBoolean("DrivingDown", elevatorState == kDrivingDown);
		frc::SmartDashboard::PutBoolean("DrivingUp", elevatorState == kDrivingUp);
		frc::SmartDashboard::PutBoolean("Holding", elevatorState == kHolding);
	}

	void TestPeriodic() {}

private:
	frc::LiveWindow& m_lw = *LiveWindow::GetInstance();
	frc::SendableChooser<std::string> m_chooser;
	const std::string kAutoNameDefault = "Default";
	const std::string kAutoNameCustom = "My Auto";
	std::string m_autoSelected;
};

START_ROBOT_CLASS(Robot)
