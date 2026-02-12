# Makefile

CXX ?= g++

CXXFLAGS ?= --std=c++17 -Wall -Werror -pedantic -g -Wno-sign-compare -Wno-comment --std=c++17 -Wall -Werror -pedantic -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG

INCLUDE = inc

all: build/nxncube

debug: build/nxncube_d

build/util_d.o: src/util.cpp
	$(CXX) -c $(CXXFLAGS) $^ -I $(INCLUDE) -o $@

build/NxNCube_d.o: src/NxNCube.cpp
	$(CXX) -c $(CXXFLAGS) $^ -I $(INCLUDE) -o $@

build/driver_d.o: src/driver.cpp
	$(CXX) -c $(CXXFLAGS) $^ -I $(INCLUDE) -o $@

build/nxncube_d: build/util_d.o build/NxNCube_d.o build/driver_d.o
	$(CXX) $(CXXFLAGS) $^ -o build/nxncube_d

build/util.o: src/util.cpp
	$(CXX) -c $^ -I $(INCLUDE) -o $@

build/NxNCube.o: src/NxNCube.cpp
	$(CXX) -c $^ -I $(INCLUDE) -o $@

build/driver.o: src/driver.cpp
	$(CXX) -c $^ -I $(INCLUDE) -o $@

build/nxncube: build/util.o build/NxNCube.o build/driver.o
	$(CXX) $^ -o build/nxncube

.SUFFIXES:

clean:
	rm -rvf build/*.exe build/*.o build/nxncube build/nxncube_d