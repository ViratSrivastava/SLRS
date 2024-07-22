#include "RocketStage.h"
#include <iostream>
#include <fstream>
#include <cmath>

RocketStage::RocketStage(const RocketDataHub& dataHub, double totalFuel, double fuelUsageRate)
    : totalFuel(totalFuel), fuelUsageRate(fuelUsageRate), initialMass(dataHub.getInitialMass()), 
      currentMass(dataHub.getInitialMass()), specificImpulse(dataHub.getSpecificImpulse()) {
    calculateBurnTime();
    calculateDeltaV();
}

void RocketStage::calculateBurnTime() {
    burnTime = totalFuel / fuelUsageRate;
}

void RocketStage::calculateDeltaV() {
    deltaV = specificImpulse * 9.81 * std::log(initialMass / (initialMass - totalFuel));
}

double RocketStage::getThrust(double throttle) const {
    return specificImpulse * 9.81 * fuelUsageRate * throttle;
}

void RocketStage::simulateBurn(double throttle) {
    std::ofstream outFile("rocket_output.csv");
    outFile << "Time,Thrust,RemainingFuel,CurrentMass\n";

    double time = 0;
    while (totalFuel > 0) {
        double thrust = getThrust(throttle);
        double fuelBurned = fuelUsageRate * throttle;

        totalFuel -= fuelBurned;
        currentMass -= fuelBurned;
        time += 1;

        if (totalFuel < 0) {
            totalFuel = 0;
        }

        outFile << time << "," << thrust << "," << totalFuel << "," << currentMass << "\n";

        std::cout << "Time: " << time << "s, Thrust: " << thrust << "N, Remaining Fuel: " << totalFuel << "kg, Current Mass: " << currentMass << "kg\n";
    }

    outFile.close();
}

void RocketStage::printRocketInfo() const {
    std::cout << "Initial Mass: " << initialMass << "kg\n";
    std::cout << "Total Fuel: " << totalFuel << "kg\n";
    std::cout << "Fuel Usage Rate: " << fuelUsageRate << "kg/s\n";
    std::cout << "Specific Impulse: " << specificImpulse << "s\n";
    std::cout << "Total Delta V: " << deltaV << "m/s\n";
    std::cout << "Burn Time: " << burnTime << "s\n";
}
