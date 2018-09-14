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


namespace auton {

class PitTestSequence: public SequenceBase {
	TestCommand test1;

	SequenceBase sequence1;

public:
	PitTestSequence()
		: test1{0.1}
    {
    	sequence1.setCommandsToRun(std::list<CommandBase*>{&test1});

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
