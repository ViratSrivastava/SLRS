from stable_baselines3 import PPO
from stable_baselines3.common.env_checker import check_env

# Create the environment
env = RocketLandingEnv()

# Check if the environment is valid
check_env(env)

# Define the RL model
model = PPO("MlpPolicy", env, verbose=1)

# Train the model
model.learn(total_timesteps=100000)

# Save the trained model
model.save("rocket_landing_model")

# Load the model for future use
# model = PPO.load("rocket_landing_model")

# Test the trained model
obs = env.reset()
for _ in range(1000):
    action, _states = model.predict(obs)
    obs, rewards, dones, info = env.step(action)
    env.render()
