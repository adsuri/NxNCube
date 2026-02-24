# NxNCube

A C++ program that simulates an NxNxN Rubik's Cube by using a 2D net that is printed in the terminal.
Intended for use with WSL/Linux.

## Instructions:
  1. Clone into this repository
  2. To build the executable, run these commands in your terminal in the project directory:
      ```bash
      make
      ```
  3. To run the executable, run this command in the project directory:
      - `build/nxncube LAYERS [letters]`
          - `LAYERS` represents the number of layers to generate the Rubik's Cube with
          - `[letters]` is an optional argument that replaces the solid blocks of color with letters
  4. To manipulate the cube, enter in a list of moves in this format:
      - `[layers-]move` where `move` is in {`"u"`, `"ui"`, `"u2"`, `"l"`, `"li"`, `"l2"`, `"f"`, `"fi"`, `"f2"`, `"r"`, `"ri"`, `"r2"`, `"b"`, `"bi"`, `"b2"`,  `"d"`, `"di"`, `"d2"`, `"x"`, `"xi"`, `"x2"`, `"y"`, `"yi"`, `"y2"`, `"z"`, `"zi"`, `"z2"`} and `layers` is to optionally specify how many layers to turn at once.
        - Note: When specifying a depth, you cannot use a cube rotation.
      - `scramble` to scramble the cube
      - `reset` to solve the cube
      - `exit` to leave the program

## TODO
  - Add saving and loading feature
  - Clean up code for cube turns (maybe)