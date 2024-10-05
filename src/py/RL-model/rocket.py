import numpy as np
import time

class Rocket:
    def __init__(self, rocket_id):
        self.rocket_id = rocket_id
        self.state = np.array([0, 0, 0, 0, 0, 0])  # x, y, z, vx, vy, vz
        self.gravity = -9.81
        self.time_step = 0.1
        self.fuel = 100  # Example fuel parameter

    def step(self, action):
        thrust_x, thrust_y, thrust_z = action
        x, y, z, vx, vy, vz = self.state

        # Update velocity based on thrust and gravity
        new_vx = vx + thrust_x * self.time_step
        new_vy = vy + thrust_y * self.time_step
        new_vz = vz + (thrust_z + self.gravity) * self.time_step

        # Update position based on velocity
        new_x = x + new_vx * self.time_step
        new_y = y + new_vy * self.time_step
        new_z = z + new_vz * self.time_step

        # Update fuel usage (optional)
        self.fuel -= np.sqrt(thrust_x**2 + thrust_y**2 + thrust_z**2)

        # Update state
        self.state = np.array([new_x, new_y, new_z, new_vx, new_vy, new_vz])

        # Check if rocket has landed
        done = new_z <= 0
        return self.state, done

    def simulate_landing(self):
        print(f"Rocket {self.rocket_id} initiating launch...")
        for step in range(100):  # Number of steps to simulate
            action = np.random.uniform(-1, 1, 3)  # Random thrust for example
            state, done = self.step(action)
            print(f"Rocket {self.rocket_id} State: {state}")
            if done:
                print(f"Rocket {self.rocket_id} has landed.")
                break
            time.sleep(0.1)  # Delay to simulate real-time operation

        print(f"Rocket {self.rocket_id} simulation complete.")
