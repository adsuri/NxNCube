A C++ program that simulates an NxNxN Rubik's Cube by using a 2D net that is printed in the terminal.
Intended for use with WSL/Linux.

Instructions:
  1. Clone into this repository
  2. To build the executable, run these commands in your terminal in the project directory:
      1. `mkdir build`
      2. `make`
  3. To run the executable, run this command in the project directory:
      1. `build/nxncube LAYERS [letters]`
          1. `LAYERS` represents the number of layers to generate the Rubik's Cube with
          2. `[letters]` is an optional argument that replaces the solid blocks of color with letters

TODO:
  * Make inputting commands to the cube more modular (ex:`command [args]`)
  * Parse multiple moves in a single input
  * Solve check with timer (?)