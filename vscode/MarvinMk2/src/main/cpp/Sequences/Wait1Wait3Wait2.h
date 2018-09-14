/*
 * Wait1Wait3Wait2.h
 *
 *  Created on: Jan 19, 2018
 *      Author: JARVIS
 */

#ifndef SRC_SEQUENCES_WAIT1WAIT3WAIT2_H_
#define SRC_SEQUENCES_WAIT1WAIT3WAIT2_H_

#include <list>

#include "SequenceBase.h"
#include <Commands/CommandBase.h>
#include <Commands/TestCommand.h>

namespace auton {
	class Wait1Wait3Wait2 : public SequenceBase {
		TestCommand testCommand1 = TestCommand{1};
		TestCommand testCommand3 = TestCommand{3};
		TestCommand testCommand2 = TestCommand{2};

		SequenceBase sequenceOne;
		SequenceBase sequenceTwo;

	public:
		Wait1Wait3Wait2()
		{
			sequenceOne.setCommandsToRun(std::list<CommandBase*>{&testCommand1});
			sequenceTwo.setCommandsToRun(std::list<CommandBase*>{
				&testCommand3,
				&testCommand2
			});

			std::list<SequenceBase*> sequences{
				&sequenceOne,
				&sequenceTwo
			};
			sequenceQueue = sequences;
		};
	};
}



#endif /* SRC_SEQUENCES_WAIT1WAIT3WAIT2_H_ */
