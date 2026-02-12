#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <cassert>
#include <cmath>
#include <chrono>
#include <random>
#include <sstream>

#include "NxNCube.hpp"
#include "util.hpp"

NxNCube::NxNCube(int layers, bool blocks)
 : n(layers),
   m_top(n * n, NxNCube::color::WHITE),
   m_left(n * n, NxNCube::color::ORANGE),
   m_front(n * n, NxNCube::color::GREEN),
   m_right(n * n, NxNCube::color::RED),
   m_back(n * n, NxNCube::color::BLUE),
   m_bottom(n * n, NxNCube::color::YELLOW) {
    NxNCube::BLOCKS = blocks;
}

int NxNCube::idx(int r, int c) const noexcept {
  return (r * this->n) + c;
}

void NxNCube::rotate_cw(Face &face) {
  Face temp(this->n * this->n, NxNCube::color::RESET);

  for (int r = 0; r < this->n; ++r) {
    for (int c = 0; c < this->n; ++c) {
      temp[idx(c, this->n - 1 - r)] = face[idx(r, c)];
    }
  }
  face = temp;
}

void NxNCube::rotate_ccw(Face &face) {
  Face temp(this->n * this->n, NxNCube::color::RESET);

  for (int r = 0; r < this->n; ++r) {
    for (int c = 0; c < this->n; ++c) {
      temp[idx(this->n - 1 - c, r)] = face[idx(r, c)];
    }
  }
  face = temp;
}

void NxNCube::rotate_half_turn(Face &face) {
  Face temp(this->n * this->n, NxNCube::color::RESET);

  for (int r = 0; r < this->n; ++r) {
    for (int c = 0; c < this->n; ++c) {
      temp[idx(this->n - 1 - r, this->n - 1- c)] = face[idx(r, c)];
    }
  }
  face = temp;
}

bool NxNCube::is_valid_move(const std::string &input) const {
  return util::str_in_vector(NxNCube::VALID_MOVES, input);
}

bool NxNCube::is_valid_depth(const std::string &input) const {
  if (!util::is_positive_int(input)) {
    return false;
  }

  if (std::stoi(input) == 0) {
    return false;
  }

  if (std::stoi(input) > this->n) {
    return false;
  }

  return true;
}

void NxNCube::draw() {
  // top face
  const std::string filler(2 * this->n, ' ');
  for (int i = 0; i < this->n; ++i) {
    std::cout << filler;
    for (int j = 0; j < this->n; ++j) {
      std::cout << m_top[idx(i, j)];
    }
    std::cout << std::endl;
  }

  // main "belt" of faces
  for (int i = 0; i < this->n; ++i) {
    for (int j = 0; j < this->n; ++j) {
      std::cout << m_left[idx(i, j)];
    }
    for (int j = 0; j < this->n; ++j) {
      std::cout << m_front[idx(i, j)];
    }
    for (int j = 0; j < this->n; ++j) {
      std::cout << m_right[idx(i, j)];
    }
    for (int j = 0; j < this->n; ++j) {
      std::cout << m_back[idx(i, j)];
    }
    std::cout << std::endl;
  }
  
  // bottom face
  for (int i = 0; i < this->n; ++i) {
    std::cout << filler;
    for (int j = 0; j < this->n; ++j) {
      std::cout << m_bottom[idx(i, j)];
    }
    std::cout << std::endl;
  }
  std::cout << NxNCube::color::RESET;
  
  if (m_last_error != "") {
    std::cout << m_last_error << std::endl;
  }
}

void NxNCube::clear_console() const {
  std::cout << "\033[H\033[2J";
}

void NxNCube::clear_draw() {
  this->clear_console();
  this->draw();
}

