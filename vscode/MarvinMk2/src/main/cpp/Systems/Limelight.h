/*
 * Limelight.h
 *
 *  Created on: Jan 20, 2018
 *      Author: JARVIS
 */

#ifndef SRC_SYSTEMS_LIMELIGHT_H_
#define SRC_SYSTEMS_LIMELIGHT_H_

#include <string>

#include <Systems/SystemBase.h>
#include <Libraries/LimelightMap.h>

#include <NetworkTables/NetworkTableInstance.h>
#include <PIDSource.h>

#include <Preferences.h>

class Limelight : SystemBase, public frc::PIDSource {
	double hasValidTargets = false;
	double horizontalOffsetToTargetDegrees = 0;
	double verticalOffsetToTargetDegrees = 0;
	double targetAreaPercent = 0;
	double skewTargetDegrees = 0;
	double pipelineLatencyMilliseconds = 0;

	const double kImageCaptureLatencyMilliseconds = 11;
	const std::string kNetworkTableName = "limelight";

	std::shared_ptr<NetworkTable> networkTable;

	Preferences* preferences = Preferences::GetInstance();
public:
	//PID gains for turn
	double kP{.03};
	double kI{0.00};
	double kD{0};
	double kMinRate{0.2};

	Limelight();
	void refreshNetworkTableValues();
	void setLedMode(limelightMap::LedMode);
	void setCamMode(limelightMap::CamMode);
	void setPipeline(limelightMap::PipeLine);

	bool getHasValidTargets();
	double getHorizontalOffset();
	double getVerticalOffset();
	double getTargetArea();
	double getSkew();
	double getLatency();

	void printToSmartDashboard();

	frc::PIDSourceType GetPIDSourceType();
	double PIDGet();
};

#endif /* SRC_SYSTEMS_LIMELIGHT_H_ */
