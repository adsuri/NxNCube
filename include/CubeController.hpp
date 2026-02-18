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

#ifndef CUBECONTROLLER_HPP
#define CUBECONTROLLER_HPP

#include <string>
#include <vector>
#include <chrono>

#include "NxNCube.hpp"
#include "util.hpp"

class CubeController {
 private:
  NxNCube m_cube;

  enum solve_state {
    NOT_SOLVING,
    WAITING_TO_START,
    SOLVING
  };

  using MovePair = std::pair<std::string, int>;
  using SplitMove = std::pair<std::string, std::string>;

  std::string m_last_error;

  solve_state m_solve_state;
  std::string m_last_solve_msg;
  std::chrono::steady_clock::time_point m_start_time;
  std::chrono::steady_clock::time_point m_curr_time;

  inline static const std::vector<std::string> CMD_LIST = {"scramble",
                                                           "time-solve",
                                                           "exit",
                                                           "reset"};

  SplitMove split_move(const std::string &str) const;

  MovePair grab_move_pair(const std::string &str) const;

 public:
  CubeController(int layers, bool blocks);

  void play();
};

#endif