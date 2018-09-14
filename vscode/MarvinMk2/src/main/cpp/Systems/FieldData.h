/*
 * FieldData.h
 *
 *  Created on: Mar 16, 2018
 *      Author: JARVIS
 */

#ifndef SRC_SYSTEMS_FIELDDATA_H_
#define SRC_SYSTEMS_FIELDDATA_H_

#include <Systems/SystemBase.h>

enum class SwitchScalePositions {
	kLeft
	, kRight
	, kUnknown
};

class FieldData: public SystemBase {
	std::string gameData;

	SwitchScalePositions homeSwitchPosition = SwitchScalePositions::kUnknown;
	SwitchScalePositions awaySwitchPosition = SwitchScalePositions::kUnknown;
	SwitchScalePositions scalePosition = SwitchScalePositions::kUnknown;

	std::string stringifySwitchScalePosition(SwitchScalePositions);
public:
	FieldData();
	virtual ~FieldData();

	void readSwitchScalePositions();
	void publishFieldDataToDashboard();
	bool acquiredSwitchScalePositions();

	SwitchScalePositions getHomeSwitchPosition();
	SwitchScalePositions getAwaySwitchPosition();
	SwitchScalePositions getScalePosition();
};

#endif /* SRC_SYSTEMS_FIELDDATA_H_ */
