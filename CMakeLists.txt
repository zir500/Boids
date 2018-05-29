cmake_minimum_required(VERSION 3.1)
set (CMAKE_CXX_STANDARD 11)


project(Boids)
#set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

set(SRCS src/Simulation.cpp
		src/ShaderProgram.cpp
		src/Boid.cpp
		src/glad.c
		)

set(SHADERS src/shaders)

find_package(OpenGL)
add_subdirectory(glfw)
include_directories("glfw/include")



# The following folder will be included
include_directories("${PROJECT_SOURCE_DIR}" "${PROJECT_SOURCE_DIR}/include/" ${GLFW_INCLUDE_DIRS} "${PROJECT_SOURCE_DIR}/src/")

link_directories("$LIBRARY_OUTPUT_PATH")

# Moves the shader files into the binary directory

add_executable(boids "${SRCS}")

target_link_libraries(boids glfw)

# Move shader sources to output directory
add_custom_command(
        TARGET boids POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_SOURCE_DIR}/${SHADERS}
		${EXECUTABLE_OUTPUT_PATH}/shaders
)

install(TARGETS boids DESTINATION bin)
