CC=g++
CXX=g++

INCLUDE_PATHS = -I/usr/local/include -I/opt/X11/include -Iinclude/
LIBRARY_PATHS = -L/usr/local/lib -I/opt/X11/lib

BUILD_DIR=bin
SRC_DIR=src

SOURCES=$(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/*.c)
OBJECTS=$(addsuffix .o,$(basename $(SOURCES)))

CFLAGS= 
CPPFLAGS= -Iinclude/
CXXFLAGS=-g -std=c++11 -Wall
LDFLAGS = $(INCLUDE_PATHS) $(LIBRARY_PATHS) -framework OpenGL -lglfw

boids: $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $(BUILD_DIR)/$@ $^ 

.PHONY: clean
clean: 
	rm $(OBJECTS) boids 

.PHONY: run
run: boids
	$(BUILD_DIR)/boids
