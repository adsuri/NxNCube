# Makefile

CXX ?= g++

CXXFLAGS ?= --std=c++17 -Wall -Werror -pedantic -g -Wno-sign-compare -Wno-comment --std=c++17 -Wall -Werror -pedantic -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG

INCLUDE = inc

make all: build/nxncube

# build/nxncube: src/driver.cpp src/NxNCube.cpp src/util.cpp
# 	$(CXX) $(CXXFLAGS) $^ -I $(INCLUDE) -o $@

build/util.o: src/util.cpp
	$(CXX) -c $(CXXFLAGS) $^ -I $(INCLUDE) -o $@

build/NxNCube.o: src/NxNCube.cpp
	$(CXX) -c $(CXXFLAGS) $^ -I $(INCLUDE) -o $@

build/driver.o: src/driver.cpp
	$(CXX) -c $(CXXFLAGS) $^ -I $(INCLUDE) -o $@

build/nxncube: build/util.o build/NxNCube.o build/driver.o
	$(CXX) $(CXXFLAGS) $^ -o build/nxncube

.SUFFIXES:

clean:
	rm -rvf *.exe *.o build/nxncube