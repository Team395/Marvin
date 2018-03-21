#include <iostream>
#include <memory>
#include <string>
#include <list>

#include <TimedRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SmartDashboard.h>
#include <SmartDashboard/SendableChooser.h>

#include <Systems/Systems.h>
#include <Commands/Commands.h>
#include <Sequences/Sequences.h>

#include <Libraries/LimelightMap.h>
#include <OI.h>
#include <Preferences.h>
#include <ctre/Phoenix.h>

#include <sstream>

enum class RobotStartPositions {
	kLeft
	, kRight
	, kCenter
};

std::string stringifyRobotStartPositions(RobotStartPositions position) {
	switch(position) {
		case RobotStartPositions::kLeft:
			return "LEFT";
			break;
		case RobotStartPositions::kRight:
			return "RIGHT";
			break;
		case RobotStartPositions::kCenter:
			return "CENTER";
			break;
		default:
			return "";
	}
}

enum class AutonomousScoringStrategy {
	kNone
	, kSwitch
	, kScale
	, kSwitchAndScale
};

std::string stringifyAutonomousScoringStrategy(AutonomousScoringStrategy strategy) {
	switch(strategy) {
		case AutonomousScoringStrategy::kNone:
			return "NONE";
			break;
		case AutonomousScoringStrategy::kSwitch:
			return "SWITCH";
			break;
		case AutonomousScoringStrategy::kScale:
			return "SCALE";
			break;
		case AutonomousScoringStrategy::kSwitchAndScale:
			return "SWITCH AND SCALE";
			break;
		default:
			return "";
	}
}

class Robot: public frc::TimedRobot {
/*	frc::LiveWindow& liveWindow = *frc::LiveWindow::GetInstance();
	frc::Preferences* preferences = frc::Preferences::GetInstance(); */
	SendableChooser<RobotStartPositions> startPositionChooser;
	SendableChooser<AutonomousScoringStrategy> scoringStrategyChooser;

	OI oi{};
	Elevator elevator{};
	Drivebase drivebase{};
	Intake intake{};
	PneumaticSystem pneumaticSystem{};
	DrivebaseEncoderSensors encoderSensors{&drivebase};
	DrivebaseGyroSensor gyroSensor{&drivebase};
	Limelight limelight{};
	ClimberSystem climberSystem{};
	FieldData fieldData{};

	TankDriveCommand tankDriveCommand{&drivebase, &oi};
	PneumaticGripperCommand pneumaticGripperCommand{&intake, &elevator, &oi};
//	ElevatorPositionCommand elevatorPositionCommand{&elevator, 0.35, 0, 0.15};
//	JoystickElevatorCommand joystickElevatorCommand{&elevator, &oi, &elevatorPositionCommand};

//  TrackPositionCommand positionCommand{&drivebaseSensors};
	Turn__DegreesCommand turn__DegreesCommand{45, &drivebase, &gyroSensor};
//	AimToTargetCommand aimToTargetCommand{&drivebase, &limelight, limelightMap::PipeLine::kPipeline0};
	InstrumentCommand instrumentCommand{&oi, &intake};
	Drive__FeetCommand driveFeetCommand{10,&drivebase,&encoderSensors,&gyroSensor};
	JoystickClimberCommand climberCommand{&oi, &climberSystem};

	auton::Wait1Wait3Wait2 wait1wait3wait2{};
	auton::Drive10Turn90Drive5 drive10turn90drive5{&drivebase, &encoderSensors, &gyroSensor};

	auton::CrossAutonLine crossAutonLine{&drivebase, &encoderSensors, &gyroSensor, &pneumaticGripperCommand};
	auton::ScoreSwitchFromCenter scoreLeftSwitchFromCenter{&drivebase, &encoderSensors, &gyroSensor, SwitchScalePositions::kLeft};
	auton::ScoreSwitchFromCenter scoreRightSwitchFromCenter{&drivebase, &encoderSensors, &gyroSensor, SwitchScalePositions::kRight};
	auton::SequenceBase* sequenceToExecute;

	RobotStartPositions startPosition;
	AutonomousScoringStrategy scoringStrategy;

public:

