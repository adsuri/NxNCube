# Makefile

CXX ?= g++

CXXFLAGS ?= --std=c++17 -Wall -Werror -pedantic -g -Wno-sign-compare -Wno-comment --std=c++17 -Wall -Werror -pedantic -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG

INCLUDE = inc

build/nxncube: src/driver.cpp src/NxNCube.cpp src/util.cpp
	$(CXX) $(CXXFLAGS) $^ -I $(INCLUDE) -o $@

.SUFFIXES:

clean:
	rm -rvf *.exe build/nxncube