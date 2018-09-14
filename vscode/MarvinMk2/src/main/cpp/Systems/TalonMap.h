#include <unordered_map>

#include <WPI_TalonSRX.h>

class TalonMap {
    public:
      TalonMap();
      WPI_TalonSRX* getTalonByID(int talonID);

    private:
      std::unordered_map<int, WPI_TalonSRX*> talonMap;

      WPI_TalonSRX leftLeader;
      WPI_TalonSRX rightLeader;
      WPI_TalonSRX leftFollower;
      WPI_TalonSRX rightFollower;
      WPI_TalonSRX winchController;
};

