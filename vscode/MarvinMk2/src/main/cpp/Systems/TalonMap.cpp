#include "TalonMap.h"
#include "..\RobotMap.h"

TalonMap::TalonMap()
    : leftLeader(DrivebaseMap::kLeftMaster),
      rightLeader(DrivebaseMap::kRightMaster),
      leftFollower(DrivebaseMap::kLeftSlave),
      rightFollower(DrivebaseMap::kRightSlave),
      winchController(ClimberMap::kWinch)
{
    talonMap.insert(std::make_pair<leftLeader.GetDeviceID(), &leftLeader);
    talonMap.insert(std::make_pair<rightLeader.GetDeviceID(), &rightLeader);
    talonMap.insert(std::make_pair<leftFollower.GetDeviceID(), &leftFollower);
    talonMap.insert(std::make_pair<rightFollower.GetDeviceID(), &rightFollower);
    talonMap.insert(std::make_pair<winchController.GetDeviceID(), &winchController);
}

WPI_TalonSRX*
TalonMap::getTalonByID(int talonID)
{
    WPI_TalonSRX* talon = 0;
    std::unordered_map<int, WPI_TalonSRX*>::iterator it = talonMap.find(talonID);
    if (it != talonMap.end()) {
        talon = it.second;
    }

    return talon;
}
