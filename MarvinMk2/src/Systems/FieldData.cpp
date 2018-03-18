/*
 * FieldData.cpp
 *
 *  Created on: Mar 16, 2018
 *      Author: JARVIS
 */

#include <Systems/FieldData.h>
#include <DriverStation.h>
#include <SmartDashboard/SmartDashboard.h>

FieldData::FieldData() : SystemBase("FieldData") {
	// TODO Auto-generated constructor stub

}

FieldData::~FieldData() {
	// TODO Auto-generated destructor stub
}

void FieldData::readSwitchScalePositions() {
	//GameSpecificMessage returns: "LLL", "LRL", "RLL", "RLR" ...
	gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();

	if(gameData.length() == 0) return;

	switch(gameData[0]){
		case 'L':
			homeSwitchPosition = SwitchScalePositions::kLeft;
			break;
		case 'R':
			homeSwitchPosition = SwitchScalePositions::kRight;
			break;
	}

	switch(gameData[1]){
	case 'L':
		scalePosition = SwitchScalePositions::kLeft;
		break;
	case 'R':
		scalePosition = SwitchScalePositions::kRight;
		break;
	}

	switch(gameData[2]){
		case 'L':
			awaySwitchPosition = SwitchScalePositions::kLeft;
			break;
		case 'R':
			awaySwitchPosition = SwitchScalePositions::kRight;
			break;
	}
}

void FieldData::publishFieldDataToDashboard() {
	frc::SmartDashboard::PutString("HomeSwitchPosition", stringifySwitchScalePosition(homeSwitchPosition));
	frc::SmartDashboard::PutString("ScalePosition", stringifySwitchScalePosition(scalePosition));
	frc::SmartDashboard::PutString("AwaySwitchPosition", stringifySwitchScalePosition(awaySwitchPosition));
}

bool FieldData::acquiredSwitchScalePositions() {
	return (homeSwitchPosition != SwitchScalePositions::kUnknown
			&& awaySwitchPosition != SwitchScalePositions::kUnknown
			&& scalePosition != SwitchScalePositions::kUnknown);
}

SwitchScalePositions FieldData::getHomeSwitchPosition() {
	return homeSwitchPosition;
}

SwitchScalePositions FieldData::getAwaySwitchPosition() {
	return awaySwitchPosition;
}

SwitchScalePositions FieldData::getScalePosition() {
	return scalePosition;
}

////////// PRIVATE

std::string FieldData::stringifySwitchScalePosition(SwitchScalePositions position) {
	switch(position) {
		case SwitchScalePositions::kLeft:
			return "LEFT";
			break;
		case SwitchScalePositions::kRight:
			return "RIGHT";
			break;
		case SwitchScalePositions::kUnknown:
			return "UNKNOWN";
			break;
		default:
			return "";
	}
}
