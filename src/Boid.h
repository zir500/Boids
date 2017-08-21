#ifndef BOID_H__
#define BOID_H__
#include <vector>

#include <glad/glad.h>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

class Boid{
	// State Fields
	glm::vec3 currentPosition; // The position of the Boid in this Tick
	glm::vec3 nextPosition; // The velocity the boid has in this tick
	
	glm::vec3 currentVelocity; // The velocity used to calculate the position the boid will have in the next tick
	glm::vec3 nextVelocity;	// 

	// Boid Properties:
	int visibility = 10; //Radius of sight of the boid
	int foV = 160; //Field of vision in Degrees

	unsigned int VAO;

	public:
		Boid(unsigned int VAO, glm::vec3 startPosition);
		void updateVelocity(std::vector<Boid*>* allBoids, float deltaTime);
		void step();

		glm::vec3 getPosition();
		glm::vec3 getVelocity();
		unsigned int getVAO();

		static unsigned int createBoidVAO();
		static glm::vec3 findCoG(std::vector<Boid*>* flock);
		glm::vec3 findAverageVectorTwo(std::vector<Boid*>* flock);
		static glm::vec3 findAverageDirection(std::vector<Boid*>* flock);
	private:
		void updateVelocity();
		std::vector<Boid*> findNeighbours(std::vector<Boid*>* allBoids);
		glm::vec3 seperation(std::vector<Boid*>* neighbours);
		glm::vec3 alignment(std::vector<Boid*>* neighbours);
		glm::vec3 cohesion(std::vector<Boid*>* neighbours);
};
#endif
