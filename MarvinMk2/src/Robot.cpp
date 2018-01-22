#include <iostream>
#include <memory>
#include <string>
#include <list>

#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SmartDashboard.h>

#include "Systems/SystemBase.h"
#include "Systems/Elevator.h"
#include "Systems/Drivebase.h"
#include "Systems/Gyroscope.h"

#include "Commands/CommandBase.h"
#include "Commands/JoystickElevatorCommand.h"
#include "Commands/ArcadeDriveCommand.h"
#include "Commands/Turn__DegreesCommand.h"
#include "Commands/TestCommand.h"

#include "Sequences/AutonomousSequences.h"

#include "OI.h"

class Robot: public frc::IterativeRobot {
	frc::LiveWindow& m_lw = *LiveWindow::GetInstance();
	Elevator elevator{};
	Drivebase drivebase{};
	Gyroscope gyroscope{};

	OI oi{};

	ArcadeDriveCommand arcadeDrive{&drivebase, &oi};
	JoystickElevatorCommand joystickElevator{&elevator, &oi};
	Turn__DegreesCommand turn__DegreesCommand{&drivebase, &gyroscope, &oi};

	std::list<CommandBase*> commandQueue;
	std::list<CommandBase*>::iterator commandQueueIterator;

	void processCommand(CommandBase* command){
		if(CommandState::kNotStarted) command->init();
		command->update();
		if(CommandState::kFinished){
			commandQueueIterator++;
		}
	}

public:

	void RobotInit() {

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

	}

	void TeleopPeriodic() override {

	}

	void TestPeriodic() override {

	}

};

START_ROBOT_CLASS(Robot)
