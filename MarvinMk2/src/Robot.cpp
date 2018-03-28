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
	ElevatorPositionCommand elevatorPositionCommand{&elevator, 0.35, 0, 0.15};
	JoystickElevatorCommand joystickElevatorCommand{&elevator, &oi, &elevatorPositionCommand};

//  TrackPositionCommand positionCommand{&drivebaseSensors};
	Turn__DegreesCommand turn__DegreesCommand{90, &drivebase, &gyroSensor};
//	AimToTargetCommand aimToTargetCommand{&drivebase, &limelight, limelightMap::PipeLine::kPipeline0};
	InstrumentCommand instrumentCommand{&oi, &intake};
	Drive__FeetCommand driveFeetCommand{5,&drivebase,&encoderSensors,&gyroSensor};
	JoystickClimberCommand climberCommand{&oi, &climberSystem};
	TestCommand testCommand{1};

	auton::Wait1Wait3Wait2 wait1wait3wait2{};
	auton::Drive10Turn90Drive5 drive10turn90drive5{&drivebase, &encoderSensors, &gyroSensor};

	auton::CrossAutonLine crossAutonLine{&drivebase, &encoderSensors, &gyroSensor, &pneumaticGripperCommand};
	auton::ScoreSwitchFromCenter scoreLeftSwitchFromCenter{&drivebase, &encoderSensors, &gyroSensor,
		SwitchScalePositions::kLeft, &elevatorPositionCommand, &pneumaticGripperCommand};
	auton::ScoreSwitchFromCenter scoreRightSwitchFromCenter{&drivebase, &encoderSensors, &gyroSensor,
		SwitchScalePositions::kRight, &elevatorPositionCommand, &pneumaticGripperCommand};
	auton::ScoreLeftFromLeft scoreLeftFromLeft{&drivebase, &encoderSensors, &gyroSensor,
		&elevatorPositionCommand, &pneumaticGripperCommand, true};
	auton::ScoreLeftFromLeft scoreRightFromRight{&drivebase, &encoderSensors, &gyroSensor,
		&elevatorPositionCommand, &pneumaticGripperCommand, false};

	//first bool is true if started on left, false if right
	//second bool is true if scoring, false if not scoring
	auton::ScaleLeftFromLeft scaleLeftFromLeft{&drivebase, &encoderSensors, &gyroSensor,
		&elevatorPositionCommand, &pneumaticGripperCommand, true, true};
	auton::ScaleLeftFromLeft scaleRightFromRight{&drivebase, &encoderSensors, &gyroSensor,
		&elevatorPositionCommand, &pneumaticGripperCommand, false, true};

	auton::ScaleLeftFromLeft driveScaleLeftFromLeft{&drivebase, &encoderSensors, &gyroSensor,
		&elevatorPositionCommand, &pneumaticGripperCommand, true, false};
	auton::ScaleLeftFromLeft driveScaleRightFromRight{&drivebase, &encoderSensors, &gyroSensor,
		&elevatorPositionCommand, &pneumaticGripperCommand, false, false};

	auton::PitTestSequence pitTestSequence;
	auton::SequenceBase* sequenceToExecute = 0;

	RobotStartPositions startPosition;
	AutonomousScoringStrategy scoringStrategy;

	bool autonomousComplete = false;

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

		tankDriveCommand.init();
		pneumaticGripperCommand.init();
		elevatorPositionCommand.init();
		joystickElevatorCommand.init();

		turn__DegreesCommand.init();
