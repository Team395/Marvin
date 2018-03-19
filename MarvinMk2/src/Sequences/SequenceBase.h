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
		std::list<SequenceBase*> sequenceQueue;
		std::list<SequenceBase*>::iterator sequenceQueueIterator;
		int numberOfCommands = 0;
		int numberOfFinishedCommands = 0;

		std::list<CommandBase*> commandsToRun;

		CommandState sequenceState{CommandState::kNotStarted};

		SequenceBase() {};

		virtual ~SequenceBase() {};

		void setCommandsToRun(std::list<CommandBase*> commands) {
			commandsToRun = commands;
		}

		std::list<SequenceBase*> getCommandQueue() {
			return sequenceQueue;
		};

		void initSequence(){
			numberOfCommands = sequenceQueue.size();
			sequenceQueueIterator = sequenceQueue.begin();

			sequenceState = CommandState::kInitialized;
		}

		void execute(){
			if(sequenceQueueIterator == sequenceQueue.end()) return;
			processSequence(*sequenceQueueIterator);
		}

		void processSequence(SequenceBase* sequence) {
			executeInParallel(sequence);
			if(sequence->sequenceState == CommandState::kFinished) {
				sequenceQueueIterator++;
			}
		}

		//return true if finished
		void executeInParallel(SequenceBase* sequence){
			std::list<CommandBase*>::iterator iterator = sequence->commandsToRun.begin();

			while(iterator != sequence->commandsToRun.end()) {
				bool finished = processCommand(*(iterator++));

				if(finished) {
					sequence->numberOfFinishedCommands++;
					if(sequence->numberOfCommands == sequence->numberOfFinishedCommands){
						sequence->sequenceState = CommandState::kFinished;
					}
				}
			}
		}

		//return true if command finished
		bool processCommand(CommandBase* command){
			if(command->getCommandState() == CommandState::kNotStarted) {
				command->init();
			}

			command->update();

			if(command->getCommandState() == CommandState::kFinished) {
				return true;
			}

			return false;
		}
	};
}



#endif /* SRC_SEQUENCES_SEQUENCEBASE_H_ */
