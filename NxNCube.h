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
public:
  inline static const std::string white = "\033[1;38;2;255;255;255;49mW\033[0m";
  inline static const std::string orange = "\033[1;38;2;255;165;0;49mO\033[0m";
  inline static const std::string green = "\033[1;38;2;0;255;0;49mG\033[0m";
  inline static const std::string red = "\033[1;38;2;255;0;0;49mR\033[0m";
  inline static const std::string blue = "\033[1;38;2;0;0;255;49mB\033[0m";
  inline static const std::string yellow = "\033[1;38;2;255;255;0;49mY\033[0m";

  NxNCube(int layers);
  void draw() const;
  void turn_cw(std::string side, int depth);
  void turn_ccw(std::string side, int depth);
  void printColors();
};

#endif