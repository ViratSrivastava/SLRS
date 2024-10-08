#include <iostream>
#include <thread>
#include <chrono>

class Rocket
{
public:
    Rocket() : currentAltitude(5000.0), numEngines(1), upperStageAttached(true) {}

    // Function to simulate engine startup
    void startupEngines(int num)
    {
        std::cout << "Starting up " << num << " engine(s)..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // Simulate engine startup time
        numEngines = num;
        std::cout << numEngines << " engine(s) running!" << std::endl;
    }

    // Function to simulate upper stage separation
    void separateUpperStage()
    {
        std::cout << "Separating upper stage..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Simulate separation delay
        upperStageAttached = false;
        std::cout << "Upper stage separated!" << std::endl;

        // Toggle to 3 engines after upper stage separation
        startupEngines(3);
    }

    // Function to simulate descent with engine switching
    void startDescent(double finalDescentAltitude)
    {
        while (currentAltitude > 0)
        {
            std::cout << "Current altitude: " << currentAltitude << " meters" << std::endl;

            // Separate upper stage at 3000 meters altitude
            if (currentAltitude <= 3000 && upperStageAttached)
            {
                separateUpperStage(); // Separate upper stage and toggle to 3 engines
            }

            // Switch to 1 engine at the last 1 km of descent
            if (currentAltitude <= finalDescentAltitude && numEngines == 3)
            {
                std::cout << "Switching to 1 engine for final descent..." << std::endl;
                startupEngines(1); // Switch to 1 engine for precision landing
            }

            // Simulate descent by decreasing altitude
            std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Time interval for descent
            currentAltitude -= 250;                                      // Decrease altitude (descent rate of 250 meters per step)
        }

        std::cout << "Rocket has landed." << std::endl;
    }

private:
    double currentAltitude;  // Current altitude of the rocket
    int numEngines;          // Number of active engines
    bool upperStageAttached; // Flag for upper stage attachment
};

int main()
{
    Rocket rocket;
    double finalDescentAltitude = 1000.0; // Set the altitude for switching to 1 engine (1 km)

    // Start the rocket descent, toggle engine count at stage separation and final descent
    rocket.startDescent(finalDescentAltitude);

    return 0;
}
