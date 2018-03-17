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
		std::list<CommandBase*> commandQueue;
		std::list<CommandBase*>::iterator commandQueueIterator;

		SequenceBase() {};

		virtual ~SequenceBase() {};

		std::list<CommandBase*> getCommandQueue() {
			return commandQueue;
		};

		void initSequence(){
			commandQueueIterator = commandQueue.begin();
		}

		void execute(){
			if(commandQueueIterator == commandQueue.end()) return;
			processCommand(*commandQueueIterator);
		}

		void processCommand(CommandBase* command){
			std::cout << "Entered processCommand().";
			if(command->getCommandState() == CommandState::kNotStarted) {
				command->init();
			}

			command->update();

			if(command->getCommandState() == CommandState::kFinished) {
				commandQueueIterator++;
			}
			std::cout << "Exited processCommand().";
		}
	};
}



#endif /* SRC_SEQUENCES_SEQUENCEBASE_H_ */
