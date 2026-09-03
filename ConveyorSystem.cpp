#include "ConveyorSystem.h"

#include <iostream>
#include <limits>

// Establish a safe initial machine state.
ConveyorSystem::ConveyorSystem()
    : conveyorStatus("STOPPED"),
      itemsProcessed(0),
      jamDetected(false),
      emergencyStopActive(false),
      programRunning(true) {
}

void ConveyorSystem::displayMenu() const {
    std::cout << "\n===== CONVEYOR BELT CONTROL SYSTEM =====\n";
    std::cout << "1. Start conveyor\n";
    std::cout << "2. Stop conveyor\n";
    std::cout << "3. Process item\n";
    std::cout << "4. View system status\n";
    std::cout << "5. Simulate jam sensor\n";
    std::cout << "6. Clear jam\n";
    std::cout << "7. Activate emergency stop\n";
    std::cout << "8. Reset emergency stop\n";
    std::cout << "9. Exit\n";
    std::cout << "Select an option: ";
}

int ConveyorSystem::getOperatorChoice() const {
    std::string input;

    // Exit normally if the input stream closes.
    if (!std::getline(std::cin, input)) {
        return 9;
    }

    // Accept exactly one menu digit; reject mixed or extra characters.
    if (input.length() == 1 && input[0] >= '1' && input[0] <= '9') {
        return input[0] - '0';
    }

    return -1;
}
 

void ConveyorSystem::startConveyor() {
    if (emergencyStopActive) {
        std::cout
            << "START BLOCKED: Reset the emergency stop first.\n";
    } else if (jamDetected) {
        std::cout
            << "START BLOCKED: Clear the conveyor jam first.\n";
    } else if (conveyorStatus == "RUNNING") {
        std::cout << "The conveyor is already running.\n";
    } else {
        conveyorStatus = "RUNNING";
        std::cout << "Conveyor started successfully.\n";
    }
}

void ConveyorSystem::stopConveyor() {
    if (conveyorStatus == "STOPPED") {
        std::cout << "The conveyor is already stopped.\n";
    } else {
        conveyorStatus = "STOPPED";
        std::cout << "Conveyor stopped successfully.\n";
    }
}

void ConveyorSystem::processItem() {
    if (emergencyStopActive) {
        std::cout
            << "PROCESS BLOCKED: Emergency stop is active.\n";
    } else if (jamDetected) {
        std::cout
            << "PROCESS BLOCKED: Conveyor jam detected.\n";
    } else if (conveyorStatus == "RUNNING") {
        itemsProcessed++;

        std::cout << "Item detected and processed.\n";
        std::cout << "Total items processed: "
                  << itemsProcessed << "\n";
    } else {
        std::cout
            << "Cannot process item: conveyor is stopped.\n";
    }
}

void ConveyorSystem::displayStatus() const {
    std::cout << "\n----- SYSTEM STATUS -----\n";
    std::cout << "Conveyor: " << conveyorStatus << "\n";
    std::cout << "Jam sensor: "
              << (jamDetected ? "JAM DETECTED" : "CLEAR")
              << "\n";
    std::cout << "Emergency stop: "
              << (emergencyStopActive ? "ACTIVE" : "READY")
              << "\n";
    std::cout << "Items processed: " << itemsProcessed << "\n";
}

void ConveyorSystem::activateJamSensor() {
    jamDetected = true;
    conveyorStatus = "STOPPED";

    std::cout
        << "JAM DETECTED: Conveyor stopped automatically.\n";
}

void ConveyorSystem::clearJam() {
    if (!jamDetected) {
        std::cout << "No conveyor jam is currently detected.\n";
    } else {
        jamDetected = false;
        std::cout << "Jam cleared. Conveyor remains stopped.\n";
    }
}

void ConveyorSystem::activateEmergencyStop() {
    emergencyStopActive = true;
    conveyorStatus = "STOPPED";

    std::cout
        << "EMERGENCY STOP ACTIVATED: Conveyor stopped.\n";
}

void ConveyorSystem::resetEmergencyStop() {
    if (!emergencyStopActive) {
        std::cout << "Emergency stop is already reset.\n";
    } else {
        emergencyStopActive = false;

        std::cout
            << "Emergency stop reset. Conveyor remains stopped.\n";
    }
}

void ConveyorSystem::shutDown() {
    conveyorStatus = "STOPPED";
    programRunning = false;

    std::cout
        << "Conveyor stopped. System shutting down safely.\n";
}

void ConveyorSystem::handleOperatorChoice(int choice) {
    switch (choice) {
        case 1:
            startConveyor();
            break;

        case 2:
            stopConveyor();
            break;

        case 3:
            processItem();
            break;

        case 4:
            displayStatus();
            break;

        case 5:
            activateJamSensor();
            break;

        case 6:
            clearJam();
            break;

        case 7:
            activateEmergencyStop();
            break;

        case 8:
            resetEmergencyStop();
            break;

        case 9:
            shutDown();
            break;

        default:
            std::cout
                << "Invalid option. Enter a number from 1 through 9.\n";
    }
}

void ConveyorSystem::run() {
    while (programRunning) {
        displayMenu();
        int choice = getOperatorChoice();
        handleOperatorChoice(choice);
    }
}