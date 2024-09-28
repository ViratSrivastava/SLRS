---

# Self-Landing Rocket System (SLRS)

Welcome to the Self-Landing Rocket System (SLRS) repository! This collection contains various software modules implemented in C++, Python, and MATLAB designed for the development of a self-landing rocket.


<div align="center">
    <img src="https://github.com/user-attachments/assets/1829abd7-7ca6-4d64-8548-47c86513c4ff" alt="Rocket Image" />
</div>


## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Repository Structure](#repository-structure)
- [Contributing](#contributing)
- [License](#license)

## Introduction

The SLRS project aims to revolutionize autonomous rocket landing technology by leveraging advanced control algorithms, machine learning models, and sensor integration. By developing a system that can precisely control a rocket's descent and landing, we seek to improve the safety, reliability, and efficiency of space missions. This repository contains the core software components necessary for achieving these objectives.

### Key Objectives
- Autonomous Control: Develop algorithms that allow the rocket to autonomously control its descent and landing in real-time.
- Precision Landing: Utilize sensor data and machine learning to accurately identify and target the landing site.
- Robust Integration: Ensure seamless integration of software and hardware components for reliable operation.

## Features

- **C++ Modules**: Real-time control algorithms and flight dynamics.
- **Python Scripts**: Data analysis, simulation, and visualization tools.
- **MATLAB Components**: Simulation and modeling of rocket dynamics.

## Installation

To get started with SLRS, follow these steps:

1. Clone the repository:
   ```sh
   git clone https://github.com/ViratSrivastava/SLRS.git
   cd SLRS
   pip install tensorflow gym blender bpy stable-baselines3
   ```

2. Install the necessary dependencies for each module:
   - For C++:
     ```sh
     sudo apt-get install build-essential
     ```
   - For Python:
     ```sh
     pip install -r requirements.txt
     ```
   - For MATLAB:
     Ensure you have MATLAB installed with the necessary toolboxes.
     ```sh
     ----------To be uploaded------
     ```

## Usage

### C++ Modules
For the Self-Landing Rocket System (SLRS) project, we chose C++ due to its superior performance and low-level hardware access. C++ ensures our real-time control algorithms run efficiently and allows direct interfacing with the rocket's sensors and actuators.

C++'s object-oriented features help us manage software complexity with modular components, and its extensive libraries streamline development. Its cross-platform compatibility facilitates testing across different environments, and strong community support accelerates our progress.

Overall, C++ is ideal for SLRS, providing the performance, control, and flexibility needed for a robust self-landing rocket system.
Navigate to the `cpp` directory and follow the instructions in the `README.md` file to compile and run the C++ programs.

### Python Scripts

For machine learning models in computer vision, we use Python. Python's extensive libraries and frameworks, such as TensorFlow and PyTorch, make it ideal for developing and deploying sophisticated machine learning algorithms. Its ease of use and powerful data processing capabilities accelerate our development process in these areas.

Navigate to the `python` directory. The `README.md` file there provides detailed instructions on how to execute the Python scripts and use the simulation tools.

### MATLAB Components

Navigate to the `matlab` directory. The `README.md` file in this directory explains how to run the MATLAB simulations and use the provided models.

## Repository Structure

```
SLRS/
├── cpp/
│   ├── src/
│   ├── include/
│   ├── CMakeLists.txt
│   └── README.md
├── python/
│   ├── scripts/
│   ├── notebooks/
│   ├── requirements.txt
│   └── README.md
├── matlab/
│   ├── models/
│   ├── scripts/
│   └── README.md
├── LICENSE
└── README.md
```

## Contributing

Contributions are welcome! If you have suggestions for improvements or new features, feel free to open an issue or submit a pull request. Please follow the guidelines outlined in the [CONTRIBUTING.md](CONTRIBUTING.md) file.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

---