//		positionCommand.init();
//		aimToTargetCommand.init();
		instrumentCommand.init();
		climberCommand.init();
		climberSystem.lockClimber();
		elevatorPositionCommand.setSetpoint(0);
	}

	void DisabledInit() {
	}

	void AutonomousInit() override {
#if 0
		fieldData.readSwitchScalePositions();
		driveFeetCommand.init();

//		sequenceToExecute->initSequence();
//		climberSystem.lockClimber();
#else
		fieldData.readSwitchScalePositions();

		SwitchScalePositions homeSwitchPosition = fieldData.getHomeSwitchPosition();
		SwitchScalePositions scalePosition = fieldData.getScalePosition();

#if 1
		switch(startPosition) {
		case RobotStartPositions::kLeft:
			if(scalePosition == SwitchScalePositions::kLeft) {
							std::cout << "AutonomousInit():  scale left" << std::endl;
							sequenceToExecute = &scaleLeftFromLeft;
			} else if(homeSwitchPosition == SwitchScalePositions::kLeft) {
//				std::cout << "AutonomousInit():  switch left" << std::endl;
//				sequenceToExecute = &scoreLeftFromLeft;
				sequenceToExecute = &driveScaleLeftFromLeft;
			}  else {
				sequenceToExecute = &crossAutonLine;
			}
			break;

		case RobotStartPositions::kRight:
			if(scalePosition == SwitchScalePositions::kRight) {
				std::cout << "AutonomousInit():  scale left" << std::endl;
				sequenceToExecute = &scaleRightFromRight;
			} else if(homeSwitchPosition == SwitchScalePositions::kRight) {
//				std::cout << "AutonomousInit():  switch left" << std::endl;
//				sequenceToExecute = &scoreRightFromRight;
				sequenceToExecute = &driveScaleRightFromRight;
			}  else {
				sequenceToExecute = &crossAutonLine;
			}
			break;
		default:
			sequenceToExecute = &crossAutonLine;
		};
#else
		switch(scoringStrategy) {
			case AutonomousScoringStrategy::kNone:
				std::cout << "AutonomousInit():  AutonomousScoringStrategy::kNone" << std::endl;
				sequenceToExecute = &crossAutonLine;
				break;
			case AutonomousScoringStrategy::kSwitch:
				switch(startPosition) {
					case RobotStartPositions::kCenter:
						switch(homeSwitchPosition) {
							case SwitchScalePositions::kLeft:
								std::cout << "AutonomousInit():  AutonomousScoringStrategy::kSwitch, RobotStartPositions::kCenter, SwitchScalePositions::kLeft" << std::endl;
								sequenceToExecute = &scoreLeftSwitchFromCenter;
								break;
							case SwitchScalePositions::kRight:
								std::cout << "AutonomousInit():  AutonomousScoringStrategy::kSwitch, RobotStartPositions::kCenter, SwitchScalePositions::kRight" << std::endl;
								sequenceToExecute = &scoreRightSwitchFromCenter;
								break;
							case SwitchScalePositions::kUnknown:
								std::cout << "AutonomousInit():  AutonomousScoringStrategy::kSwitch, RobotStartPositions::kCenter, SwitchScalePositions::kUnknown" << std::endl;
								//TODO: should not score or raise elevator. maybe define this behavior with a function/setter?
								sequenceToExecute = &scoreLeftSwitchFromCenter;
								break;
						}
						break;
					case RobotStartPositions::kLeft:
						std::cout << "AutonomousInit():  AutonomousScoringStrategy::kSwitch, RobotStartPositions::kLeft" << std::endl;
						switch(homeSwitchPosition){
							case(SwitchScalePositions::kLeft):
								sequenceToExecute = &scoreLeftFromLeft;
								break;
							default:
								sequenceToExecute= &crossAutonLine;
								break;
						}
						break;
					case RobotStartPositions::kRight:
						std::cout << "AutonomousInit():  AutonomousScoringStrategy::kSwitch, RobotStartPositions::kRight" << std::endl;
						break;
				}
				break;
			case AutonomousScoringStrategy::kScale:
				std::cout << "AutonomousInit():  AutonomousScoringStrategy::kScale" << std::endl;
				break;
			case AutonomousScoringStrategy::kSwitchAndScale:
				std::cout << "AutonomousInit():  AutonomousScoringStrategy::kSwitchAndScale" << std::endl;
				break;
		}
#endif

		if(!sequenceToExecute){
			std::cout << "sequenceToExecute was null" << std::endl;
		}

		sequenceToExecute->initSequence();

		SmartDashboard::PutBoolean("Auton Complete", false);
		elevatorPositionCommand.setSetpoint(0);
#endif
	}

	void AutonomousPeriodic() override {
#if 0
		SwitchScalePositions homeSwitchPosition = fieldData.getHomeSwitchPosition();
//		SwitchScalePositions scalePosition = fieldData.getScalePosition();

		switch(scoringStrategy) {
			case AutonomousScoringStrategy::kNone:
				std::cout << "AutonomousInit():  AutonomousScoringStrategy::kNone" << std::endl;
				crossAutonLine.execute();
				if(crossAutonLine.sequenceState) autonomousComplete = true;
				break;
			case AutonomousScoringStrategy::kSwitch:
				switch(startPosition) {
					case RobotStartPositions::kCenter:
						switch(homeSwitchPosition) {
							case SwitchScalePositions::kLeft:
								std::cout << "AutonomousInit():  AutonomousScoringStrategy::kSwitch, RobotStartPositions::kCenter, SwitchScalePositions::kLeft" << std::endl;
								scoreLeftSwitchFromCenter.execute();
								if(scoreLeftSwitchFromCenter.sequenceState) autonomousComplete = true;
								break;
							case SwitchScalePositions::kRight:
								std::cout << "AutonomousInit():  AutonomousScoringStrategy::kSwitch, RobotStartPositions::kCenter, SwitchScalePositions::kRight" << std::endl;
								scoreRightSwitchFromCenter.execute();
								if(scoreRightSwitchFromCenter.sequenceState) autonomousComplete = true;
								break;
							case SwitchScalePositions::kUnknown:
								std::cout << "AutonomousInit():  AutonomousScoringStrategy::kSwitch, RobotStartPositions::kCenter, SwitchScalePositions::kUnknown" << std::endl;
								//TODO: should not score or raise elevator. maybe define this behavior with a function/setter?
								scoreLeftSwitchFromCenter.execute();
								if(scoreLeftSwitchFromCenter.sequenceState) autonomousComplete = true;
								break;
						}
						break;
					case RobotStartPositions::kLeft:
						std::cout << "AutonomousInit():  AutonomousScoringStrategy::kSwitch, RobotStartPositions::kLeft" << std::endl;
						scoreLeftFromLeft.execute();
						if(scoreLeftFromLeft.sequenceState) autonomousComplete = true;
						break;
					case RobotStartPositions::kRight:
						std::cout << "AutonomousInit():  AutonomousScoringStrategy::kSwitch, RobotStartPositions::kRight" << std::endl;
						autonomousComplete = true;
						break;
				}
				break;
			case AutonomousScoringStrategy::kScale:
				std::cout << "AutonomousInit():  AutonomousScoringStrategy::kScale" << std::endl;
				autonomousComplete = true;
				break;
			case AutonomousScoringStrategy::kSwitchAndScale:
				std::cout << "AutonomousInit():  AutonomousScoringStrategy::kSwitchAndScale" << std::endl;
				autonomousComplete = true;
				break;
		}
#endif
#if 1
		if(sequenceToExecute) {
			sequenceToExecute->execute();
			if(sequenceToExecute->sequenceState == CommandState::kFinished){
				SmartDashboard::PutBoolean("Auton Complete", true);
			}
		}

		elevatorPositionCommand.update();
#endif

#if 0 //FULL STUPID
		if(driveFeetCommand.getCommandState() == CommandState::kNotStarted) {
			driveFeetCommand.init();
		}
		if(driveFeetCommand.getCommandState() == CommandState::kInitialized) {
			driveFeetCommand.update();
			}
		if(driveFeetCommand.getCommandState() == CommandState::kFinished) {
			autonomousComplete = true;
		}
#endif

		SmartDashboard::PutBoolean("Auton Complete", autonomousComplete);
	}

	void TeleopInit() override {
//		SwitchScalePositions homeSwitchPosition = fieldData.getHomeSwitchPosition();
//		SwitchScalePositions scalePosition = fieldData.getScalePosition();

#if 0
		switch(scoringStrategy) {
			case AutonomousScoringStrategy::kNone:
				crossAutonLine.disable();
				break;
			case AutonomousScoringStrategy::kSwitch:
				switch(startPosition) {
					case RobotStartPositions::kCenter:
						switch(homeSwitchPosition) {
							case SwitchScalePositions::kLeft:
								scoreLeftSwitchFromCenter.disable();
								break;
							case SwitchScalePositions::kRight:
								scoreRightSwitchFromCenter.disable();
								break;
							case SwitchScalePositions::kUnknown:
								scoreLeftSwitchFromCenter.disable();
								break;
						}
						break;
					case RobotStartPositions::kLeft:
						scoreLeftFromLeft.disable();
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
#endif
#if 0 //FULL STUPID
		driveFeetCommand.disable();
#endif
		if(sequenceToExecute) {
			sequenceToExecute->disable();
		}

		limelight.setLedMode(limelightMap::LedMode::kOff);
		limelight.setCamMode(limelightMap::CamMode::kDriverCamera);
	}

	void TeleopPeriodic() override {
//		frc::SmartDashboard::PutNumber("XboxPOV", oi.xboxController.GetPOV(0));
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
		tankDriveCommand.update();
		instrumentCommand.update();
#endif

//		limelight.refreshNetworkTableValues();
//		limelight.printToSmartDashboard();

		pneumaticGripperCommand.update();

		climberCommand.update();
		joystickElevatorCommand.update();
		elevatorPositionCommand.update();
	}

	void TestPeriodic() override {

	}

	void DisabledPeriodic() override {
		startPosition = startPositionChooser.GetSelected();
		scoringStrategy = scoringStrategyChooser.GetSelected();

		frc::SmartDashboard::PutString("StartPos", stringifyRobotStartPositions(startPosition));
		frc::SmartDashboard::PutString("ScoringStrat", stringifyAutonomousScoringStrategy(scoringStrategy));
		intake.reset();
	}
};

START_ROBOT_CLASS(Robot)
