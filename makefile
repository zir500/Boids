CC=clang
CXX=clang++

BUILD_DIR=bin
SRC_DIR=src

SOURCES=$(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/*.c)
OBJECTS=$(addsuffix .o,$(basename $(SOURCES)))

INCLUDE_PATHS =  -Iinclude/
LIBRARY_PATHS = 

CFLAGS= 
CPPFLAGS= -Iinclude/
CXXFLAGS=-g -std=c++11 -Wall
LDFLAGS = $(INCLUDE_PATHS) $(LIBRARY_PATHS) 



ifeq ($(OS), Windows_NT)
	LDFLAGS += -lopengl32 -lglfw3 
	LIBRARY_PATHS += -Llib/
else
	UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S), Darwin)
        INCLUDE_PATHS += -I/usr/local/include -I/opt/X11/include
        LIBRARY_PATHS += -L/usr/local/lib -I/opt/X11/lib 
        LDFLAGS += -framework OpenGL -lglfw -framework Cocoa -framework IOKit -framework CoreVideo
    endif
endif



boids: $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $(BUILD_DIR)/$@ $^ 

.PHONY: clean
clean: 
	rm $(OBJECTS) boids 

.PHONY: run
run: boids
	$(BUILD_DIR)/boids
