/*
 * BaseSequence.h
 *
 *  Created on: Jan 19, 2018
 *      Author: JARVIS
 */

#ifndef SRC_SEQUENCES_SEQUENCEBASE_H_
#define SRC_SEQUENCES_SEQUENCEBASE_H_

#include <list>

#include <Commands/CommandBase.h>

namespace auton {
	class SequenceBase {
	public:
		SequenceBase() {};
		virtual ~SequenceBase() {};
		virtual std::list<CommandBase*> getCommandQueue()=0;
	};
}



#endif /* SRC_SEQUENCES_SEQUENCEBASE_H_ */
