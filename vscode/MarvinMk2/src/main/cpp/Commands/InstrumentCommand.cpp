/*
 * InstrumentCommand.cpp
 *
 *  Created on: Mar 11, 2018
 *      Author: JARVIS
 */

#include <Commands/InstrumentCommand.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Timer.h>

InstrumentCommand::InstrumentCommand(OI* oi, Intake* intake) : CommandBase("InstrumentCommand")
	, oi{oi}
	, intake{intake} {

}

InstrumentCommand::~InstrumentCommand() {
}

void InstrumentCommand::init() {
	CommandBase::init();
}

void InstrumentCommand::update() {
	//intake
	double intakeThrottle = oi->getIntakeThrottle();

	intakeOut = (scoreTimerStarted && intakeOut) || intakeThrottle < 0;
	intakeIn = intakeThrottle > 0;
	frc::SmartDashboard::PutBoolean("Intake Out", intakeOut);
	frc::SmartDashboard::PutBoolean("Intake In", intakeIn);

	GripperState gripperState = intake->getGripperState();
	bool gripperOpen = gripperState == GripperState::open ? true : false;

	frc::SmartDashboard::PutBoolean("Intake Open", gripperOpen);
	frc::SmartDashboard::PutBoolean("Intake Open2", gripperOpen);
	frc::SmartDashboard::PutBoolean("Intake Closed", !gripperOpen);

	intakeState = intake->getState();

	frc::SmartDashboard::PutBoolean("IntakeAutomaticMode", intakeState == IntakeState::automatic);
	frc::SmartDashboard::PutBoolean("IntakeManualMode", intakeState == IntakeState::manual);
	frc::SmartDashboard::PutBoolean("IntakeAutoscore", intakeState == IntakeState::autoscore);

	// Elevator Presets
	double elevatorThrottle = oi->getElevatorThrottle();

	bool elevatorUp = elevatorThrottle > 0;
	bool elevatorDown = elevatorThrottle < 0;
	if(elevatorUp) elevatorState = kDrivingUp;
	else if(elevatorDown) elevatorState = kDrivingDown;
	else if(elevatorState != kZero
			&& elevatorState != kSwitch
			&& elevatorState != kScaleLow
			&& elevatorState != kScaleNormal
			&& elevatorState != kScaleHigh) {
		elevatorState = kHolding;
	}

	OI::ElevatorPreset preset = oi->getElevatorPreset();
	if(preset == OI::ElevatorPreset::kSwitch) elevatorState = kSwitch;
	if(preset == OI::ElevatorPreset::kLowScale) elevatorState = kScaleLow;
	if(preset == OI::ElevatorPreset::kNormalScale) elevatorState = kScaleNormal;
	if(preset == OI::ElevatorPreset::kHighScale) elevatorState = kScaleHigh;
	if(preset == OI::ElevatorPreset::kBottom) elevatorState = kZero;

	frc::SmartDashboard::PutBoolean("SwitchPosition", elevatorState == kSwitch);
	frc::SmartDashboard::PutBoolean("ScaleLowPosition", elevatorState == kScaleLow);
	frc::SmartDashboard::PutBoolean("ScaleNormalPosition", elevatorState == kScaleNormal);
	frc::SmartDashboard::PutBoolean("ScaleHighPosition", elevatorState == kScaleHigh);
	frc::SmartDashboard::PutBoolean("Zero", elevatorState == kZero);
	frc::SmartDashboard::PutBoolean("DrivingDown", elevatorState == kDrivingDown);
	frc::SmartDashboard::PutBoolean("DrivingUp", elevatorState == kDrivingUp);
	frc::SmartDashboard::PutBoolean("Holding", elevatorState == kHolding);

	frc::SmartDashboard::PutNumber("elevatorState", elevatorState);
}

void InstrumentCommand::finish() {
	CommandBase::finish();
}

void InstrumentCommand::disable(){}