	void RobotInit() {
		startPositionChooser.AddDefault("Left", RobotStartPositions::kLeft);
		startPositionChooser.AddObject("Center", RobotStartPositions::kCenter);
		startPositionChooser.AddObject("Right", RobotStartPositions::kRight);

		scoringStrategyChooser.AddDefault("Cross Auton Line", AutonomousScoringStrategy::kNone);
		scoringStrategyChooser.AddObject("Score in Switch", AutonomousScoringStrategy::kSwitch);
		scoringStrategyChooser.AddObject("Score in Scale", AutonomousScoringStrategy::kScale);
		scoringStrategyChooser.AddObject("Score in Switch and Scale", AutonomousScoringStrategy::kSwitchAndScale);

		SmartDashboard::PutData("Scoring Strategy", &scoringStrategyChooser);
		SmartDashboard::PutData("Start Position", &startPositionChooser);
	}

	void DisabledInit() {
	}

	void AutonomousInit() override {
		fieldData.readSwitchScalePositions();

		SwitchScalePositions homeSwitchPosition = fieldData.getHomeSwitchPosition();
		SwitchScalePositions scalePosition = fieldData.getScalePosition();

		switch(scoringStrategy) {
			case AutonomousScoringStrategy::kNone:
				sequenceToExecute = &crossAutonLine;
				break;
			case AutonomousScoringStrategy::kSwitch:
				switch(startPosition) {
					case RobotStartPositions::kCenter:
						switch(homeSwitchPosition) {
							case SwitchScalePositions::kLeft:
								sequenceToExecute = &scoreLeftSwitchFromCenter;
								break;
							case SwitchScalePositions::kRight:
								sequenceToExecute = &scoreRightSwitchFromCenter;
								break;
							case SwitchScalePositions::kUnknown:
								//TODO: should not score or raise elevator. maybe define this behavior with a function/setter?
								sequenceToExecute = &scoreLeftSwitchFromCenter;
								break;
						}
						break;
					case RobotStartPositions::kLeft:
						break;
					case RobotStartPositions::kRight:
						break;
				}
				break;
			case AutonomousScoringStrategy::kScale:
				break;
			case AutonomousScoringStrategy::kSwitchAndScale:
				break;
		}

		sequenceToExecute->initSequence();
		climberSystem.lockClimber();
		SmartDashboard::PutBoolean("Auton Complete", false);
	}

	void AutonomousPeriodic() override {
		sequenceToExecute->execute();
		if(sequenceToExecute->sequenceState == CommandState::kFinished){
			SmartDashboard::PutBoolean("Auton Complete", true);
		}
	}

	void TeleopInit() override {
		if(sequenceToExecute) {
			sequenceToExecute->disable();
		}

		limelight.setLedMode(limelightMap::LedMode::kOff);
		limelight.setCamMode(limelightMap::CamMode::kDriverCamera);

		tankDriveCommand.init();
		pneumaticGripperCommand.init();
//		elevatorPositionCommand.init();
//		joystickElevatorCommand.init();

		turn__DegreesCommand.init();
//		positionCommand.init();
//		aimToTargetCommand.init();
		instrumentCommand.init();
		driveFeetCommand.init();
		climberCommand.init();
		climberSystem.lockClimber();
	}

	void TeleopPeriodic() override {
		frc::SmartDashboard::PutNumber("XboxPOV", oi.xboxController.GetPOV(0));
#if 1
		if(oi.getTurnButton()){
			turn__DegreesCommand.update();
		}
		else {
			turn__DegreesCommand.disable();
			turn__DegreesCommand.startNewturn();
		}

		if(oi.getLeftStick()->GetRawButton(2))
		{
			driveFeetCommand.update();
		}
		else{
			driveFeetCommand.disable();
			driveFeetCommand.startNewMovement();
		}

		if(!oi.getTurnButton() && !oi.getLeftStick()->GetRawButton(2)) {
			tankDriveCommand.update();
		}
#else
//		tankDriveCommand.update();
//		instrumentCommand.update();
#endif

//		limelight.refreshNetworkTableValues();
//		limelight.printToSmartDashboard();

		pneumaticGripperCommand.update();
		instrumentCommand.update();
		climberCommand.update();
//		joystickElevatorCommand.update();
//		elevatorPositionCommand.update();
	}

	void TestPeriodic() override {

	}

	void DisabledPeriodic() override {
		startPosition = startPositionChooser.GetSelected();
		scoringStrategy = scoringStrategyChooser.GetSelected();

		frc::SmartDashboard::PutString("StartPos", stringifyRobotStartPositions(startPosition));
		frc::SmartDashboard::PutString("ScoringStrat", stringifyAutonomousScoringStrategy(scoringStrategy));
	}
};

START_ROBOT_CLASS(Robot)
