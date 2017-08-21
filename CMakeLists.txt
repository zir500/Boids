cmake_minimum_required(VERSION 3.1)
set (CMAKE_CXX_STANDARD 11)


project(Boids)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(SRCS src/Simulation.cpp
	src/ShaderProgram.cpp
	src/Boid.cpp
	src/glad.c
	)

#find_package(OpenGL)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)


# The following folder will be included
include_directories("${PROJECT_SOURCE_DIR}" "${PROJECT_SOURCE_DIR}/include/" ${GLFW_INCLUDE_DIRS}) 

add_executable(boids "${SRCS}")

target_link_libraries(boids ${GLFW_STATIC_LIBRARIES})



install(TARGETS boids DESTINATION bin)
