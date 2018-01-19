/*
 * SystemBase.cpp
 *
 *  Created on: Jan 19, 2018
 *      Author: JARVIS
 */
#include <cassert>
#include "SystemBase.h"

SystemBase::SystemBase(std::string name) : name{name} {
	//Makes sure system is unique
	for(auto iter = systemsList.begin(); iter != systemsList.end(); iter++){
		assert(name != (*iter)->name);
	}
	//If this passes, adds the currently initializing system to the list
	systemsList.push_back(this);
}

SystemBase::~SystemBase() {
	//If this destructor is ever called (not sure why it would be) a system should be removed from the systems list
	for(auto iter = systemsList.begin(); iter != systemsList.end(); iter++){
		if(*iter == this){
			systemsList.erase(iter);
		}
	}
}

static const std::vector<SystemBase*>& SystemBase::getSystemsList() {
	return systemsList;
}

