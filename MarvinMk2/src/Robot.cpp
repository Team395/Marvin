#include <iostream>
#include <memory>
#include <string>
#include <list>

#include <TimedRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SmartDashboard.h>

#include <Systems/Systems.h>
#include <Commands/Commands.h>
#include <Sequences/Sequences.h>

#include <Libraries/LimelightMap.h>
#include <OI.h>
#include <Preferences.h>
#include <ctre/Phoenix.h>

#include <sstream>

class Robot: public frc::TimedRobot {
/*	frc::LiveWindow& liveWindow = *frc::LiveWindow::GetInstance();
	frc::Preferences* preferences = frc::Preferences::GetInstance(); */
	OI oi{};

//	Elevator elevator{};
	Drivebase drivebase{};
//	Intake intake{};
//	PneumaticSystem pneumaticSystem{};
	DrivebaseSensors drivebaseSensors{&drivebase};
	Limelight limelight{};


	TankDriveCommand tankDriveCommand{&drivebase, &oi};
//	PneumaticGripperCommand pneumaticGripperCommand{&intake, &oi};
//	ElevatorPositionCommand elevatorPositionCommand{&elevator, 0.35, 0, 0.15};
//	JoystickElevatorCommand joystickElevatorCommand{&elevator, &oi, &elevatorPositionCommand};

//  TrackPositionCommand positionCommand{&drivebaseSensors};
	Turn__DegreesCommand turn__DegreesCommand{&drivebase, &drivebaseSensors, &oi};
//	AimToTargetCommand aimToTargetCommand{&drivebase, &limelight, limelightMap::PipeLine::kPipeline0};

	/*
	std::list<CommandBase*> commandQueue;
	std::list<CommandBase*>::iterator commandQueueIterator;

	void processCommand(CommandBase* command){
		if(command->getCommandState() == CommandState::kNotStarted) {
			command->init();
		}

		command->update();

		if(command->getCommandState() == CommandState::kFinished) {
			commandQueueIterator++;
		}
	}*/

	int loopCount = 0;
	int timesInMotionMagic = 0;

public:

	void RobotInit() {
		//limelight.setLedMode(limelightMap::LedMode::kOff);
		//limelight.setCamMode(limelightMap::CamMode::kDriverCamera);
	}

	void DisabledInit() {
	}

	void AutonomousInit() override {
//		commandQueue = auton::Wait1Wait3Wait2().getCommandQueue();
//		commandQueueIterator = commandQueue.begin();
	}

	void AutonomousPeriodic() override {
//		if(commandQueueIterator == commandQueue.end()) return;
//		processCommand(*commandQueueIterator);
	}

	void TeleopInit() override {
		limelight.setLedMode(limelightMap::LedMode::kOff);
		limelight.setCamMode(limelightMap::CamMode::kDriverCamera);

		tankDriveCommand.init();
//		pneumaticGripperCommand.init();
//		elevatorPositionCommand.init();
//		joystickElevatorCommand.init();

		turn__DegreesCommand.init();
//		positionCommand.init();
//		aimToTargetCommand.init();

		drivebase.getLeftMaster()->
				ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative
						, 0
						, 10);
		drivebase.getLeftMaster()->SetStatusFramePeriod(StatusFrameEnhanced::Status_13_Base_PIDF0
				, 10
				, 10);
		drivebase.getLeftMaster()->SetStatusFramePeriod(StatusFrameEnhanced::Status_10_MotionMagic
				, 10
				, 10);

		drivebase.getLeftMaster()->ConfigNominalOutputForward(0, 10);
		drivebase.getLeftMaster()->ConfigNominalOutputReverse(0, 10);
		drivebase.getLeftMaster()->ConfigPeakOutputForward(1, 10);
		drivebase.getLeftMaster()->ConfigPeakOutputReverse(-1, 10);

		drivebase.getLeftMaster()->SelectProfileSlot(0, 0);
		drivebase.getLeftMaster()->Config_kF(0, 0, 10);
		drivebase.getLeftMaster()->Config_kP(0, 0, 10);
		drivebase.getLeftMaster()->Config_kI(0, 0, 10);
		drivebase.getLeftMaster()->Config_kD(0, 0, 10);

