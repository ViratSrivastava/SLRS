#include <iostream>
#include <thread>
#include <chrono>

class Rocket
{
public:
    // Constructor initializes the grid fins state and adds an altitude property
    Rocket() : altitude(80000.0)
    { // Initial altitude set to 80 km
        for (int i = 0; i < 4; i++)
        {
            gridFins[i] = false; // All grid fins are retracted initially
        }
    }

    // Function to simulate altitude descent
    void updateAltitude()
    {
        // Simulating the rocket descending by reducing the altitude in each loop
        altitude -= 1000.0; // Decrease altitude by 1 km per iteration (adjust as needed)
        std::cout << "Current altitude: " << altitude << " meters" << std::endl;
    }

    // Function to deploy a single grid fin
    void deployGridFin(int finNumber)
    {
        if (finNumber >= 0 && finNumber < 4)
        {
            std::cout << "Deploying grid fin " << finNumber + 1 << "..." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Simulate time taken to deploy the grid fin
            gridFins[finNumber] = true;
            std::cout << "Grid fin " << finNumber + 1 << " deployed!" << std::endl;
        }
        else
        {
            std::cout << "Invalid grid fin number!" << std::endl;
        }
    }

    // Function to deploy all grid fins in sequence
    void deployAllGridFins()
    {
        std::cout << "Starting grid fin deployment sequence..." << std::endl;
        for (int i = 0; i < 4; i++)
        {
            deployGridFin(i);
            std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Small delay between each deployment
        }
        std::cout << "All grid fins deployed. Rocket is stabilized for descent!" << std::endl;
    }

    // Function to check whether grid fins should be deployed (based on altitude)
    void checkAndDeployGridFins()
    {
        if (altitude <= 70000.0 && altitude >= 40000.0 && !gridFinsDeployed)
        { // Deploy between 70 km and 40 km
            std::cout << "Grid fin deployment condition met at altitude " << altitude << " meters." << std::endl;
            deployAllGridFins();
            gridFinsDeployed = true;
        }
    }

private:
    bool gridFins[4];              // Grid fins state: false = retracted, true = deployed
    double altitude;               // Rocket altitude (in meters)
    bool gridFinsDeployed = false; // Ensure grid fins are deployed only once
};

int main()
{
    Rocket rocket;

    // Simulate rocket descent and check for grid fin deployment
    while (true)
    {
        rocket.updateAltitude();         // Simulate the altitude changing over time
        rocket.checkAndDeployGridFins(); // Check if it's time to deploy grid fins

        if (rocket.getAltitude() < 40000.0)
        {
            std::cout << "Rocket is below grid fin deployment range. Descent continues." << std::endl;
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Simulate time passing
    }

    return 0;
}
