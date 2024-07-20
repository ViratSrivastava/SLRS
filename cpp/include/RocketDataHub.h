#ifndef ROCKETDATAHUB_H
#define ROCKETDATAHUB_H

class RocketDataHub
{
private:
    double initialMass;
    double specificImpulse;

public:
    RocketDataHub(double initialMass, double specificImpulse)
        : initialMass(initialMass), specificImpulse(specificImpulse) {}

    double getInitialMass() const { return initialMass; }
    double getSpecificImpulse() const { return specificImpulse; }
};

#endif // ROCKETDATAHUB_H
