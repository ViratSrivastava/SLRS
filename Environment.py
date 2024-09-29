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
        # Apply action (thrust in x, y, z directions)
        thrust_x, thrust_y, thrust_z = action
        
        # Update state based on action and physics
        x, y, z, vx, vy, vz = self.state
        
        # Update velocity based on thrust and gravity
        new_vx = vx + thrust_x * self.time_step
        new_vy = vy + thrust_y * self.time_step
        new_vz = vz + (thrust_z + self.gravity) * self.time_step
        
        # Update position based on velocity
        new_x = x + new_vx * self.time_step
        new_y = y + new_vy * self.time_step
        new_z = z + new_vz * self.time_step
        
        # Update state
        self.state = np.array([new_x, new_y, new_z, new_vx, new_vy, new_vz])
        
        # Calculate reward: proximity to the landing pad and stability
        reward = -np.sqrt(new_x**2 + new_y**2 + (new_z - 0)**2)  # Negative distance to the landing pad
        
        # Termination conditions: either successful landing or crash
        done = new_z <= 0  # Rocket has landed or crashed
        # Sensor data integration
        imu_data = self.get_acceleration()
        lidar_distance = self.get_lidar_distance()
         gps_data = self.get_gps()
        
        # Append sensor data to observation
         observation = np.concatenate([self.state, imu_data, [lidar_distance], gps_data])
        return self.state, reward, done, {}

    def render(self, mode='human'):
        # Optional rendering method, use Blender bpy to show the simulation
        pass
