/*
 * PitTestSequence.h
 *
 *  Created on: Mar 23, 2018
 *      Author: JARVIS
 */

#ifndef SRC_SEQUENCES_PITTESTSEQUENCE_H_
#define SRC_SEQUENCES_PITTESTSEQUENCE_H_

#include <Sequences/SequenceBase.h>

#include <Commands/TestCommand.h>
#include <Commands/Turn__DegreesCommand.h>
#include <Systems/DrivebaseGyroSensor.h>
#include <Systems/Drivebase.h>

namespace auton {

class PitTestSequence: public SequenceBase {
	TestCommand test1;
	Turn__DegreesCommand turnDegreesCommand;
	SequenceBase sequence1;

public:
	PitTestSequence(Drivebase* drivebase, DrivebaseGyroSensor* gyro)
		: test1{0.1},
		  turnDegreesCommand{90, drivebase, gyro, 0}
    {
    	sequence1.setCommandsToRun(std::list<CommandBase*>{&turnDegreesCommand});

		std::list<SequenceBase*> sequences{
			&sequence1
		};
		sequenceQueue = sequences;

	}

	virtual ~PitTestSequence()
	{
	}
};

} /* namespace auton */

#endif /* SRC_SEQUENCES_PITTESTSEQUENCE_H_ */
