#include <RobotMap.h>
#include <Systems/NewTalonMap.h>

NewTalonMap::NewTalonMap()
    : leftLeader(DrivebaseMap::kLeftMaster),
      rightLeader(DrivebaseMap::kRightMaster),
      leftFollower(DrivebaseMap::kLeftSlave),
      rightFollower(DrivebaseMap::kRightSlave),
      winchController(ElevatorMap::kWinchOne)
{
    talonMap.insert(std::make_pair<int, WPI_TalonSRX*>(leftLeader.GetDeviceID(), &leftLeader));
    talonMap.insert(std::make_pair<int, WPI_TalonSRX*>(rightLeader.GetDeviceID(), &rightLeader));
    talonMap.insert(std::make_pair<int, WPI_TalonSRX*>(leftFollower.GetDeviceID(), &leftFollower));
    talonMap.insert(std::make_pair<int, WPI_TalonSRX*>(rightFollower.GetDeviceID(), &rightFollower));
    talonMap.insert(std::make_pair<int, WPI_TalonSRX*>(winchController.GetDeviceID(), &winchController));
}

WPI_TalonSRX*
NewTalonMap::getTalonByID(int talonID)
{
    WPI_TalonSRX* talon = 0;
    std::unordered_map<int, WPI_TalonSRX*>::iterator it = talonMap.find(talonID);
    if (it != talonMap.end()) {
        talon = it->second;
    }

    return talon;
}
