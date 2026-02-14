# Makefile

CXX ?= g++

CXXFLAGS ?= -Wall -Werror -pedantic -g -Wno-sign-compare -Wno-comment --std=c++17 -Wall -Werror -pedantic -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG

INCLUDE = include

all: build/nxncube

debug: debug/nxncube

debug/util.o: src/util.cpp
	$(CXX) -c $(CXXFLAGS) $^ -I $(INCLUDE) -o $@ --std=c++17

debug/NxNCube.o: src/NxNCube.cpp
	$(CXX) -c $(CXXFLAGS) $^ -I $(INCLUDE) -o $@ --std=c++17

debug/driver.o: src/driver.cpp
	$(CXX) -c $(CXXFLAGS) $^ -I $(INCLUDE) -o $@ --std=c++17

debug/nxncube: debug/util.o debug/NxNCube.o debug/driver.o
	$(CXX) $(CXXFLAGS) $^ -o debug/nxncube --std=c++17

build/util.o: src/util.cpp
	$(CXX) -c $^ -I $(INCLUDE) -o $@ --std=c++17

build/NxNCube.o: src/NxNCube.cpp
	$(CXX) -c $^ -I $(INCLUDE) -o $@ --std=c++17

build/driver.o: src/driver.cpp
	$(CXX) -c $^ -I $(INCLUDE) -o $@ --std=c++17

build/nxncube: build/util.o build/NxNCube.o build/driver.o
	$(CXX) $^ -o build/nxncube --std=c++17

.SUFFIXES:

clean:
	rm -rvf build/* debug/*