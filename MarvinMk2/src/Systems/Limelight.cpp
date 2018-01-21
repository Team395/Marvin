/*
 * Limelight.cpp
 *
 *  Created on: Jan 20, 2018
 *      Author: JARVIS
 */

#include <string>
#include <memory>
#include <NetworkTables/NetworkTable.h>
#include <NetworkTables/NetworkTableInstance.h>
#include <SmartDashboard/SmartDashboard.h>

#include "Limelight.h"

Limelight::Limelight() : SystemBase("limelight") {
	networkTable = nt::NetworkTableInstance::GetDefault()
		.GetTable(kNetworkTableName);
}

void Limelight::refreshNetworkTableValues() {
	hasValidTargets = networkTable->GetNumber("tv", 0);
	horizontalOffsetToTargetDegrees = networkTable->GetNumber("tx", 0);
	verticalOffsetToTargetDegrees = networkTable->GetNumber("ty", 0);
	targetAreaPercent = networkTable->GetNumber("ta", 0);
	skewTargetDegrees = networkTable->GetNumber("ts", 0);
	pipelineLatencyMilliseconds = networkTable->GetNumber("tl", 0);

	kP = preferences->GetDouble("limelightKp", -.03);
	kI = preferences->GetDouble("limelightKi", 0);
	kD = preferences->GetDouble("limelightKd", 0);
	kMinRate = preferences->GetDouble("limelightKminRate", 2.5);
}

void Limelight::setLedMode(limelightMap::LedMode ledMode){
	networkTable->PutNumber("ledMode", ledMode);
}

void Limelight::setCamMode(limelightMap::CamMode camMode){
	networkTable->PutNumber("camMode", camMode);
}

void Limelight::setPipeline(limelightMap::PipeLine pipeline){
	networkTable->PutNumber("pipeline", pipeline);
}

bool Limelight::getHasValidTargets(){
	return hasValidTargets;
}

double Limelight::getHorizontalOffset(){
	return horizontalOffsetToTargetDegrees;
}

double Limelight::getVerticalOffset(){
	return verticalOffsetToTargetDegrees;
}

double Limelight::getTargetArea(){
	return targetAreaPercent;
}

double Limelight::getSkew(){
	return skewTargetDegrees;
}

double Limelight::getLatency(){
	return pipelineLatencyMilliseconds + kImageCaptureLatencyMilliseconds;
}

void Limelight::printToSmartDashboard(){
	SmartDashboard::PutBoolean("Limelight::HasValidTargets", getHasValidTargets());
	SmartDashboard::PutNumber("Limelight::HorizontalOffset", getHorizontalOffset());
	SmartDashboard::PutNumber("Limelight::VerticalOffset", getVerticalOffset());
	SmartDashboard::PutNumber("Limelight::TargetArea", getTargetArea());
	SmartDashboard::PutNumber("Limelight::Skew", getSkew());
	SmartDashboard::PutNumber("Limelight::Latency", getLatency());
}

frc::PIDSourceType Limelight::GetPIDSourceType() {
	return frc::PIDSourceType::kDisplacement;
}

double Limelight::PIDGet() {
	refreshNetworkTableValues();
	return -1 * getHorizontalOffset();
}
