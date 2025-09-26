#include "NxNCube.h"
#include <iostream>
#include <string>
#include <vector>

NxNCube::NxNCube(int layers)
 : n(layers),
   top(layers, std::vector<std::string>(layers, NxNCube::white)),
   left(layers, std::vector<std::string>(layers, NxNCube::orange)),
   front(layers, std::vector<std::string>(layers, NxNCube::green)),
   right(layers, std::vector<std::string>(layers, NxNCube::red)),
   back(layers, std::vector<std::string>(layers, NxNCube::blue)),
   bottom(layers, std::vector<std::string>(layers, NxNCube::yellow)) {}

void NxNCube::printColors() {
  std::cout << NxNCube::white 
    << NxNCube::orange
    << NxNCube::green
    << NxNCube::red
    << NxNCube::blue
    << NxNCube::yellow
    << std::endl;
}

void NxNCube::draw() const {
  // top face
  std::string filler((2*this->n), ' ');
  for (int i = 0; i < this->n; ++i) {
    std::cout << filler;
    for (int j = 0; j < this->n; ++j) {
      std::cout << this->top[i][j] << " ";
    }
    std::cout << std::endl;
  }

  // main "belt" of faces
  for (int i = 0; i < this->n; ++i) {
    for (int j = 0; j < this->n; ++j) {
      std::cout << this->left[i][j] << " ";
    }
    for (int j = 0; j < this->n; ++j) {
      std::cout << this->front[i][j] << " ";
    }
    for (int j = 0; j < this->n; ++j) {
      std::cout << this->right[i][j] << " ";
    }
    for (int j = 0; j < this->n; ++j) {
      std::cout << this->back[i][j] << " ";
    }
    std::cout << std::endl;
  }
  
  // bottom face
  for (int i = 0; i < this->n; ++i) {
    std::cout << filler;
    for (int j = 0; j < this->n; ++j) {
      std::cout << this->bottom[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

void NxNCube::turn_cw(std::string side, int depth) {}

void NxNCube::turn_ccw(std::string side, int depth) {}