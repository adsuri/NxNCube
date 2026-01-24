#ifndef NxNCube_HPP
#define NxNCube_HPP

#include <string>
#include <vector>
#include <iostream>

class NxNCube {
 private:
  int n;

  enum color {
    WHITE,
    ORANGE,
    GREEN,
    RED,
    BLUE,
    YELLOW,
    RESET
  };

  inline static const std::string stickers[] = {"\033[1;38;2;255;255;255;49mW",
                                                "\033[1;38;2;255;165;0;49mO",
                                                "\033[1;38;2;0;255;0;49mG",
                                                "\033[1;38;2;255;0;0;49mR",
                                                "\033[1;38;2;0;0;255;49mB",
                                                "\033[1;38;2;255;255;0;49mY",
                                                "\033[0m"};
  friend std::ostream &operator<<(std::ostream &os, NxNCube::color val);

  std::vector<std::vector<NxNCube::color>> m_top;
  std::vector<std::vector<NxNCube::color>> m_left;
  std::vector<std::vector<NxNCube::color>> m_front;
  std::vector<std::vector<NxNCube::color>> m_right;
  std::vector<std::vector<NxNCube::color>> m_back;
  std::vector<std::vector<NxNCube::color>> m_bottom;

  inline static const std::vector<std::string> VALID_MOVES = {"u", "ui", "u2",
                                                              "l", "li", "l2",
                                                              "f", "fi", "f2",
                                                              "r", "ri", "r2",
                                                              "b", "bi", "b2",
                                                              "d", "di", "d2"};

  /**
   * @brief Rotates the elements in the 2D `vector` representing the given `face` clockwise by a quarter-turn
   * 
   * This does not affect the faces bordering the target `face`. That logic is taken care of in `this->move()`.
   * 
   * @param face Reference to {`this->top`, `left`, `front`, `right`, `back`, or `bottom`}
   * 
   */
  void rotate_cw(std::vector<std::vector<NxNCube::color>> &face);

  /**
   * @brief Rotates the elements in the 2D `vector` representing the given `face` counter-clockwise by a quarter-turn
   * 
   * This does not affect the faces bordering the target `face`. That logic is taken care of in `this->move()`.
   * 
   * @param face Reference to {`this->top`, `left`, `front`, `right`, `back`, or `bottom`}
   * 
   */
  void rotate_ccw(std::vector<std::vector<NxNCube::color>> &face);

  /**
   * @brief Rotates the elements in the 2D `vector` representing the given `face` by a half-turn
   * 
   * This does not affect the faces bordering the target `face`, that logic is taken care of in `this->move()`.
   * 
   * @param face Reference to {`this->top`, `left`, `front`, `right`, `back`, or `bottom`}
   * 
   */
  void rotate_half_turn(std::vector<std::vector<NxNCube::color>> &face);

  /**
   * @brief Checks if a `string` is a valid move for a turn
   * 
   * @param input Type of move
   * @return `true` if `input` represents a valid move, `false` otherwise
   * 
   */
  bool is_valid_move(const std::string &input) const;

  /**
   * @brief Checks if a `string` is a valid number of layers for a turn
   * 
   * @param input Number of layers (in string form)
   * 
   * @return `true` if `input` represents a valid depth, `false` otherwise
   * 
   */
  bool is_valid_depth(const std::string &input) const;

  /**
   * @brief Does a move on the cube, modifying the appropriate faces
   * 
   * @param move The move to do, must be in {`"u"`, `"ui"`, `"u2"`, `"l"`, `"li"`, `"l2"`, `"f"`, `"fi"`, `"f2"`, `"r"`, `"ri"`, `"r2"`, `"b"`, `"bi"`, `"b2"`, `"d"`, `"di"`, `"d2"`}
   * @param depth Number of layers to move at once (0 < depth <= n)
   * 
   */
  void move(const std::string &move, int depth);

 public:
  /**
   * @brief Construct a new NxNCube object
   * 
   * @param layers Number of layers in the cube (layers > 0)
   */
  NxNCube(int layers);

  /**
   * @brief Displays a 2D net representing the state of the puzzle
   * 
   */
  void draw() const;

  /**
   * @brief Clears the console
   * 
   */
  void clear_console() const;

  /**
   * @brief Clears the console and calls this->draw()
   * 
   */
  void clear_draw() const;
  
  /**
   * @brief Starts the main game loop
   * 
   */
  void play();
};

std::ostream &operator<<(std::ostream &os, NxNCube::color val);

#endif