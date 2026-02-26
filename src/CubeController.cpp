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
#include <filesystem>

#include "CubeController.hpp"
#include "NxNCube.hpp"
#include "util.hpp"

CubeController::CubeController(int layers, bool blocks)
 : m_cube(layers, blocks),
   m_solve_state(CubeController::solve_state::NOT_SOLVING), 
   m_start_time(),
   m_curr_time(),
   m_time_offset() {}

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
    std::vector<std::string> args_cap; // preserves capitalization
    if (!util::grab_input(&args_cap)) { return; } // handles EOF
    for (int i = 0; i < args_cap.size(); ++i) {
      args.push_back(util::string_lower(args_cap[i]));
    }
    
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

    } else if (args[0] == "save") {
      // save state
      if (m_solve_state != CubeController::solve_state::NOT_SOLVING) {
        m_solve_state = CubeController::solve_state::NOT_SOLVING;
      } // this might change later

      if (args.size() != 2) {
        m_last_error = "\033[1;38;2;255;0;0;49mPlease enter an .nxn file name to save to. It should be an absolute or home-relative path.\033[0m";
      } else {
        std::string filename = args_cap[1];

        if (!filename.empty() && filename[0] == '~') {
          const char* home = std::getenv("HOME");
          if (!home) {
              m_last_error = "\033[1;38;2;255;0;0;49mCould not find home directory\033[0m";
              return;
          }

          if (filename.size() == 1) {
            filename = home;
          } else if (filename[1] == '/') {
            filename = std::string(home) + filename.substr(1);
          } else {
            m_last_error = "\033[1;38;2;255;0;0;49mKeep your hands out of other users' directories.\033[0m";
            return;
          }
        }
        
        std::filesystem::path file_path(filename);

        bool valid = file_path.extension() == ".nxn" && file_path.is_absolute();

        if (valid) {
          if (!m_cube.save_state(filename)) {
            m_last_error = "\033[1;38;2;255;0;0;49mSaving failed...\033[0m";
          } else {
            m_last_error = "Saved cube state successfully to: ";
            m_last_error += file_path.string();
          }
        } else {
          m_last_error = "\033[1;38;2;255;0;0;49mEnter a filename ending with `.nxn`. It must be an absolute or home-relative path.\033[0m";
        }
      }

    } else if (args[0] == "load") {
      // load state
      if (m_solve_state != CubeController::solve_state::NOT_SOLVING) {
        m_solve_state = CubeController::solve_state::NOT_SOLVING;
      } // this might change later

      if (args.size() != 2) {
        m_last_error = "\033[1;38;2;255;0;0;49mPlease enter an .nxn file name to Load from. It should be an absolute or home-relative path.\033[0m";
      } else {
        std::string filename = args_cap[1];

        if (!filename.empty() && filename[0] == '~') {
          const char* home = std::getenv("HOME");
          if (!home) {
              m_last_error = "\033[1;38;2;255;0;0;49mCould not find home directory\033[0m";
              return;
          }

          if (filename.size() == 1) {
            filename = home;
          } else if (filename[1] == '/') {
            filename = std::string(home) + filename.substr(1);
          } else {
            m_last_error = "\033[1;38;2;255;0;0;49mKeep your hands out of other users' directories.\033[0m";
            return;
          }
        }
        
        std::filesystem::path file_path(filename);

        bool valid = file_path.extension() == ".nxn" && file_path.is_absolute();

        if (valid) {
          if (!m_cube.load_state(filename).first) {
            m_last_error = "\033[1;38;2;255;0;0;49mLoading failed... You may have a save file that is malformed or meant for a cube of a different size.\033[0m";
          } else {
            m_last_error = "Loaded cube state successfully from: ";
            m_last_error += file_path.string();
          }
        } else {
          m_last_error = "\033[1;38;2;255;0;0;49mEnter a filename ending with `.nxn`. It must be an absolute or home-relative path.\033[0m";
        }
      }
    } else {
      std::cout << "You shouldn't have gotten here..." << std::endl;
      assert(false);
    }
  }
}