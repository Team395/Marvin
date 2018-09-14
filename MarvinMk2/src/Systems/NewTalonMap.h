/*
 * NewTalonMap.h
 *
 *  Created on: Aug 21, 2018
 *      Author: JARVIS
 */

#ifndef SRC_SYSTEMS_NEWTALONMAP_H_
#define SRC_SYSTEMS_NEWTALONMAP_H_

#include <unordered_map>

#include <ctre/Phoenix.h>

class NewTalonMap {
    public:
      NewTalonMap();
      WPI_TalonSRX* getTalonByID(int talonID);

    private:
      std::unordered_map<int, WPI_TalonSRX*> talonMap;

      WPI_TalonSRX leftLeader;
      WPI_TalonSRX rightLeader;
      WPI_TalonSRX leftFollower;
      WPI_TalonSRX rightFollower;
      WPI_TalonSRX winchController;
};



#endif /* SRC_SYSTEMS_NEWTALONMAP_H_ */
