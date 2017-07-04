#include "simulation.h"


void Simulation::Init(int windowWidth, int windowHeight){
	//Setup a window.
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	this->window = glfwCreateWindow(windowWidth, windowHeight, "Boids Simulation", NULL, NULL);
	if (this->window == NULL){
		throw std::runtime_error("Could not create GLFW window.");
		
	}
	
	glfwMakeContextCurrent(this->window);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		throw std::runtime_error("Could not initialise GLAD");
	}

	glViewport(0, 0, windowWidth, windowHeight);
	glfwSetFramebufferSizeCallback(this->window, Simulation::frameBufferSizeCallback);
}

void Simulation::Render(ShaderProgram* shaderProgram){
	glClearColor(0.2f, 0.3, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	shaderProgram->use()
	glBindVertexArray();

	for(const Boid b : this->boids){
		shaderProgram.set();
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}


	glfwSwapBuffers(this->window);
	glfwPollEvents();
}

void Simulation::Tick(){
	
}

Simulation::~Simulation(){
	glfwTerminate();
}

void Simulation::frameBufferSizeCallback(GLFWwindow* window, int width, int height){
	glViewport(0, 0, width, height);
}
