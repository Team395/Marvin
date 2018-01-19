/*
 * SubsystemBase.h
 *
 *  Created on: Jan 19, 2018
 *      Author: JARVIS
 */

#ifndef SRC_SYSTEMS_SUBSYSTEMBASE_H_
#define SRC_SYSTEMS_SUBSYSTEMBASE_H_
#include <string>

class SubsystemBase {
	std::string name;

public:
	SubsystemBase(std::string);
	virtual ~SubsystemBase();
};

#endif /* SRC_SYSTEMS_SUBSYSTEMBASE_H_ */
