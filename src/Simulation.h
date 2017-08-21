#ifndef SIMULATION_H__
#define SIMULATION_H__
#include <iostream>
#include <stdexcept>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ShaderProgram.h"
#include "Boid.h"

class Simulation{
	GLFWwindow* window;

	public:
		Simulation();
		void Init(int, int);
		void Render(ShaderProgram* shaderProgram, int windowWidth, int windowHeight);
		void Tick();
		~Simulation();

	private:
		static void frameBufferSizeCallback(GLFWwindow*, int, int);
		std::vector<Boid*> boids;
		float lastTickTime;

};


#endif
