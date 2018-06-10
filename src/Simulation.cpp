#include "Simulation.h"

void Simulation::Init(int windowWidth, int windowHeight){
	//Setup a window.
	std::cout << "Creating Window" << std::endl;

	if (!glfwInit()) {
		throw std::runtime_error("Failed ot Initialize GLFW");
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif 

	this->window = glfwCreateWindow(windowWidth, windowHeight, "Boids Simulation", NULL, NULL);
	if (this->window == NULL){
		std::cout << "Couldnt Create GLFW Window" << std::endl;
		throw std::runtime_error("Could not create GLFW window.");
	}
	
	glfwMakeContextCurrent(this->window);

	std::cout << "Initializing GLAD" << std::endl;
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		throw std::runtime_error("Could not initialise GLAD");
	}

	glViewport(0, 0, windowWidth, windowHeight);
	glfwSetFramebufferSizeCallback(this->window, Simulation::frameBufferSizeCallback);


	std::cout << "Creating Boid VAO" << std::endl;
	unsigned int BoidVAO = Boid::createBoidVAO();	

	//Generate Boids
	std::cout << "Generating Boids" << std::endl;
	for(int i=0; i<10; i++){
		this->boids.push_back(new Boid(BoidVAO, glm::vec3(10.0f, 10.0f, 0.0f)));
	}

	this->lastTickTime = glfwGetTime();
}

void Simulation::Render(ShaderProgram* shaderProgram, int windowWidth, int windowHeight){
	glClearColor(0.2f, 0.3, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	shaderProgram->use();

	glm::mat4 view;
	glm::mat4 projection;
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection = glm::perspective(glm::radians(45.0f), (float)windowWidth/(float)windowHeight, 1.0f, 100.0f);
	shaderProgram->set("view", view);
        shaderProgram->set("projection", projection);

	for(Boid* b : this->boids){
		glm::mat4 model;

		model = glm::translate(model, b->getPosition());

		
		glBindVertexArray(b->getVAO());
		shaderProgram->set("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}


	glfwSwapBuffers(this->window);
	glfwPollEvents();
}

void Simulation::Tick(){
	float currentTickTime = glfwGetTime();
	
	for(Boid* b : this->boids){
		b->updateVelocity(&(this->boids), currentTickTime-this->lastTickTime);	
	}

	for(Boid* b : this->boids){
		b->step();	
	}
	this->lastTickTime = currentTickTime;
}

Simulation::~Simulation(){
	//Free Boids
	for(const Boid* b : this->boids){
		delete b;
	}

	glfwTerminate();
}

void Simulation::frameBufferSizeCallback(GLFWwindow* window, int width, int height){
	glViewport(0, 0, width, height);
}


Simulation::Simulation(){
	std::cout << "Starting Simulation..." << std::endl;
	this->Init(500, 500);

	std::string vertexShaderSource = EXECUTABLE_PATH + "\\..\\shaders\\vertexShader.vert";
	std::string fragmentShaderSource = EXECUTABLE_PATH + "\\..\\shaders\\fragmentShader.frag";


	ShaderProgram shader(vertexShaderSource, fragmentShaderSource );
	
	 while (1){
		//this->Tick();
		this->Render(&shader, 500, 500);
	 }

}

int main(int argc, char* argv[]){
	EXECUTABLE_PATH = std::string(argv[0]);
	EXECUTABLE_PATH = EXECUTABLE_PATH.substr(0, EXECUTABLE_PATH.find_last_of("\\/"));
	Simulation simulation;
	return 0;
}
