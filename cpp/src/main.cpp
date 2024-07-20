#include "RocketDataHub.h"
#include "RocketStage.h"
#include <iostream>

int main()
{
    // Rocket data
    double initialMass = 1000;    // kg
    double specificImpulse = 300; // s

    // Parameters to be provided by the user
    double totalFuel;
    double fuelUsageRate;
    double throttle;

    // User input for total fuel, fuel usage rate, and throttle percentage
    std::cout << "Enter total fuel (kg): ";
    std::cin >> totalFuel;
    std::cout << "Enter fuel usage rate (kg/s): ";
    std::cin >> fuelUsageRate;
    std::cout << "Enter throttle percentage (0 to 1): ";
    std::cin >> throttle;

    // Initialize data hub with rocket parameters
    RocketDataHub dataHub(initialMass, specificImpulse);

    // Initialize rocket stage with data from data hub and user inputs
    RocketStage stage(dataHub, totalFuel, fuelUsageRate);

    // Print initial rocket information
    stage.printRocketInfo();

    // Simulate burn with given throttle
    stage.simulateBurn(throttle);

    return 0;
}
