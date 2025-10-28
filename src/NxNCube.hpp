#ifndef NxNCube_HPP
#define NxNCube_HPP
#include <string>
#include <vector>

// bool str_in_vector(const std::vector<std::string> &str, std::string value) {
//   for (size_t i = 0; i < str.size(); ++i) {
//     if (str[i] == value) {
//       return true;
//     }
//   }
//   return false;
// }

class NxNCube {
private:
  int n;
  std::vector<std::vector<std::string>> top;
  std::vector<std::vector<std::string>> left;
  std::vector<std::vector<std::string>> front;
  std::vector<std::vector<std::string>> right;
  std::vector<std::vector<std::string>> back;
  std::vector<std::vector<std::string>> bottom;
  inline static const std::string WHITE = "\033[1;38;2;255;255;255;49mW";
  inline static const std::string ORANGE = "\033[1;38;2;255;165;0;49mO";
  inline static const std::string GREEN = "\033[1;38;2;0;255;0;49mG";
  inline static const std::string RED = "\033[1;38;2;255;0;0;49mR";
  inline static const std::string BLUE = "\033[1;38;2;0;0;255;49mB";
  inline static const std::string YELLOW = "\033[1;38;2;255;255;0;49mY";
  inline static const std::string CLEAR_COLOR = "\033[0m";
  inline static const std::vector<std::string> valid_moves = {"u", "ui", "u2",
                                                              "l", "li", "l2",
                                                              "f", "fi", "f2",
                                                              "r", "ri", "r2",
                                                              "b", "bi", "b2",
                                                              "d", "di", "d2"};

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

  // EFFECTS: Returns str with all characters converted to lowercase
  static std::string STRING_LOWER(std::string str);

  // EFFECTS: Returns true if input is a valid move
  static bool IS_VALID_MOVE(std::string &input);

  // EFFECTS: Returns true if input is a valid amount of layers for an NxNCube with n layers
  static bool IS_VALID_DEPTH(std::string &input, int n);

  // REQUIRES: move is in {"u", "ui", "u2", "l", "li", "l2", "f", "fi", "f2", "r", "ri", "r2", "b", "bi", "b2", "d", "di", "d2"}, 
  // MODIFIES: All relevant faces
  // EFFECTS: Simulates a rotation of a face and twists depth layers.
  void move(std::string move, int depth);
public:
  // EFFECTS: Returns true if str is a positive integer
  static bool IS_POSITIVE_INT(std::string str);

  // REQUIRES: layers > 0
  // EFFECTS: Initializes an NxNCube object with 6 layers x layers nested vectors representing each side of a cube.
  NxNCube(int layers);

  // EFFECTS: Prints a 2D net representing the cube onto the terminal.
  void draw() const;

  // EFFECTS: Clears the console
  static void CLEAR_CONSOLE();

  // EFFECTS: Clears the console and calls this->draw()
  void clear_draw() const;
  
  // Main game loop
  void play();
};

#endif