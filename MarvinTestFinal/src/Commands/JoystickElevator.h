#ifndef JoystickElevator_H
#define JoystickElevator_H

#include "../CommandBase.h"

class JoystickElevator : public CommandBase {
public:
	JoystickElevator();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // JoystickElevator_H
