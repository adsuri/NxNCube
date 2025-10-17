#ifndef NxNCube_H
#define NxNCube_H
#include <string>
#include <vector>

class NxNCube {
private:
  int n;
  std::vector<std::vector<std::string>> top;
  std::vector<std::vector<std::string>> left;
  std::vector<std::vector<std::string>> front;
  std::vector<std::vector<std::string>> right;
  std::vector<std::vector<std::string>> back;
  std::vector<std::vector<std::string>> bottom;

  // REQUIRES: face is this->top, left, front, right, back, or bottom
  // MODIFIES: Appropriate side of cube
  // EFFECTS: Rotates the nested vector representing the side of the cube by 90 degrees clockwise.
  void rotate_cw(std::vector<std::vector<std::string>> &face);

  // REQUIRES: face is this->top, left, front, right, back, or bottom
  // MODIFIES: Appropriate side of cube
  // EFFECTS: Rotates the nested vector representing the side of the cube by 90 degrees counterclockwise.
  void rotate_ccw(std::vector<std::vector<std::string>> &face);

  // REQUIRES: face is this->top, left, front, right, back, or bottom
  // MODIFIES: Appropriate side of cube
  // EFFECTS: Rotates the nested vector representing the side of the cube by 180 degrees.
  void rotate_half_turn(std::vector<std::vector<std::string>> &face);

  // EFFECTS: Returns true if value is in str
  static bool str_in_vector(std::vector<std::string> str, std::string value);

  // EFFECTS: Returns str with all characters converted to lowercase
  static std::string string_lower(std::string str);

  // EFFECTS: Returns true if input is a valid move
  static bool valid_move(std::string &input);

  // EFFECTS: Returns true if input is a valid amount of layers for a nxn NxNCube
  static bool valid_move_layers(std::string &input, int n);
public:
  inline static const std::string white = "\033[1;38;2;255;255;255;49mW\033[0m";
  inline static const std::string orange = "\033[1;38;2;255;165;0;49mO\033[0m";
  inline static const std::string green = "\033[1;38;2;0;255;0;49mG\033[0m";
  inline static const std::string red = "\033[1;38;2;255;0;0;49mR\033[0m";
  inline static const std::string blue = "\033[1;38;2;0;0;255;49mB\033[0m";
  inline static const std::string yellow = "\033[1;38;2;255;255;0;49mY\033[0m";
  inline static const std::vector<std::string> moves = {"u", "ui", "u2",
                                                        "l", "li", "l2",
                                                        "f", "fi", "f2",
                                                        "r", "ri", "r2",
                                                        "b", "bi", "b2",
                                                        "d", "di", "d2"};

  // // EFFECTS: Clears the console
  // static void clear_console();

  // EFFECTS: Returns true if str is a positive integer
  static bool is_positive_int(std::string str);

  // // EFFECTS: Returns true if value is in str
  // static bool str_in_vector(std::vector<std::string> str, std::string value);

  // // EFFECTS: Returns str with all characters converted to lowercase
  // static std::string string_lower(std::string str);

  // // EFFECTS: Returns true if input is a valid move
  // static bool valid_move(std::string &input);

  // // EFFECTS: Returns true if input is a valid amount of layers for a nxn NxNCube
  // static bool valid_move_layers(std::string &input, int n);

  // REQUIRES: layers > 0
  // EFFECTS: Initializes an NxNCube object with 6 layers x layers nested vectors representing each side of a cube.
  NxNCube(int layers);

  // EFFECTS: Prints a 2d net representing the cube onto the terminal.
  void draw() const;

  // EFFECTS: Clears the console
  static void clear_console();

  // EFFECTS: Clears the console and calls this->draw()
  void clear_draw() const;

  // REQUIRES: move is in {"u", "ui", "u2", "l", "li", "l2", "f", "fi", "f2", "r", "ri", "r2", "b", "bi", "b2", "d", "di", "d2"}, 
  // MODIFIES: All relevant faces
  // EFFECTS: Simulates a rotation of a face and twists depth layers.
  void move(std::string move, int depth);

  void printColors();
  
  // Main game loop
  void play();
};

#endif