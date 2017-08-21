#include "Boid.h"

Boid::Boid(unsigned int VAO, glm::vec3 startPosition) : currentPosition(startPosition), VAO(VAO) {
		
}


void Boid::updateVelocity(std::vector<Boid*>* allBoids, float deltaTime){
	//Calculate the velocity the bird will have as a result of the current tick
	std::vector<Boid*> neighbours = this->findNeighbours(allBoids);	

	

	nextVelocity = currentVelocity;
	nextPosition = currentPosition + (currentVelocity * deltaTime);	
}

void Boid::step(){
	currentPosition = nextPosition;
	currentVelocity = nextVelocity;
}

std::vector<Boid*> Boid::findNeighbours(std::vector<Boid*>* allBoids){
	std::vector<Boid*> neighbours;
	// TODO: This loop can be parallelised
	for(std::vector<Boid*>::iterator it = allBoids->begin(); it != allBoids->end(); ++it){
		//TODO add FOV effect
		if((glm::distance((*it)->getPosition(), this->currentPosition) <= this->visibility) 
				&& (*it != this)){//Ensure the boid doesnt consider itself in the search 
			neighbours.push_back(*it);	
		}	
	}
	return neighbours;
}

glm::vec3 Boid::findCoG(std::vector<Boid*>* flock){
	glm::vec3 average;
	//TODO This loop can be combined into the loop in findNeighbours() in an exchange 
	// of improved performance for reduced flexibility.
	for(std::vector<Boid*>::iterator it = flock->begin(); it != flock->end(); ++it){
		average += (*it)->getPosition();	
	}
	return average/(float)flock->size();
}

glm::vec3 Boid::findAverageDirection(std::vector<Boid*>* flock){
	glm::vec3 average;
	//TODO This loop can be combined into the loop in findNeighbours() in an exchange 
	// of improved performance for reduced flexibility.
	for(std::vector<Boid*>::iterator it = flock->begin(); it != flock->end(); ++it){
		average += (*it)->getVelocity();	
	}
	return glm::normalize(average/(float)flock->size());
}

glm::vec3 Boid::findAverageVectorTwo(std::vector<Boid*>* flock){
	glm::vec3 average;
	//TODO This loop can be combined into the loop in findNeighbours() in an exchange 
	// of improved performance for reduced flexibility.
	for(std::vector<Boid*>::iterator it = flock->begin(); it != flock->end(); ++it){
		average += ((*it)->getPosition() - this->currentPosition);
	}
	return glm::normalize(average/(float)flock->size());
}

glm::vec3 Boid::seperation(std::vector<Boid*>* neighbours){
	// -ve of the average vector from this boid to its neighbours
	return -findAverageVectorTwo(neighbours);
}

glm::vec3 Boid::alignment(std::vector<Boid*>* neighbours){
	//Normalised cross product of the current velocity vector and area's average velocity vectr
	return glm::vec3(0.0f, 0.0f, 0.0f);
}

glm::vec3 Boid::cohesion(std::vector<Boid*>* neighbours){
	glm::vec3 CoG = findCoG(neighbours);
	return glm::normalize(CoG - this->currentPosition);
}

glm::vec3 Boid::getPosition(){
	    return this->currentPosition;
    }

glm::vec3 Boid::getVelocity(){
	    return this->currentVelocity;
    }

unsigned int Boid::getVAO(){
	return this->VAO;
}

unsigned int Boid::createBoidVAO(){
	float triangleVertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};  
	
	unsigned int VBO;
	unsigned int VAO;


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);// attrib ID, size of each vertex's data, type, normalized, strie, first component offset. 
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
	return VAO;
}


