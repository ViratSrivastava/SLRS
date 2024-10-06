#include <iostream>
#include <thread>
#include <chrono>

class Rocket {
public:
    // Constructor initializes the legs state
    Rocket() {
        for (int i = 0; i < 4; i++) {
            legs[i] = false;  // All legs are retracted initially
        }
    }

    // Function to extend a single leg
    void extendLeg(int legNumber) {
        if (legNumber >= 0 && legNumber < 4) {
            std::cout << "Extending leg " << legNumber + 1 << "..." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));  // Simulate time taken to extend the leg
            legs[legNumber] = true;
            std::cout << "Leg " << legNumber + 1 << " extended!" << std::endl;
        } else {
            std::cout << "Invalid leg number!" << std::endl;
        }
    }

    // Function to extend all legs in sequence
    void extendAllLegs() {
        std::cout << "Starting landing legs extension sequence..." << std::endl;
        for (int i = 0; i < 4; i++) {
            extendLeg(i);
        }
        std::cout << "All legs extended. Ready for landing!" << std::endl;
    }

private:
    bool legs[4];  // Legs state: false = retracted, true = extended
};

int main() {
    Rocket rocket;

    // Execute the landing legs extension sequence
    rocket.extendAllLegs();

    return 0;
}
