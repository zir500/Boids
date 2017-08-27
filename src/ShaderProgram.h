#ifndef SHADER_PROGRAM_H__
#define SHADER_PROGRAM_H__

#include <string>
#include <stdexcept>
#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>



class ShaderProgram{
	int program;

	public:
		ShaderProgram(std::string, std::string);
		~ShaderProgram();
		void use();
		void set(const char*, glm::mat4);	

	private:
		static int isCompilationSuccessfull(int);
		static std::string getInfoLog(int);
		static std::string loadShader(std::string filePath);
};

#endif //SHADER_PROGRAM_H__
