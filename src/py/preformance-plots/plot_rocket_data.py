import pandas as pd
import matplotlib.pyplot as plt

# Read the CSV file
data = pd.read_csv('rocket_output.csv')

# Plot the data
plt.figure(figsize=(10, 8))

# Plot Time vs Thrust
plt.subplot(2, 2, 1)
plt.plot(data['Time'], data['Thrust'], label='Thrust')
plt.xlabel('Time (s)')
plt.ylabel('Thrust (N)')
plt.title('Time vs Thrust')
plt.grid(True)

# Plot Time vs Remaining Fuel
plt.subplot(2, 2, 2)
plt.plot(data['Time'], data['RemainingFuel'], label='Remaining Fuel', color='orange')
plt.xlabel('Time (s)')
plt.ylabel('Remaining Fuel (kg)')
plt.title('Time vs Remaining Fuel')
plt.grid(True)

# Plot Time vs Current Mass
plt.subplot(2, 2, 3)
plt.plot(data['Time'], data['CurrentMass'], label='Current Mass', color='green')
plt.xlabel('Time (s)')
plt.ylabel('Current Mass (kg)')
plt.title('Time vs Current Mass')
plt.grid(True)

# Adjust layout and show the plot
plt.tight_layout()
plt.show()
