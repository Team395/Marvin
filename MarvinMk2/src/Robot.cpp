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

class Robot: public frc::TimedRobot {
	frc::LiveWindow& m_lw = *frc::LiveWindow::GetInstance();
	Elevator elevator{};
	Drivebase drivebase{};
	Gyroscope gyroscope{&elevator};
//	Limelight limelight{};
//	Intake intake{};
//	PneumaticSystem pneumaticSystem{};

	OI oi{};

	TankDriveCommand tankDrive{&drivebase, &oi};
	JoystickElevatorCommand joystickElevator{&elevator, &oi};
	Turn__DegreesCommand turn__DegreesCommand{&drivebase, &gyroscope, &oi};
//	AimToTargetCommand aimToTargetCommand{&drivebase, &limelight, limelightMap::PipeLine::kPipeline0};
//	PneumaticGripperCommand pneumaticGripperCommand{&intake, &oi};

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
	}

public:

	void RobotInit() {
//		limelight.setLedMode(limelightMap::LedMode::kOn);
	}

	void AutonomousInit() override {
		commandQueue = auton::Wait1Wait3Wait2().getCommandQueue();
		commandQueueIterator = commandQueue.begin();
	}

	void AutonomousPeriodic() override {
		if(commandQueueIterator == commandQueue.end()) return;

		processCommand(*commandQueueIterator);
	}

	void TeleopInit() override {
		turn__DegreesCommand.init();
		tankDrive.init();
		joystickElevator.init();
//		aimToTargetCommand.init();
//		pneumaticGripperCommand.init();
	}

	void TeleopPeriodic() override {
		if(oi.getTurnButton()){
			turn__DegreesCommand.update();
		}
		else{
			turn__DegreesCommand.disable();
			turn__DegreesCommand.startNewturn();
			tankDrive.update();
		}

/*		if(!oi.getTurnButton()){
			aimToTargetCommand.disable();
			aimToTargetCommand.startNewTurn();
			arcadeDrive.update();
		}
		else{
			aimToTargetCommand.update();
		}
*/
		joystickElevator.update();
//		pneumaticGripperCommand.update();

		SmartDashboard::PutNumber("Elevator Throttle", oi.getElevatorThrottle());
//		SmartDashboard::PutBoolean("Claw Position", oi.getIntakeThrottle());
		SmartDashboard::PutBoolean("topLimit", elevator.topPressed());
		SmartDashboard::PutBoolean("bottomLimit", elevator.bottomPressed());

//		limelight.refreshNetworkTableValues();
//		limelight.printToSmartDashboard();
	}

	void TestPeriodic() override {

	}

};

START_ROBOT_CLASS(Robot)
