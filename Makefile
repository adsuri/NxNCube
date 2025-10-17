# Makefile

CXX ?= g++

CXXFLAGS ?= --std=c++17 -Wall -Werror -pedantic -g -Wno-sign-compare -Wno-comment --std=c++17 -Wall -Werror -pedantic -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG

builds/nxncube.exe: src/game.cpp src/NxNCube.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

.SUFFIXES:

clean:
	rm -rvf *.exe *.out.txt *.out.ppm *.dSYM *.stackdump