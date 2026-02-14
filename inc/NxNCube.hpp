/*
 * Copyright (C) 2026 Aditya Suri
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

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

  using Face = std::vector<NxNCube::color>; 
  using MovePair = std::pair<std::string, int>;
  using SplitMove = std::pair<std::string, std::string>;

  Face m_top;
  Face m_left;
  Face m_front;
  Face m_right;
  Face m_back;
  Face m_bottom;

  std::string m_last_error;

  inline static bool BLOCKS;

  inline static const std::string STICKERS_BLOCKS[] = {"\033[1;38;2;255;255;255;49m██",
                                                                  "\033[1;38;2;255;165;0;49m██",
                                                                  "\033[1;38;2;0;255;0;49m██",
                                                                  "\033[1;38;2;255;0;0;49m██",
                                                                  "\033[1;38;2;0;0;255;49m██",
                                                                  "\033[1;38;2;255;255;0;49m██",
                                                                  "\033[0m"};

  inline static const std::string STICKERS_LETTERS[] = {"\033[1;38;2;255;255;255;49mW ",
                                                                   "\033[1;38;2;255;165;0;49mO ",
                                                                   "\033[1;38;2;0;255;0;49mG ",
                                                                   "\033[1;38;2;255;0;0;49mR ",
                                                                   "\033[1;38;2;0;0;255;49mB ",
                                                                   "\033[1;38;2;255;255;0;49mY ",
                                                                   "\033[0m"};
  friend std::ostream &operator<<(std::ostream &os, NxNCube::color val);

  inline static const std::vector<std::string> VALID_MOVES = {"u", "ui", "u2",
                                                              "l", "li", "l2",
                                                              "f", "fi", "f2",
                                                              "r", "ri", "r2",
                                                              "b", "bi", "b2",
                                                              "d", "di", "d2",
                                                              "x", "xi", "x2",
                                                              "y", "yi", "y2",
                                                              "z", "zi", "z2"};

  inline static const std::vector<std::string> VALID_MOVES_NO_ROTATIONS = {"u", "ui", "u2",
                                                                           "l", "li", "l2",
                                                                           "f", "fi", "f2",
                                                                           "r", "ri", "r2",
                                                                           "b", "bi", "b2",
                                                                           "d", "di", "d2"};

  inline static const std::vector<std::string> CMD_LIST = {"scramble",
                                                           "exit",
                                                           "reset"};

  /**
   * @brief Converts a 2D index `[r][c]` to a 1D index for a `this->n` x `this->n` long vector
   * 
   * @param r Row index (0 <= r < this->n)
   * @param c Column index (0 <= c < this->n)
   * @return Equivalent 1D index
   * 
   */
  int idx(int r, int c) const noexcept;

  /**
   * @brief Rotates the elements in the 2D `vector` representing the given `face` clockwise by a quarter-turn
   * 
   * This does not affect the faces bordering the target `face`. That logic is taken care of in `this->move()`.
   * 
   * @param face Reference to {`this->top`, `left`, `front`, `right`, `back`, or `bottom`}
   * 
   */
  void rotate_cw(Face &face);

  /**
   * @brief Rotates the elements in the 2D `vector` representing the given `face` counter-clockwise by a quarter-turn
   * 
   * This does not affect the faces bordering the target `face`. That logic is taken care of in `this->move()`.
   * 
   * @param face Reference to {`this->top`, `left`, `front`, `right`, `back`, or `bottom`}
   * 
   */
  void rotate_ccw(Face &face);

  /**
   * @brief Rotates the elements in the 2D `vector` representing the given `face` by a half-turn
   * 
   * This does not affect the faces bordering the target `face`, that logic is taken care of in `this->move()`.
   * 
   * @param face Reference to {`this->top`, `left`, `front`, `right`, `back`, or `bottom`}
   * 
   */
  void rotate_half_turn(Face &face);

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

  /**
   * @brief Scrambles the cube
   * 
   * Scramble length grows roughly with n^2 / log n
   * 
   */
  void scramble();

  /**
   * @brief Attempts to split a `string` using a dash
   * 
   * @param str Move to split
   * @return `std::pair` containing each part, {"BAD_MOVE", "BAD_MOVE"} otherwise
   * 
   */
  SplitMove split_move(const std::string &str) const;

  /**
   * @brief Attempts to parse a move from a string
   * 
   * @param str `string` to parse
   * @return `std::pair` containing move information, {"BAD_MOVE", -1} otherwise
   * 
   */
  MovePair grab_move_pair(const std::string &str) const;

 public:
  /**
   * @brief Construct a new NxNCube object
   * 
   * @param layers Number of layers in the cube (layers > 0)
   */
  NxNCube(int layers, bool blocks);

  /**
   * @brief Displays a 2D net representing the state of the puzzle
   * 
   */
  void draw();

  /**
   * @brief Clears the console
   * 
   */
  void clear_console() const;

  /**
   * @brief Clears the console and calls this->draw()
   * 
   */
  void clear_draw();
  
  /**
   * @brief Starts the main game loop
   * 
   */
  void play();
};

std::ostream &operator<<(std::ostream &os, NxNCube::color val);

#endif