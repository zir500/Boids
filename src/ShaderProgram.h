#include <string>
#include <stdexcept>
#include <fstream>

#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>



class ShaderProgram{
	int program;

	public:
		ShaderProgram(const char*, const char*);
		~ShaderProgram();
		void use();
		void set(const char*, glm::mat4);	

	private:
		static int isCompilationSuccessfull(int);
		static std::string getInfoLog(int);
		static std::string loadShader(const char*);
};

