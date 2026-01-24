A C++ program that simulates an NxNxN Rubik's Cube by using a 2D net that is printed in the terminal.
Intended for use with WSL/Linux.

Instructions:
  1. Clone into this repository
  2. Install g++ if it is not installed already on your machine
  3. To build the executable, run this command in your terminal in the project directory:
      1. `make build/nxncube`
  4. To run the executable, run this command in the project directory:
      1. `build/nxncube LAYERS`
      2. `LAYERS` represents the number of layers to generate the Rubik's Cube with

TODO:
  * Finish basic moves
  * Add rotations to rotate entire cube more efficiently than rotating all layers at once
  * Scramble function and argument
  * Solve check with timer (?)
  * Parse multiple moves in a single input (?)