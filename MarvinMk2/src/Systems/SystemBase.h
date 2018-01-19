/*
 * SystemBase.h
 *
 *  Created on: Jan 19, 2018
 *      Author: JARVIS
 */

#ifndef SRC_SYSTEMS_SYSTEMBASE_H_
#define SRC_SYSTEMS_SYSTEMBASE_H_
#include <string>
#include <vector>

class SystemBase {
	static std::vector<SystemBase*> systemsList{};
	std::string name;

public:
	SystemBase(std::string);
	virtual ~SystemBase();

	static const std::vector<SystemBase*>& getSystemsList();
};

#endif /* SRC_SYSTEMS_SYSTEMBASE_H_ */
