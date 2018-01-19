/*
 * SystemBase.h
 *
 *  Created on: Jan 19, 2018
 *      Author: JARVIS
 */

#ifndef SRC_SYSTEMS_SYSTEMBASE_H_
#define SRC_SYSTEMS_SYSTEMBASE_H_
#include <string>

class SystemBase {
	std::string name;

public:
	SystemBase(std::string);
	virtual ~SystemBase();
};

#endif /* SRC_SYSTEMS_SYSTEMBASE_H_ */
