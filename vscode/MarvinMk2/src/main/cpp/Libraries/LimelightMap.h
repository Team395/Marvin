/*
 * LimelightMap.h
 *
 *  Created on: Jan 20, 2018
 *      Author: JARVIS
 */

#ifndef SRC_LIBRARIES_LIMELIGHTMAP_H_
#define SRC_LIBRARIES_LIMELIGHTMAP_H_

namespace limelightMap {
	enum LedMode {
		kOn = 0
		, kOff
		, kBlink
	};

	enum CamMode {
		kVisionProcessor = 0
		, kDriverCamera = 1
	};

	enum PipeLine {
		kPipeline0 = 0
		, kPipeline1
		, kPipeline2
		, kPipeline3
		, kPipeline4
		, kPipeline5
		, kPipeline6
		, kPipeline7
		, kPipeline8
		, kPipeline9
	};
};



#endif /* SRC_LIBRARIES_LIMELIGHTMAP_H_ */
