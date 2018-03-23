/*
 * BaseSequence.h
 *
 *  Created on: Jan 19, 2018
 *      Author: JARVIS
 */

#ifndef SRC_SEQUENCES_SEQUENCEBASE_H_
#define SRC_SEQUENCES_SEQUENCEBASE_H_

#include <list>
#include <exception>
#include <iostream>
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
			numberOfCommands = commandsToRun.size();
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
			if(sequenceQueueIterator == sequenceQueue.end()) {
				sequenceState = CommandState::kFinished;
				return;
			}
			processSequence(*sequenceQueueIterator);
		}

		void processSequence(SequenceBase* sequence) {
			executeInParallel(sequence);
			if(sequence->sequenceState == CommandState::kFinished) {
				numberOfFinishedCommands++;
				sequenceQueueIterator++;
			}
		}

		//return true if finished
		void executeInParallel(SequenceBase* sequence){
#if 1
//			for (auto iterator : sequence->commandsToRun) {
			for (auto& iterator : sequence->commandsToRun) {
				if (iterator->getCommandState() == CommandState::kFinished) {
					continue;
				}

				bool finished = processCommand(iterator);
				if (finished) {
					sequence->numberOfFinishedCommands++;

					if(sequence->numberOfCommands == sequence->numberOfFinishedCommands){
						sequence->sequenceState = CommandState::kFinished;
					}
				}
			}
#else
			std::list<CommandBase*>::iterator iterator = sequence->commandsToRun.begin();

			while(iterator != sequence->commandsToRun.end()) {
//				std::cout << (*iterator)->getName() << std::endl;
//				sequence->sequenceState = CommandState::kFinished;
//				iterator++;
				while((*iterator)->getCommandState() == CommandState::kFinished){
					iterator++;
					if(iterator == sequence->commandsToRun.end()) return;
				}

				bool finished = processCommand(*(iterator++));

				if(finished) {
					sequence->numberOfFinishedCommands++;

					if(sequence->numberOfCommands == sequence->numberOfFinishedCommands){
						sequence->sequenceState = CommandState::kFinished;
					}
				}
			}
#endif
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

		void disable() {
#if 1
			for (auto& sequenceIterator : sequenceQueue) {
				for (auto& iterator : sequenceIterator->commandsToRun) {
					iterator->disable();
				}
			}
#else
			auto sequenceIterator = sequenceQueue.begin();

			while(sequenceIterator != sequenceQueue.end()) {
				for(auto i : (*sequenceIterator)->commandsToRun){
					i->disable();
				}

				sequenceIterator++;
				//WHY WAS THIS NOT BREAKING OUT OF THE LOOP
//				auto iterator = (*sequenceIterator)->commandsToRun.begin();
//				while(iterator != (*sequenceIterator)->commandsToRun.end()) {
////					try {
////					*(*iterator);//->disable();
////					} catch(std::exception& e) {
////						std::cout << e.what() << std::endl;
////					}
//					std::cout<< "disabling command\n";
//
//					iterator++;
//				}
			}
#endif
		}
	};
}



#endif /* SRC_SEQUENCES_SEQUENCEBASE_H_ */
