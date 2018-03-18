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

enum class AutonomousScoringStrategy {
	kNone
	, kSwitch
	, kScale
	, kSwitchAndScale
};

class Robot: public frc::TimedRobot {
/*	frc::LiveWindow& liveWindow = *frc::LiveWindow::GetInstance();
	frc::Preferences* preferences = frc::Preferences::GetInstance(); */
	SendableChooser<RobotStartPositions> startPositionChooser;
	SendableChooser<AutonomousScoringStrategy> scoringStrategyChooser;

	OI oi{};
//	Elevator elevator{};
	Drivebase drivebase{};
	Intake intake{};
	PneumaticSystem pneumaticSystem{};
	DrivebaseEncoderSensors encoderSensors{&drivebase};
	DrivebaseGyroSensor gyroSensor{&drivebase};
	Limelight limelight{};
	ClimberSystem climberSystem{};
	FieldData fieldData{};

	TankDriveCommand tankDriveCommand{&drivebase, &oi};
	PneumaticGripperCommand pneumaticGripperCommand{&intake, &oi};
//	ElevatorPositionCommand elevatorPositionCommand{&elevator, 0.35, 0, 0.15};
//	JoystickElevatorCommand joystickElevatorCommand{&elevator, &oi, &elevatorPositionCommand};

//  TrackPositionCommand positionCommand{&drivebaseSensors};
	Turn__DegreesCommand turn__DegreesCommand{90, &drivebase, &gyroSensor};
//	AimToTargetCommand aimToTargetCommand{&drivebase, &limelight, limelightMap::PipeLine::kPipeline0};
	InstrumentCommand instrumentCommand{&oi, &intake};
	Drive__FeetCommand driveFeetCommand{10,&drivebase,&encoderSensors,&gyroSensor};
	JoystickClimberCommand climberCommand{&oi, &climberSystem};

	auton::Wait1Wait3Wait2 wait1wait3wait2{};
	auton::Drive10Turn90Drive5 drive10turn90drive5{&drivebase, &encoderSensors, &gyroSensor};

	auton::CrossAutonLine crossAutonLine{&drivebase, &encoderSensors, &gyroSensor};
	auton::ScoreSwitchFromCenter scoreLeftSwitchFromCenter{&drivebase, &encoderSensors, &gyroSensor, SwitchScalePositions::kLeft};
	auton::ScoreSwitchFromCenter scoreRightSwitchFromCenter{&drivebase, &encoderSensors, &gyroSensor, SwitchScalePositions::kRight};
	auton::SequenceBase* sequenceToExecute;

public:

	void RobotInit() {
		startPositionChooser.AddObject("Left", RobotStartPositions::kLeft);
		startPositionChooser.AddObject("Center", RobotStartPositions::kCenter);
		startPositionChooser.AddObject("Right", RobotStartPositions::kRight);

		scoringStrategyChooser.AddObject("Cross Auton Line", AutonomousScoringStrategy::kNone);
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

		RobotStartPositions startPosition = startPositionChooser.GetSelected();
		AutonomousScoringStrategy scoringStrategy = scoringStrategyChooser.GetSelected();

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
	}

	void AutonomousPeriodic() override {
		sequenceToExecute->execute();
	}

	void TeleopInit() override {
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
		//std::cout << "I am disabled\n";
	}
};

START_ROBOT_CLASS(Robot)
