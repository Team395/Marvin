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
#include <AutonomousEnums.h>

#include <Libraries/LimelightMap.h>
#include <OI.h>
#include <Preferences.h>
#include <ctre/Phoenix.h>

#include <sstream>

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
#if 0

	SendableChooser<RobotStartPositions> startPositionChooser;
	SendableChooser<AutonomousScoringStrategy> scoringStrategyChooser;
#endif

	NewTalonMap newTalonMap{};
	OI oi{};
	Elevator elevator{&newTalonMap};
	Drivebase drivebase{&newTalonMap};
	Intake intake{};
	PneumaticSystem pneumaticSystem{};
	DrivebaseEncoderSensors encoderSensors{&drivebase,&newTalonMap};
	DrivebaseGyroSensor gyroSensor{&drivebase,&newTalonMap};
	Limelight limelight{};
	ClimberSystem climberSystem{};
	FieldData fieldData{};
	AutonomousChooser chooserSystem{};

	TankDriveCommand tankDriveCommand{&drivebase, &oi};
	PneumaticGripperCommand pneumaticGripperCommand{&intake, &elevator, &oi};
	ElevatorPositionCommand elevatorPositionCommand{&elevator, 0.15, 0, 0.0225}; //TODO tune this
	JoystickElevatorCommand joystickElevatorCommand{&elevator, &oi, &elevatorPositionCommand};

//  TrackPositionCommand positionCommand{&drivebaseSensors};
	Turn__DegreesCommand turn__DegreesCommand{90, &drivebase, &gyroSensor, 0};
//	AimToTargetCommand aimToTargetCommand{&drivebase, &limelight, limelightMap::PipeLine::kPipeline0};
	InstrumentCommand instrumentCommand{&oi, &intake};
	Drive__FeetCommand driveFeetCommand{5,&drivebase,&encoderSensors,&gyroSensor,0};
	JoystickClimberCommand climberCommand{&oi, &climberSystem};
	TestCommand testCommand{1};

	auton::Wait1Wait3Wait2 wait1wait3wait2{};
	auton::Drive10Turn90Drive5 drive10turn90drive5{&drivebase, &encoderSensors, &gyroSensor};

	auton::CrossAutonLine crossAutonLine{&drivebase, &encoderSensors, &gyroSensor, &pneumaticGripperCommand};
	auton::ScoreSwitchFromCenter scoreLeftSwitchFromCenter{&drivebase, &encoderSensors, &gyroSensor,
		SwitchScalePositions::kLeft, &elevatorPositionCommand, &pneumaticGripperCommand};
	auton::ScoreSwitchFromCenter scoreRightSwitchFromCenter{&drivebase, &encoderSensors, &gyroSensor,
		SwitchScalePositions::kRight, &elevatorPositionCommand, &pneumaticGripperCommand};
	auton::ScoreSwitchFromSide scoreSwitchFromSideLeft{&drivebase, &encoderSensors, &gyroSensor,
		&elevatorPositionCommand, &pneumaticGripperCommand, RobotStartPositions::kLeft};
	auton::ScoreSwitchFromSide scoreSwitchFromSideRight{&drivebase, &encoderSensors, &gyroSensor,
		&elevatorPositionCommand, &pneumaticGripperCommand, RobotStartPositions::kRight};

	auton::ScoreNearScaleFromSide scoreNearScaleFromLeft{&drivebase, &encoderSensors, &gyroSensor,
		&elevatorPositionCommand, &pneumaticGripperCommand, SwitchScalePositions::kLeft};
	auton::ScoreNearScaleFromSide scoreNearScaleFromRight{&drivebase, &encoderSensors, &gyroSensor,
		&elevatorPositionCommand, &pneumaticGripperCommand, SwitchScalePositions::kRight};

	auton::ScoreFarScaleFromSide scoreFarScaleFromLeft{&drivebase, &encoderSensors, &gyroSensor,
		&elevatorPositionCommand, &pneumaticGripperCommand, SwitchScalePositions::kRight};
	auton::ScoreFarScaleFromSide scoreFarScaleFromRight{&drivebase, &encoderSensors, &gyroSensor,
		&elevatorPositionCommand, &pneumaticGripperCommand, SwitchScalePositions::kLeft};


	auton::PitTestSequence pitTestSequence{&drivebase, &gyroSensor};
	auton::SequenceBase* sequenceToExecute = 0;

	RobotStartPositions startPosition;
	AutonomousScoringStrategy scoringStrategy;

	bool autonomousComplete = false;