void NxNCube::move(const std::string &move, int depth) {
  if (!this->is_valid_move(move)) {
    throw std::invalid_argument("Invalid move entered: " + move);
  }
  if (depth > this->n) {
    throw std::out_of_range("Invalid depth entered: depth must be <= this->n");
  }

  if (move == "u") {
    this->rotate_cw(m_top);

    for (int layer = 0; layer < depth; ++layer) {
      for (int c = 0; c < this->n; ++c) {
        const int index = idx(layer, c);
        NxNCube::color temp_left = m_left[index];

        m_left[index] = m_front[index];
        m_front[index] = m_right[index];
        m_right[index] = m_back[index];
        m_back[index] = temp_left;
      }
    }

    if (depth == this->n) {
      this->rotate_ccw(m_bottom);
    }
  } else if (move == "ui") {
    this->rotate_ccw(m_top);

    for (int layer = 0; layer < depth; ++layer) {
      for (int c = 0; c < this->n; ++c) {
        const int index = idx(layer, c);
        NxNCube::color temp_back = m_back[index];

        m_back[index] = m_right[index];
        m_right[index] = m_front[index];
        m_front[index] = m_left[index];
        m_left[index] = temp_back;
      }
    }

    if (depth == this->n) {
      this->rotate_cw(m_bottom);
    }
  } else if (move == "u2") {
    this->rotate_half_turn(m_top);

    for (int layer = 0; layer < depth; ++layer) {
      for (int c = 0; c < this->n; ++c) {
        const int index = idx(layer, c);
        NxNCube::color temp_left = m_left[index];
        NxNCube::color temp_back = m_back[index];

        m_left[index] = m_right[index];
        m_right[index] = temp_left;
        m_back[index] = m_front[index];
        m_front[index] = temp_back;
      }
    }

    if (depth == this->n) {
      this->rotate_half_turn(m_bottom);
    }
  } else if (move == "d") {
    this->rotate_cw(m_bottom);

    for (int layer = this->n - 1; layer >= this->n - depth; --layer) {
      for (int c = 0; c < this->n; ++c) {
        const int index = idx(layer, c);
        NxNCube::color temp_back = m_back[index];

        m_back[index] = m_right[index];
        m_right[index] = m_front[index];
        m_front[index] = m_left[index];
        m_left[index] = temp_back;
      }
    }

    if (depth == this->n) {
      this->rotate_ccw(m_top);
    }
  } else if (move == "di") {
    this->rotate_ccw(m_bottom);

    for (int layer = this->n - 1; layer >= this->n - depth; --layer) {
      for (int c = 0; c < this->n; ++c) {
        const int index = idx(layer, c);
        NxNCube::color temp_left = m_left[index];

        m_left[index] = m_front[index];
        m_front[index] = m_right[index];
        m_right[index] = m_back[index];
        m_back[index] = temp_left;
      }
    }

    if (depth == this->n) {
      this->rotate_cw(m_top);
    }
  } else if (move == "d2") {
    this->rotate_half_turn(m_bottom);

    for (int layer = this->n - 1; layer >= this->n - depth; --layer) {

      for (int c = 0; c < this->n; ++c) {
        const int index = idx(layer, c);
        NxNCube::color temp_left = m_left[index];
        NxNCube::color temp_back = m_back[index];

        m_left[index] = m_right[index];
        m_right[index] = temp_left;
        m_back[index] = m_front[index];
        m_front[index] = temp_back;
      }
    }

    if (depth == this->n) {
      this->rotate_half_turn(m_top);
    }
  } else if (move == "r") {
    this->rotate_cw(m_right);

    for (int layer = this->n - 1; layer >= this->n - depth; --layer) {
      for (int r = 0; r < this->n; ++r) {
        NxNCube::color temp_top = m_top[idx(r, layer)];

        m_top[idx(r, layer)] = m_front[idx(r, layer)];
        m_front[idx(r, layer)] = m_bottom[idx(r, layer)];
        m_bottom[idx(r, layer)] = m_back[idx(this->n - 1 - r, this->n - 1 - layer)];
        m_back[idx(this->n - 1 - r, this->n - 1 - layer)] = temp_top;
      }
    }

    if (depth == this->n) {
      this->rotate_ccw(m_left);
    }
  } else if (move == "ri") {
    this->rotate_ccw(m_right);

    for (int layer = this->n - 1; layer >= this->n - depth; --layer) {
      for (int r = 0; r < this->n; ++r) {
        NxNCube::color temp_bottom = m_bottom[idx(r, layer)];

        m_bottom[idx(r, layer)] = m_front[idx(r, layer)];
        m_front[idx(r, layer)] = m_top[idx(r, layer)];
        m_top[idx(r, layer)] = m_back[idx(this->n - 1 - r, this->n - 1 - layer)];
        m_back[idx(this->n - 1 -r, this->n - 1 - layer)] = temp_bottom;
      }
    }

    if (depth == this->n) {
      this->rotate_cw(m_left);
    }
  } else if (move == "r2") {
    this->rotate_half_turn(m_right);

    for (int layer = this->n - 1; layer >= this->n - depth; --layer) {
      for (int r = 0; r < this->n; ++r) {
        NxNCube::color temp_bottom = m_bottom[idx(r, layer)];
        NxNCube::color temp_front = m_front[idx(r, layer)];

        m_bottom[idx(r, layer)] = m_top[idx(r, layer)];
        m_top[idx(r, layer)] = temp_bottom;
        m_front[idx(r, layer)] = m_back[idx(this->n - 1 - r, this->n - 1 - layer)];
        m_back[idx(this->n - 1 - r, this->n - 1 - layer)] = temp_front;
      }
    }

    if (depth == this->n) {
      this->rotate_half_turn(m_left);
    }
  } else if (move == "f") {
    this->rotate_cw(m_front);

    for (int layer = 0; layer < depth; ++layer) {
      for (int c = 0; c < this->n; ++c) {
        NxNCube::color temp_bottom = m_bottom[idx(layer, c)];
        
        m_bottom[idx(layer, c)] = m_right[idx(this->n - 1 - c, layer)];
        m_right[idx(this->n - 1 - c, layer)] = m_top[idx(this->n - 1- layer, this->n - 1 - c)];
        m_top[idx(this->n - 1- layer, this->n - 1 - c)] = m_left[idx(c, this->n - 1 - layer)];
        m_left[idx(c, this->n - 1 - layer)] = temp_bottom;
      }
    }

    if (depth == this->n) {
      this->rotate_ccw(m_back);
    }
  } else if (move == "fi") {
    this->rotate_ccw(m_front);

    for (int layer = 0; layer < depth; ++layer) {
      for (int c = 0; c < this->n; ++c) {
        NxNCube::color temp_bottom = m_bottom[idx(layer, c)];

        m_bottom[idx(layer, c)] = m_left[idx(c, this->n - 1 - layer)];
        m_left[idx(c, this->n - 1 - layer)] = m_top[idx(this->n - 1- layer, this->n - 1 - c)];
        m_top[idx(this->n - 1- layer, this->n - 1 - c)] = m_right[idx(this->n - 1 - c, layer)];
        m_right[idx(this->n - 1 - c, layer)] = temp_bottom;
      }
    }

    if (depth == this->n) {
      this->rotate_cw(m_back);
    }
  } else if (move == "f2") {
    this->rotate_half_turn(m_front);

    for (int layer = 0; layer < depth; ++layer) {
      for (int c = 0; c < this->n; ++c) {
        NxNCube::color temp_bottom = m_bottom[idx(layer, c)];
        NxNCube::color temp_left = m_left[idx(c, this->n - 1 - layer)];

        m_bottom[idx(layer, c)] = m_top[idx(this->n - 1- layer, this->n - 1 - c)];
        m_top[idx(this->n - 1- layer, this->n - 1 - c)] = temp_bottom;
        m_left[idx(c, this->n - 1 - layer)] = m_right[idx(this->n - 1 - c, layer)];
        m_right[idx(this->n - 1 - c, layer)] = temp_left;
      }
    }

    if (depth == this->n) {
      this->rotate_half_turn(m_back);
    }
  } else if (move == "l") {
    this->rotate_cw(m_left);

    for (int layer = 0; layer < depth; ++layer) {
      for (int r = 0; r < this->n; ++r) {
        NxNCube::color temp_bottom = m_bottom[idx(r, layer)];
        
        m_bottom[idx(r, layer)] = m_front[idx(r, layer)];
        m_front[idx(r, layer)] = m_top[idx(r, layer)];
        m_top[idx(r, layer)] = m_back[idx(this->n - 1 - r, this->n - 1 - layer)];
        m_back[idx(this->n - 1 - r, this->n - 1 - layer)] = temp_bottom;
      }
    }

    if (depth == this->n) {
      this->rotate_ccw(m_right);
    }
  } else if (move == "li") {
    this->rotate_ccw(m_left);

    for (int layer = 0; layer < depth; ++layer) {
      for (int r = 0; r < this->n; ++r) {
        NxNCube::color temp_bottom = m_bottom[idx(r, layer)];

        m_bottom[idx(r, layer)] = m_back[idx(this->n - 1 - r, this->n - 1 - layer)];
        m_back[idx(this->n - 1 - r, this->n - 1 - layer)] = m_top[idx(r, layer)];
        m_top[idx(r, layer)] = m_front[idx(r, layer)];
        m_front[idx(r, layer)] = temp_bottom;
      }
    }
    
    if (depth == this->n) {
      this->rotate_cw(m_right);
    }
  } else if (move == "l2") {
    this->rotate_half_turn(m_left);

    for (int layer = 0; layer < depth; ++layer) {
      for (int r = 0; r < this->n; ++r) {
        NxNCube::color temp_bottom = m_bottom[idx(r, layer)];
        NxNCube::color temp_front = m_front[idx(r, layer)];

        m_bottom[idx(r, layer)] = m_top[idx(r, layer)];
        m_top[idx(r, layer)] = temp_bottom;
        m_front[idx(r, layer)] = m_back[idx(this->n - 1 - r, this->n - 1 - layer)];
        m_back[idx(this->n - 1 - r, this->n - 1 - layer)] = temp_front;
      }
    }
    
    if (depth == this->n) {
      this->rotate_half_turn(m_right);
    }
  } else if (move == "b") {
    this->rotate_cw(m_back);

    for (int layer = 0; layer < depth; ++layer) {
      for (int c = 0; c < this->n; ++c) {
        NxNCube::color temp_top = m_top[idx(layer, c)];

        m_top[idx(layer, c)] = m_right[idx(c, this->n - 1 - layer)];
        m_right[idx(c, this->n - 1 - layer)] = m_bottom[idx(this->n - 1 - layer, this->n - 1 - c)];
        m_bottom[idx(this->n - 1 - layer, this->n - 1 - c)] = m_left[idx(this->n - 1 - c, layer)];
        m_left[idx(this->n - 1 - c, layer)] = temp_top;
      }
    }

    if (depth == this->n) {
      this->rotate_ccw(m_front);
    }
  } else if (move == "bi") {
    this->rotate_ccw(m_back);

    for (int layer = 0; layer < depth; ++layer) {
      for (int c = 0; c < this->n; ++c) {
        NxNCube::color temp_top = m_top[idx(layer, c)];
        
        m_top[idx(layer, c)] = m_left[idx(this->n - 1 - c, layer)];
        m_left[idx(this->n - 1 - c, layer)] = m_bottom[idx(this->n - 1 - layer, this->n - 1 - c)];
        m_bottom[idx(this->n - 1 - layer, this->n - 1 - c)] = m_right[idx(c, this->n - 1 - layer)];
        m_right[idx(c, this->n - 1 - layer)] = temp_top;
      }
    }

    if (depth == this->n) {
      this->rotate_cw(m_front);
    }
  } else if (move == "b2") {
    this->rotate_half_turn(m_back);

    for (int layer = 0; layer < depth; ++layer) {
      for (int c = 0; c < this->n; ++c) {
        NxNCube::color temp_top = m_top[idx(layer, c)];
        NxNCube::color temp_left = m_left[idx(this->n - 1 - c, layer)];

        m_top[idx(layer, c)] = m_bottom[idx(this->n - 1 - layer, this->n - 1 - c)];
        m_bottom[idx(this->n - 1 - layer, this->n - 1 - c)] = temp_top;
        m_left[idx(this->n - 1 - c, layer)] = m_right[idx(c, this->n - 1 - layer)];
        m_right[idx(c, this->n - 1 - layer)] = temp_left;
      }
    }

    if (depth == this->n) {
      this->rotate_half_turn(m_front);
    }
  } else if (move == "x") {
    this->move("r", this->n);
  } else if (move == "xi") {
    this->move("ri", this->n);
  } else if (move == "x2") {
    this->move("r2", this->n);
  } else if (move == "y") {
    this->move("u", this->n);
  } else if (move == "yi") {
    this->move("ui", this->n);
  } else if (move == "y2") {
    this->move("u2", this->n);
  } else if (move == "z") {
    this->move("f", this->n);
  } else if (move == "zi") {
    this->move("fi", this->n);
  } else if (move == "z2") {
    this->move("f2", this->n);
  }

  else {
    std::cout << "You *really* shouldn't have gotten here" << std::endl;
    assert(false);
  }
}

