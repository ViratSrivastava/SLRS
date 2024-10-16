# Installation For Essential Requirements

## CPP "vcpkg" Installation

Generally `vcpkg` is not installed or not recognized on your system.

`vcpkg` is a tool that simplifies the process of installing and managing C++ libraries like `libpqxx`.

Here's how you can set it up:

### Steps to Install and Use `vcpkg` on Windows

1. **Download `vcpkg`**:
   - Open PowerShell and clone the `vcpkg` repository:

     ```bash
     git clone https://github.com/microsoft/vcpkg.git
     cd vcpkg
     ```

2. **Bootstrap `vcpkg`**:
   - Run the bootstrap script to build `vcpkg`:

     ```bash
     .\bootstrap-vcpkg.bat
     ```

3. **Add `vcpkg` to Path (optional)**:
   - To make `vcpkg` accessible from anywhere in your terminal, add it to your system's PATH:

     ```bash
     [System.Environment]::SetEnvironmentVariable("Path", "$env:Path;C:\path\to\vcpkg", [System.EnvironmentVariableTarget]::Machine)
     ```

   - Close and reopen your terminal for the changes to take effect.

4. **Install `libpqxx` using `vcpkg`**:
   - Now that `vcpkg` is set up, you can install `libpqxx`:

     ```bash
     .\vcpkg install libpqxx
     ```

5. **Link `vcpkg` with your Project**:
   - Use `vcpkg` with your project by specifying the `vcpkg` toolchain file in your C++ build command (using `g++`):

     ```bash
     g++ rocket_descent.cpp -o rocket_descent -I[path_to_vcpkg]/installed/x64-windows/include -L[path_to_vcpkg]/installed/x64-windows/lib -lpqxx -lpq
     ```

Once these steps are complete, you should be able to use PostgreSQL in your C++ project.
