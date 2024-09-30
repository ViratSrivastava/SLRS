import gym
from gym import spaces
import numpy as np

class RocketLandingEnv(gym.Env):
    def __init__(self):
        super(RocketLandingEnv, self).__init__()
        
        # Define the action space (thrust controls: x, y, z forces)
        self.action_space = spaces.Box(low=-1, high=1, shape=(3,), dtype=np.float32)
        
        # Define the observation space (rocket's position, velocity, orientation)
        self.observation_space = spaces.Box(low=-np.inf, high=np.inf, shape=(6,), dtype=np.float32)
        
        # Initial state
        self.state = np.zeros(6)  # [x, y, z, vx, vy, vz]
        
        # Rocket parameters
        self.gravity = -9.81
        self.time_step = 0.1

    def reset(self):
        # Reset state to initial position (above the landing pad)
        self.state = np.array([0.0, 0.0, 100.0, 0.0, 0.0, 0.0])  # High altitude
        return self.state

    def step(self, action):
        # Extract action values (thrust in x, y, z directions)
        thrust_x, thrust_y, thrust_z = action
        
        # Unpack current state: position (x, y, z) and velocity (vx, vy, vz)
        x, y, z, vx, vy, vz = self.state
        
        # Update velocity based on thrust and gravity
        new_vx = vx + thrust_x * self.time_step  # Assuming thrust_x is in Newtons and mass is 1 unit
        new_vy = vy + thrust_y * self.time_step
        new_vz = vz + (thrust_z - self.gravity) * self.time_step  # Thrust against gravity (self.gravity is positive)
        
        # Update position based on the new velocity
        new_x = x + new_vx * self.time_step
        new_y = y + new_vy * self.time_step
        new_z = z + new_vz * self.time_step
        
        # Ensure the rocket doesn't go below ground level
        if new_z < 0:
            new_z = 0
            new_vz = 0  # Set velocity to zero to simulate a crash
        
        # Update the rocket's state
        self.state = np.array([new_x, new_y, new_z, new_vx, new_vy, new_vz])
        
        # Reward function: penalize distance from the landing pad (assumed at (0, 0, 0)) and velocity
        distance_to_pad = np.sqrt(new_x**2 + new_y**2 + new_z**2)
        velocity_penalty = np.linalg.norm([new_vx, new_vy, new_vz])
        reward = -distance_to_pad - 0.1 * velocity_penalty  # Weight velocity penalty less than distance
        
        # Check for termination: successful landing if the rocket is on the ground with low velocity
        done = False
        if new_z == 0:
            if velocity_penalty < 0.5:  # Successful landing if velocity is low
                reward += 100  # Large reward for successful landing
                done = True
            else:
                reward -= 100  # Large penalty for crashing
                done = True
        
        # Sensor data integration
        imu_data = self.get_acceleration()  # Simulate IMU sensor for acceleration
        lidar_distance = self.get_lidar_distance(new_z)  # Simulate LIDAR sensor for height
        gps_data = self.get_gps()  # Simulate GPS data
        
        # Combine the state and sensor data into the observation
        observation = np.concatenate([self.state, imu_data, [lidar_distance], gps_data])
        
        return observation, reward, done, {}


    def render(self, mode='human'):
        # Optional rendering method, use Blender bpy to show the simulation
        pass