		drivebase.getLeftMaster()->ConfigMotionCruiseVelocity(0, 10);
		drivebase.getLeftMaster()->ConfigMotionAcceleration(0, 10);

		drivebase.getLeftMaster()->SetSelectedSensorPosition(0, 0, 10);
	}

	void TeleopPeriodic() override {
#if 0
		if(oi.getTurnButton()){
			turn__DegreesCommand.update();
		}
		else{
			turn__DegreesCommand.disable();
			turn__DegreesCommand.startNewturn();
			tankDriveCommand.update();
			//positionCommand.update();
		}
#endif
		tankDriveCommand.update();

/*		if(!oi.getTurnButton()){
			aimToTargetCommand.disable();
			aimToTargetCommand.startNewTurn();
			arcadeDrive.update();
		}
		else{
			aimToTargetCommand.update();
		}
*/
//		SmartDashboard::PutNumber("Elevator Throttle", oi.getElevatorThrottle());
//		SmartDashboard::PutBoolean("Claw Position", oi.getIntakeThrottle());
		//SmartDashboard::PutBoolean("topLimit", elevator.topPressed());
		//SmartDashboard::PutBoolean("bottomLimit", elevator.bottomPressed());

//		limelight.refreshNetworkTableValues();
//		limelight.printToSmartDashboard();

//		tankDriveCommand.update();
//		pneumaticGripperCommand.update();
//		joystickElevatorCommand.update();
//		elevatorPositionCommand.update();

#if 0
		/************************************/
		/*********** MOTION MAGIC ***********/
		/************************************/
		std::ostringstream outputStream;
		double leftYstick = oi.getDriveLeft();

		double motorOutput = drivebase.getLeftMaster()->GetMotorOutputPercent();
		outputStream << "\tOut%:" << motorOutput;
		outputStream << "\tVel:" << drivebase.getLeftMaster()->GetSelectedSensorVelocity(0);

		if(oi.getLeftStick()->GetTrigger()) {
			drivebase.getLeftMaster()->SetSelectedSensorPosition(0, 0, 10);

			//Motion Magic - 4096 ticks/rev * 10 Rotations in either direction
			double targetPos = leftYstick * 4096 * 10.0;
			drivebase.getLeftMaster()->Set(ControlMode::MotionMagic, targetPos);

			outputStream << "\terr:" << drivebase.getLeftMaster()->GetClosedLoopError(0);
			outputStream << "\ttrg:" << targetPos;
		}

		frc::SmartDashboard::PutNumber("SensorVel", drivebase.getLeftMaster()->GetSelectedSensorVelocity(0));
		frc::SmartDashboard::PutNumber("SensorPos", drivebase.getLeftMaster()->GetSelectedSensorPosition(0));
		frc::SmartDashboard::PutNumber("MotorOutputPercent", drivebase.getLeftMaster()->GetMotorOutputPercent());
		frc::SmartDashboard::PutNumber("ClosedLoopError", drivebase.getLeftMaster()->GetClosedLoopError(0));

		if(drivebase.getLeftMaster()->GetControlMode() == ControlMode::MotionMagic){
			++timesInMotionMagic;
		} else {
			timesInMotionMagic = 0;
		}

		if(timesInMotionMagic > 10) {
			frc::SmartDashboard::PutNumber("ClosedLoopTarget", drivebase.getLeftMaster()->GetClosedLoopTarget(0));
			frc::SmartDashboard::PutNumber("ActTrajVelocity", drivebase.getLeftMaster()->GetActiveTrajectoryVelocity());
			frc::SmartDashboard::PutNumber("ActTrajPosition", drivebase.getLeftMaster()->GetActiveTrajectoryPosition());
			frc::SmartDashboard::PutNumber("ActTrajHeading", drivebase.getLeftMaster()->GetActiveTrajectoryHeading());
		}
		outputStream << "\n";
		/************************************/
		/*********** MOTION MAGIC ***********/
		/************************************/

		if(++loopCount > 10) {
			loopCount = 0;
			std::cout << outputStream.str();
		}

		outputStream.str() = "";
#endif
	}

	void TestPeriodic() override {

	}
};

START_ROBOT_CLASS(Robot)
