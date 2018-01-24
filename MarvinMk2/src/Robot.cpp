#include <iostream>
#include <memory>
#include <string>
#include <list>

#include <TimedRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SmartDashboard.h>

#include <Systems/SystemBase.h>
#include <Systems/Elevator.h>
#include <Systems/Drivebase.h>
#include <Systems/Gyroscope.h>
#include <Systems/Limelight.h>

#include <Commands/CommandBase.h>
#include <Commands/JoystickElevatorCommand.h>
#include <Commands/ArcadeDriveCommand.h>
#include <Commands/Turn__DegreesCommand.h>
#include <Commands/TestCommand.h>
#include <Commands/AimToTargetCommand.h>

#include <Sequences/AutonomousSequences.h>
#include <Libraries/LimelightMap.h>
#include <OI.h>

class Robot: public frc::TimedRobot {
	frc::LiveWindow& m_lw = *frc::LiveWindow::GetInstance();
	Elevator elevator{};
	Drivebase drivebase{};
	Gyroscope gyroscope{};
	Limelight limelight{};

	OI oi{};

	ArcadeDriveCommand arcadeDrive{&drivebase, &oi};
	JoystickElevatorCommand joystickElevator{&elevator, &oi};
	Turn__DegreesCommand turn__DegreesCommand{&drivebase, &gyroscope, &oi};
	AimToTargetCommand aimToTargetCommand{&drivebase, &limelight, limelightMap::PipeLine::kPipeline0};

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
		limelight.setLedMode(limelightMap::LedMode::kOn);
	}

	void AutonomousInit() override {
		commandQueue = auton::Wait1Wait3Wait2().getCommandQueue();
		commandQueueIterator = commandQueue.begin();
	}

	void AutonomousPeriodic() override {
		if(commandQueueIterator == commandQueue.end()) return;

		processCommand(*commandQueueIterator);
	}

	std::list<CommandBase*> currentlyExecuting{};

	void TeleopInit() override {

	}

	void TeleopPeriodic() override {
		/*if(!oi.GetTurnButton()){
			turn__DegreesCommand.disable();
			turn__DegreesCommand.startNewturn();
			arcadeDrive.update();
		}
		else{
			turn__DegreesCommand.update();
		}*/

		if(!oi.GetTurnButton()){
			aimToTargetCommand.disable();
			aimToTargetCommand.startNewTurn();
			arcadeDrive.update();
		}
		else{
			aimToTargetCommand.update();
		}

		joystickElevator.update();
//		SmartDashboard::PutData("IMU", gyroscope.getIMU());
		SmartDashboard::PutBoolean("topLimit", elevator.topPressed());
		SmartDashboard::PutBoolean("bottomLimit", elevator.bottomPressed());

		limelight.refreshNetworkTableValues();
		limelight.printToSmartDashboard();
	}

	void TestPeriodic() override {

	}

};

START_ROBOT_CLASS(Robot)
