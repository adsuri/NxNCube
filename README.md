A C++ program that simulates an NxNxN Rubik's Cube by using a 2D net that is printed in the terminal.
Intended for use with WSL/Linux.

Instructions:
  1. Clone into this repository
  2. Install g++ if it is not installed already on your machine
  3. Install CMake if it is not installed already on your machine
  4. To build the executable, run these commands in your terminal in the project directory:
      1. `cmake -s .B build`
      2. `cmake --build build`
  5. To run the executable, run this command in the project directory:
      1. `build/nxncube.exe LAYERS`
      2. `LAYERS` represents the number of layers to generate the Rubik's Cube with