/*
 * PneumaticSystem.cpp
 *
 *  Created on: Jan 26, 2018
 *      Author: JARVIS
 */

#include <Systems/PneumaticSystem.h>

PneumaticSystem::PneumaticSystem() : SystemBase("PneumaticSystem"){
	compressor.SetClosedLoopControl(true);
}

PneumaticSystem::~PneumaticSystem() {
	// TODO Auto-generated destructor stub
}

