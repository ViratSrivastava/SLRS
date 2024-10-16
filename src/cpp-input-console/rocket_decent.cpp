#include <iostream>
#include <thread>
#include <chrono>
#include <pqxx/pqxx> // PostgreSQL C++ library

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

    // Function to log data into PostgreSQL database
    void logData(pqxx::work &W)
    {
        std::string query = "INSERT INTO descent_data (altitude, engine_count, stage_separated) VALUES (" +
                            std::to_string(currentAltitude) + ", " +
                            std::to_string(numEngines) + ", " +
                            (upperStageAttached ? "false" : "true") + ");";

        W.exec(query);
    }

    // Function to simulate descent with engine switching
    void startDescent(double finalDescentAltitude, pqxx::connection &C)
    {
        pqxx::work W(C); // Create a PostgreSQL transaction

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

            // Log current data to the database
            logData(W);

            // Simulate descent by decreasing altitude
            std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Time interval for descent
            currentAltitude -= 250;                                      // Decrease altitude (descent rate of 250 meters per step)
        }

        // Commit the transaction to save the logged data
        W.commit();

        std::cout << "Rocket has landed." << std::endl;
    }

private:
    double currentAltitude;  // Current altitude of the rocket
    int numEngines;          // Number of active engines
    bool upperStageAttached; // Flag for upper stage attachment
};

int main()
{
    // Connect to the PostgreSQL database
    std::string connStr = "dbname=rocket_data user=your_user password=your_password hostaddr=127.0.0.1 port=5432";
    pqxx::connection C(connStr);

    if (C.is_open())
    {
        std::cout << "Connected to the database successfully!" << std::endl;
    }
    else
    {
        std::cerr << "Could not connect to the database." << std::endl;
        return 1;
    }

    Rocket rocket;
    double finalDescentAltitude = 1000.0; // Set the altitude for switching to 1 engine (1 km)

    // Start the rocket descent and log data to PostgreSQL
    rocket.startDescent(finalDescentAltitude, C);

    return 0;
}
