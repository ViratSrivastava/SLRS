#ifndef ROCKETSTAGE_H
#define ROCKETSTAGE_H

#include "RocketDataHub.h"

class RocketStage
{
private:
    double totalFuel;
    double fuelUsageRate;
    double initialMass;
    double currentMass;
    double specificImpulse;
    double deltaV;
    double burnTime;

public:
    RocketStage(const RocketDataHub &dataHub, double totalFuel, double fuelUsageRate);

    void calculateBurnTime();
    void calculateDeltaV();
    double getThrust(double throttle) const;
    void simulateBurn(double throttle);
    void printRocketInfo() const;
};

#endif // ROCKETSTAGE_H
