#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath){
	std::string vertexShaderString = ShaderProgram::loadShader(vertexShaderPath);
	std::string fragmentShaderString = ShaderProgram::loadShader(fragmentShaderPath);

	const char* vertexShaderSource = vertexShaderString.c_str();
	const char* fragmentShaderSource = fragmentShaderString.c_str(); 

	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);	
	this->program = glCreateProgram();

	//Vertex Shader	
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	if(!isCompilationSuccessfull(vertexShader)){
		throw std::runtime_error("Vertex Shader Compilation Failed:  " + getInfoLog(vertexShader));
	}

	//Fragment Shader	
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	if(!isCompilationSuccessfull(fragmentShader)){
		throw std::runtime_error("Fragment Shader Compilation Failed:  " + getInfoLog(fragmentShader));
	}

	glAttachShader(this->program, vertexShader);
	glAttachShader(this->program, fragmentShader);
	glLinkProgram(this->program);
	int success;
	glGetShaderiv(this->program, GL_LINK_STATUS, &success);
	if(!success){
		throw std::runtime_error("Shader Linking failed:  " + getInfoLog(this->program));
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

int ShaderProgram::isCompilationSuccessfull(int shader){
	int wasSuccessfull;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &wasSuccessfull);
	return wasSuccessfull;
}

std::string ShaderProgram::getInfoLog(int shader){
	char infoLog[512];
	glGetShaderInfoLog(shader, 512, NULL, infoLog);
	std::string infoLogStr(infoLog);
	return infoLogStr;
}

std::string ShaderProgram::loadShader(const char* filePath){
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);

    if(!fileStream.is_open()) {
        throw std::runtime_error("Could not read file " + std::string(filePath) + ". File does not exist.");
        return "";
    }

    std::string line = "";
    while(!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}

ShaderProgram::~ShaderProgram(){
	glDeleteProgram(this->program);
}

void ShaderProgram::use(){
	glUseProgram(this->program);	
}

void ShaderProgram::set(const char* uniform, glm::mat4 value){
	int uniformLocation = glGetUniformLocation(this->program, uniform);
	glUniform4fv(uniformLocation, 1, glm::value_ptr(value));	
}