void NxNCube::scramble() {
  const int move_count = ((this->n * this->n) / std::log10(this->n) + 15); // approximation of god's number for an nxn cube

  const std::vector<std::string> faces = {"u", "l", "f", "r", "b", "d"};
  const std::vector<std::string> dirs = {"", "i", "2"};

  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 engine(seed);
  std::uniform_int_distribution<int> face_dist(0, 5);
  std::uniform_int_distribution<int> dir_dist(0, 2);
  std::uniform_int_distribution<int> depth_dist(1, static_cast<int>(this->n / 2));

  int curr_face = face_dist(engine);
  int last_face = curr_face;

  std::string move_to_do;
  move_to_do += faces[curr_face];
  move_to_do += dirs[dir_dist(engine)];

  this->move(move_to_do, depth_dist(engine));

  for (int i = 0; i < move_count; ++i) {
    curr_face = face_dist(engine);
    while (curr_face == last_face) { curr_face = face_dist(engine); }
    last_face = curr_face;

    move_to_do = faces[curr_face];
    move_to_do += dirs[dir_dist(engine)];

    this->move(move_to_do, depth_dist(engine));
  }
}

NxNCube::SplitMove NxNCube::split_move(const std::string &str) const {
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

NxNCube::MovePair NxNCube::grab_move_pair(const std::string &str) const {
  const MovePair BAD_MOVE = {"BAD_MOVE", -1};

  if (util::str_in_vector(NxNCube::VALID_MOVES, str)) { return {str, 1}; }

  SplitMove move = this->split_move(str);

  if (!this->is_valid_depth(move.first)) { return BAD_MOVE; }
  // ex: 2-x is invalid
  if (move.second == "BAD_MOVE" || (!util::str_in_vector(NxNCube::VALID_MOVES_NO_ROTATIONS, move.second))) { return BAD_MOVE; }

  return {move.second, std::stoi(move.first)};
}

void NxNCube::play() {
  std::string input;

  while (true) {
    this->clear_draw();
    m_last_error = "";

    std::vector<std::string> args;
    if (!util::grab_input(&args)) { return; } // handles EOF

    bool is_cmd = util::str_in_vector(NxNCube::CMD_LIST, args[0]);
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
          this->move(curr_move.first, curr_move.second);
        }
      }
    } else if (args[0] == "scramble") {
      if (args.size() != 1) {
        m_last_error = "\033[1;38;2;255;0;0;49m`scramble` has no arguments\033[0m";
      } else {
        this->scramble();
      }
    } else if (args[0] == "exit") {
      return;
    } else if (args[0] == "reset") {
      m_top = Face(this->n * this->n, NxNCube::color::WHITE);
      m_left = Face(this->n * this->n, NxNCube::color::ORANGE);
      m_front = Face(this->n * this->n, NxNCube::color::GREEN);
      m_right = Face(this->n * this->n, NxNCube::color::RED);
      m_back = Face(this->n * this->n, NxNCube::color::BLUE);
      m_bottom = Face(this->n * this->n, NxNCube::color::YELLOW);
    } else {
      std::cout << "You shouldn't have gotten here..." << std::endl;
      assert(false);
    }
  }
}

std::ostream &operator<<(std::ostream &os, NxNCube::color val) {
  if (NxNCube::BLOCKS) {
    os << NxNCube::STICKERS_BLOCKS[val];
  } else {
    os << NxNCube::STICKERS_LETTERS[val];
  }
  return os;
}