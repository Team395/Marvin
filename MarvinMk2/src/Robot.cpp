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

class Robot: public frc::TimedRobot {
	frc::LiveWindow& liveWindow = *frc::LiveWindow::GetInstance();
	frc::Preferences* preferences = frc::Preferences::GetInstance();
	OI oi{};

	Elevator elevator{};
//	Drivebase drivebase{};
	Intake intake{};
	PneumaticSystem pneumaticSystem{};
//	DrivebaseSensors drivebaseSensors{&drivebase};
//	Limelight limelight{};


	//	TankDriveCommand tankDriveCommand{&drivebase, &oi};
	PneumaticGripperCommand pneumaticGripperCommand{&intake, &oi};
	ElevatorPositionCommand elevatorPositionCommand{&elevator, 0.35, 0, 0.15};
	JoystickElevatorCommand joystickElevatorCommand{&elevator, &oi, &elevatorPositionCommand};

//  TrackPositionCommand positionCommand{&drivebaseSensors};
//	Turn__DegreesCommand turn__DegreesCommand{&drivebase, &drivebaseSensors, &oi};
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

public:

	void RobotInit() {
//		limelight.setLedMode(limelightMap::LedMode::kOn);
	}

	void DisabledInit() {
		std::cout << "I AM DISABLEDDDDD\n";
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
//		tankDriveCommand.init();
		pneumaticGripperCommand.init();
		elevatorPositionCommand.init();
		joystickElevatorCommand.init();

//		turn__DegreesCommand.init();
//		positionCommand.init();
//		aimToTargetCommand.init();
	}

	void TeleopPeriodic() override {
//		if(oi.getTurnButton()){
//			turn__DegreesCommand.update();
//		}
//		else{
//			turn__DegreesCommand.disable();
//			turn__DegreesCommand.startNewturn();
//			tankDrive.update();
			//positionCommand.update();
//		}

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
		pneumaticGripperCommand.update();
		joystickElevatorCommand.update();
		elevatorPositionCommand.update();
	}

	void TestPeriodic() override {

	}
};

START_ROBOT_CLASS(Robot)
