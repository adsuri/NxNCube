#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <cassert>

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
    k_blocks = blocks;
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

void NxNCube::draw() const {
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
}

void NxNCube::clear_console() const {
  std::cout << "\033[H\033[2J";
}

void NxNCube::clear_draw() const {
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
  }

  else {
    std::cout << "You *really* shouldn't have gotten here" << std::endl;
    assert(false);
  }
}

void NxNCube::play() {
  std::string input;

  while (true) {
    this->clear_draw();
    std::cout << "Valid moves are: {'u', 'ui', 'u2', 'l', 'li', 'l2', 'f', 'fi', 'f2', 'r', 'ri', 'r2', 'b', 'bi', 'b2', 'd', 'di', 'd2'}" << std::endl;
    std::cout << "Valid rotations are: {'x', 'xi', 'x2', 'y', 'yi', 'y2', 'z', 'zi', 'z2'}" << std::endl;

    std::cout << "What move?: ";
    if (!(std::cin >> input)) {
      std::cout << std::endl;
      return;
    }
    input = util::string_lower(input);

    if (input == "done") { return; }

    if      (input == "x")  { this->move("r",  this->n); continue; }
    else if (input == "xi") { this->move("ri", this->n); continue; }
    else if (input == "x2") { this->move("r2", this->n); continue; }
    else if (input == "y")  { this->move("u",  this->n); continue; }
    else if (input == "yi") { this->move("ui", this->n); continue; }
    else if (input == "y2") { this->move("u2", this->n); continue; }
    else if (input == "z")  { this->move("f",  this->n); continue; }
    else if (input == "zi") { this->move("fi", this->n); continue; }
    else if (input == "z2") { this->move("f2", this->n); continue; }

    bool to_continue = false;
    while (!this->is_valid_move(input)) {
      std::cout << "Invalid move, try again: ";
      if (!(std::cin >> input)) {
        std::cout << std::endl;
        return;
      }
      input = util::string_lower(input);

      if      (input == "x")  { this->move("r",  this->n); to_continue = true; }
      else if (input == "xi") { this->move("ri", this->n); to_continue = true; }
      else if (input == "x2") { this->move("r2", this->n); to_continue = true; }
      else if (input == "y")  { this->move("u",  this->n); to_continue = true; }
      else if (input == "yi") { this->move("ui", this->n); to_continue = true; }
      else if (input == "y2") { this->move("u2", this->n); to_continue = true; }
      else if (input == "z")  { this->move("f",  this->n); to_continue = true; }
      else if (input == "zi") { this->move("fi", this->n); to_continue = true; }
      else if (input == "z2") { this->move("f2", this->n); to_continue = true; }

      if (input == "done") { return; }
    }
    if (to_continue) { continue; }
    
    std::string side = input;

    std::cout << "How many layers?: " ;
    std::cin >> input;
    input = util::string_lower(input);

    if(input == "done") { return; }

    while (!this->is_valid_depth(input)) {
      std::cout << "Invalid number of layers, try again: ";
      if (!(std::cin >> input)) {
        std::cout << std::endl;
        return;
      }
      input = util::string_lower(input);

      if(input == "done") { return; }
    }
    int layers = std::stoi(input);

    this->move(side, layers);
  }
}

std::ostream &operator<<(std::ostream &os, NxNCube::color val) {
  if (NxNCube::k_blocks) {
    os << NxNCube::STICKERS_BLOCKS[val];
  } else {
    os << NxNCube::STICKERS_LETTERS[val];
  }
  return os;
}