#ifndef CONVEYOR_SYSTEM_H
#define CONVEYOR_SYSTEM_H

#include <string>

/*
    Declares the ConveyorSystem class and its available operations.

    The internal machine state remains private so it can only be changed
    through the system's controlled operating and safety functions.
*/

class ConveyorSystem {
private:
    std::string conveyorStatus;
    int itemsProcessed;
    bool jamDetected;
    bool emergencyStopActive;
    bool programRunning;

    void displayMenu() const;
    int getOperatorChoice() const;
    void startConveyor();
    void stopConveyor();
    void processItem();
    void displayStatus() const;
    void activateJamSensor();
    void clearJam();
    void activateEmergencyStop();
    void resetEmergencyStop();
    void shutDown();
    void handleOperatorChoice(int choice);

public:
    ConveyorSystem();
    void run();
};

#endif