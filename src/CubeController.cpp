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

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <cassert>

#include "CubeController.hpp"
#include "NxNCube.hpp"
#include "util.hpp"

CubeController::CubeController(int layers, bool blocks)
 : m_cube(layers, blocks),
   m_solve_state(CubeController::solve_state::NOT_SOLVING), 
   m_start_time(),
   m_curr_time() {}

CubeController::SplitMove CubeController::split_move(const std::string &str) const {
  const SplitMove BAD_MOVE = {"BAD_MOVE", "BAD_MOVE"};
  const std::string delim = "-";
  int delim_index = -1;

  for (int i = 0; i < str.length(); ++i) {
    const char c = str[i];

    if (c == '-') {
      delim_index = i;
      continue;
    }
  }

  if (delim_index == -1 || delim_index == 0 || delim_index == str.length() - 1) { return BAD_MOVE; }

  std::string first_part;
  std::string second_part;

  for (int i = 0; i < delim_index; ++i) {
    first_part += str[i];
  }
  for (int i = delim_index + 1; i < str.length(); ++i) {
    second_part += str[i];
  }

  return {first_part, second_part};
}

CubeController::MovePair CubeController::grab_move_pair(const std::string &str) const {
  const MovePair BAD_MOVE = {"BAD_MOVE", -1};

  if (util::str_in_vector(NxNCube::VALID_MOVES, str)) { return {str, 1}; }

  SplitMove move = this->split_move(str);

  if (!m_cube.is_valid_depth(move.first)) { return BAD_MOVE; }
  if (move.second == "BAD_MOVE" || (!util::str_in_vector(NxNCube::VALID_MOVES_NO_ROTATIONS, move.second))) {
    return BAD_MOVE;
  }

  return {move.second, std::stoi(move.first)};
}

void CubeController::play() {
  std::string input;

  while (true) {
    m_cube.clear_draw();

    switch (m_solve_state) {
      case CubeController::solve_state::NOT_SOLVING: {
        break;
      }
      case CubeController::solve_state::WAITING_TO_START: {
        m_last_solve_msg = "Timer will start when you enter a valid move or scramble the cube.";
        break;
      }
      case CubeController::solve_state::SOLVING: {
        m_curr_time = std::chrono::steady_clock::now();
        double elapsed_time = std::chrono::duration<double>(m_curr_time - m_start_time).count();

        if (m_cube.is_solved()) {
          m_solve_state = CubeController::solve_state::NOT_SOLVING;
          m_last_solve_msg += "Solved! Time was: ";
        }

        m_last_solve_msg += util::format_time(elapsed_time);

        break;
      }
    }

    if (m_last_solve_msg != "") {
      std::cout << m_last_solve_msg << std::endl;
    }
    m_last_solve_msg = "";

    if (m_last_error != "") {
      std::cout << m_last_error << std::endl;
    }
    m_last_error = "";

    std::vector<std::string> args;
    if (!util::grab_input(&args)) { return; } // handles EOF
    
    if (args.size() == 0) {
      m_last_error = "\033[1;38;2;255;0;0;49mEnter a valid command or list of moves\033[0m";
      continue;
    }

    bool is_cmd = util::str_in_vector(CubeController::CMD_LIST, args[0]);
    bool is_move = (this->grab_move_pair(args[0])).first != "BAD_MOVE";

    bool is_first_arg_valid = is_cmd || is_move;

    if (!is_first_arg_valid) {
      m_last_error = "\033[1;38;2;255;0;0;49mEnter a valid command or list of moves\033[0m";
      continue;
    }

    if (is_move) {
      std::vector<MovePair> moves_to_do;
      bool are_moves_valid = true;

      for (int i = 0; i < args.size(); ++i) {
        MovePair curr_pair = this->grab_move_pair(args[i]);
        if (curr_pair.first == "BAD_MOVE") {
          m_last_error = "\033[1;38;2;255;0;0;49m`";
          m_last_error += args[i];
          m_last_error += "` is not a valid move\033[0m";
          are_moves_valid = false;
          continue;
        }

        moves_to_do.push_back(curr_pair);
      }

      if (are_moves_valid) {
        for (const MovePair &curr_move : moves_to_do) {
          m_cube.move(curr_move.first, curr_move.second);
        } 

        if (m_solve_state == CubeController::solve_state::WAITING_TO_START) {
          m_solve_state = CubeController::solve_state::SOLVING;
          m_start_time = std::chrono::steady_clock::now();
        }
      }
    } else if (args[0] == "scramble") {
      if (args.size() != 1) {
        m_last_error = "\033[1;38;2;255;0;0;49m`scramble` has no arguments\033[0m";
      } else {
        m_cube.scramble();
        if (m_solve_state == CubeController::solve_state::WAITING_TO_START) {
          m_solve_state = SOLVING;
          m_start_time = std::chrono::steady_clock::now();
        }
      }
    } else if (args[0] == "time-solve") {
      m_solve_state = CubeController::solve_state::WAITING_TO_START;
      m_cube.scramble();
    } else if (args[0] == "exit") {
      return;
    } else if (args[0] == "reset") {
      m_cube.reset();
      m_solve_state = CubeController::solve_state::NOT_SOLVING;
    } else {
      std::cout << "You shouldn't have gotten here..." << std::endl;
      assert(false);
    }
  }
}