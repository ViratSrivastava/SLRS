import gym
import numpy as np
from stable_baselines3 import PPOzz
from gym import spaces

class RocketLandingEnv(gym.Env):
    def __init__(self):
        super(RocketLandingEnv, self).__init__()
        
        # State space: (x, y, z, vx, vy, vz) -> 6 variables
        n_state_variables = 6
        # Sensor data: (IMU: 3, LIDAR: 1, GPS: 3) -> 7 variables
        n_sensors = 7
        
        # Define observation space (state + sensor data)
        self.observation_space = spaces.Box(low=-np.inf, high=np.inf, shape=(n_state_variables + n_sensors,), dtype=np.float32)
        
        # Define action space (thrust in x, y, z directions)
        self.action_space = spaces.Box(low=-1, high=1, shape=(3,), dtype=np.float32)
        
        # Initial state: [x, y, z, vx, vy, vz]
        self.state = np.array([0.0, 0.0, 100.0, 0.0, 0.0, 0.0])  # Start at 100m height
        self.gravity = -9.8  # Gravity
        self.time_step = 0.1  # Time step for each simulation step

    def step(self, action):
        # Apply thrust and update state (rocket physics)
        thrust_x, thrust_y, thrust_z = action
        x, y, z, vx, vy, vz = self.state
        
        # Update velocity with thrust and gravity
        new_vx = vx + thrust_x * self.time_step
        new_vy = vy + thrust_y * self.time_step
        new_vz = vz + (thrust_z + self.gravity) * self.time_step
        
        # Update position with new velocity
        new_x = x + new_vx * self.time_step
        new_y = y + new_vy * self.time_step
        new_z = max(z + new_vz * self.time_step, 0)  # Rocket can't go below ground
        
        # Update state
        self.state = np.array([new_x, new_y, new_z, new_vx, new_vy, new_vz])
        
        # Sensor data
        imu_data = self.get_acceleration()
        lidar_distance = self.get_lidar_distance(new_z)
        gps_data = self.get_gps()
        
        # Observation (state + sensor data)
        observation = np.concatenate([self.state, imu_data, [lidar_distance], gps_data])
        
        # Reward: penalize distance from target landing zone and high velocity
        reward = -np.sqrt(new_x**2 + new_y**2 + new_z**2)  # Negative distance to the landing pad
        
        # Termination conditions
        done = False
        if new_z == 0:
            velocity_penalty = np.linalg.norm([new_vx, new_vy, new_vz])
            if velocity_penalty < 0.5:
                reward += 100  # Successful landing
            else:
                reward -= 100  # Crash
            done = True

        return observation, reward, done, {}

    def reset(self):
        # Reset rocket to initial state
        self.state = np.array([0.0, 0.0, 100.0, 0.0, 0.0, 0.0])
        imu_data = self.get_acceleration()
        lidar_distance = self.get_lidar_distance(100.0)
        gps_data = self.get_gps()
        
        return np.concatenate([self.state, imu_data, [lidar_distance], gps_data])

    def get_acceleration(self):
        # Simulate IMU sensor (acceleration in x, y, z with some noise)
        return np.array([0.0, 0.0, self.gravity]) + np.random.normal(0, 0.1, 3)

    def get_lidar_distance(self, z):
        # Simulate LIDAR sensor (distance to ground)
        return z + np.random.normal(0, 0.05)  # Add some noise

    def get_gps(self):
        # Simulate GPS sensor (position with noise)
        return np.array([self.state[0], self.state[1], self.state[2]]) + np.random.normal(0, 0.5, 3)

# Create the environment
env = RocketLandingEnv()

# Use the PPO algorithm from stable-baselines3
model = PPO("MlpPolicy", env, verbose=1)

# Train the model
model.learn(total_timesteps=100000)

# Save the model
model.save("ppo_rocket_landing")

# Load and test the trained model
model = PPO.load("ppo_rocket_landing")

obs = env.reset()
for _ in range(1000):
    action, _states = model.predict(obs, deterministic=True)
    obs, reward, done, info = env.step(action)
    if done:
        obs = env.reset()