public:

	void RobotInit() {
#if 0
		startPositionChooser.AddDefault("Left", RobotStartPositions::kLeft);
		startPositionChooser.AddObject("Center", RobotStartPositions::kCenter);
		startPositionChooser.AddObject("Right", RobotStartPositions::kRight);

		scoringStrategyChooser.AddDefault("Cross Auton Line", AutonomousScoringStrategy::kNone);
		scoringStrategyChooser.AddObject("Score in Switch", AutonomousScoringStrategy::kSwitch);
		scoringStrategyChooser.AddObject("Score in Scale", AutonomousScoringStrategy::kScale);
		scoringStrategyChooser.AddObject("Score in Switch and Scale", AutonomousScoringStrategy::kSwitchAndScale);

		SmartDashboard::PutData("Scoring Strategy", &scoringStrategyChooser);
		SmartDashboard::PutData("Start Position", &startPositionChooser);
#endif
		tankDriveCommand.init();
		pneumaticGripperCommand.init();
		elevatorPositionCommand.init();
		joystickElevatorCommand.init();

		turn__DegreesCommand.init();
//		positionCommand.init();
//		aimToTargetCommand.init();
		instrumentCommand.init();
		climberCommand.init();
		elevatorPositionCommand.setSetpoint(0);
		limelight.setLedMode(limelightMap::LedMode::kOff);
		limelight.setCamMode(limelightMap::CamMode::kDriverCamera);
	}

	void DisabledInit() {

	}

	void AutonomousInit() override {
		fieldData.readSwitchScalePositions();

		SwitchScalePositions homeSwitchPosition = fieldData.getHomeSwitchPosition();
		SwitchScalePositions scalePosition = fieldData.getScalePosition();


		if(scoringStrategy == AutonomousScoringStrategy::kNone){
			std::cout << "AutonomousInit():  AutonomousScoringStrategy::kNone" << std::endl;
			sequenceToExecute = &crossAutonLine;
		}
		else{
			switch(startPosition){
				case RobotStartPositions::kCenter:
					switch(homeSwitchPosition){
						case SwitchScalePositions::kLeft:
							std::cout << "AutonomousInit(): RobotStartPositions::kCenter, SwitchScalePositions::kLeft" << std::endl;
							sequenceToExecute = &scoreLeftSwitchFromCenter;
							break;
						case SwitchScalePositions::kRight:
							std::cout << "AutonomousInit(): RobotStartPositions::kCenter, SwitchScalePositions::kRight" << std::endl;
							sequenceToExecute = &scoreRightSwitchFromCenter;
							break;
						default:
							std::cout << "AutonomousInit(): RobotStartPositions::kCenter, SwitchScalePositions::defaukt" << std::endl;
							sequenceToExecute = &crossAutonLine;
							break;
					}
					break;
				case RobotStartPositions::kLeft:
					if(scoringStrategy == AutonomousScoringStrategy::kSwitch && homeSwitchPosition == SwitchScalePositions::kLeft){
						std::cout << "AutonomousInit(): RobotStartPositions::kLeft, homeSwitchPosition kLeft, AutonomousScoringStrategy::kSwitch" << std::endl;
						sequenceToExecute = &scoreSwitchFromSideLeft;
					} else if(scalePosition == SwitchScalePositions::kLeft){
						std::cout << "AutonomousInit(): RobotStartPositions::kLeft, scalePosition kLeft" << std::endl;
						sequenceToExecute = &scoreNearScaleFromLeft;
					} else {
						std::cout << "AutonomousInit(): RobotStartPositions::kLeft, scalePosition kRight" << std::endl;
						sequenceToExecute = &scoreFarScaleFromLeft;
					}
					break;
				case RobotStartPositions::kRight:
					if(scoringStrategy == AutonomousScoringStrategy::kSwitch && homeSwitchPosition == SwitchScalePositions::kRight){
						std::cout << "AutonomousInit(): RobotStartPositions::kRight, homeSwitchPosition kRight, AutonomousScoringStrategy::kSwitch" << std::endl;
						sequenceToExecute = &scoreSwitchFromSideRight;
					} else if(scalePosition == SwitchScalePositions::kRight){
						std::cout << "AutonomousInit(): RobotStartPositions::kRight, scalePosition kRight" << std::endl;
						sequenceToExecute = &scoreNearScaleFromRight;
					} else {
						std::cout << "AutonomousInit(): RobotStartPositions::kRight, scalePosition kLeft" << std::endl;
						sequenceToExecute = &scoreFarScaleFromRight;
					}
					break;
			}
		}

		if(!sequenceToExecute){
			std::cout << "sequenceToExecute was null" << std::endl;
			sequenceToExecute = &crossAutonLine;
		}

		//sequenceToExecute= &auton::PitTestSequence(&drivebase, &gyroSensor);
		sequenceToExecute->initSequence();

		SmartDashboard::PutBoolean("Auton Complete", false);
		elevatorPositionCommand.setSetpoint(0);
	}

	void AutonomousPeriodic() override {
		if(sequenceToExecute) {
			sequenceToExecute->execute();
			if(sequenceToExecute->sequenceState == CommandState::kFinished){
				SmartDashboard::PutBoolean("Auton Complete", true);
			}
		}

		elevatorPositionCommand.update();

		SmartDashboard::PutBoolean("Auton Complete", autonomousComplete);
	}

	void TeleopInit() override {
		if(sequenceToExecute) {
			sequenceToExecute->disable();
		}

		limelight.setLedMode(limelightMap::LedMode::kOff);
		limelight.setCamMode(limelightMap::CamMode::kDriverCamera);
	}

	void TeleopPeriodic() override {
//		frc::SmartDashboard::PutNumber("XboxPOV", oi.xboxController.GetPOV(0));
#if 0
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

		pneumaticGripperCommand.update();

		climberCommand.update();
		joystickElevatorCommand.update();
		elevatorPositionCommand.update();
	}

	void TestPeriodic() override {

	}

	void DisabledPeriodic() override {
		startPosition = chooserSystem.getRobotStartPosition();//startPositionChooser.GetSelected();
		scoringStrategy = chooserSystem.getAutonomousScoringStrategy();//scoringStrategyChooser.GetSelected();

		frc::SmartDashboard::PutString("StartPos", stringifyRobotStartPositions(startPosition));
		frc::SmartDashboard::PutString("ScoringStrat", stringifyAutonomousScoringStrategy(scoringStrategy));
		intake.reset();
	}
};

START_ROBOT_CLASS(Robot)
