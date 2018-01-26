/*
 * PneumaticSystem.h
 *
 *  Created on: Jan 26, 2018
 *      Author: JARVIS
 */

#ifndef SRC_SYSTEMS_PNEUMATICSYSTEM_H_
#define SRC_SYSTEMS_PNEUMATICSYSTEM_H_

#include <Systems/SystemBase.h>
#include <Compressor.h>

  class PneumaticSystem: public SystemBase {

frc::Compressor compressor{};
public:
	PneumaticSystem();
	virtual ~PneumaticSystem();
};

#endif /* SRC_SYSTEMS_PNEUMATICSYSTEM_H_ */
