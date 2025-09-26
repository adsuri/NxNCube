# Makefile

CXX ?= g++

CXXFLAGS ?= --std=c++17 -Wall -Werror -pedantic -g -Wno-sign-compare -Wno-comment --std=c++17 -Wall -Werror -pedantic -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG

game.exe: game.cpp NxNCube.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -rvf *.exe *.out.txt *.out.ppm *.dSYM *.stackdump