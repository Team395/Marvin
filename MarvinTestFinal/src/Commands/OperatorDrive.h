#ifndef OperatorDrive_H
#define OperatorDrive_H

#include "../CommandBase.h"

class OperatorDrive : public CommandBase {
public:
	OperatorDrive();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // OperatorDrive_H
