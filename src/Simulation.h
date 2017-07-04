#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include "ShaderProgram.h"

class Simulation{
	GLFWwindow* window;

	public:
		Simulation();
		void Init(int, int);
		void Render(ShaderProgram*);
		void Tick();
		~Simulation();

	private:
		static void frameBufferSizeCallback(GLFWwindow*, int, int);
		std::vector<Boid> boids;

};



