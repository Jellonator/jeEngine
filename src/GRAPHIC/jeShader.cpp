/*#include "jeShader.h"
#include "jeUtil.h"
#include <iostream>
namespace JE{namespace GRAPHICS{
Shader::Shader(std::string file, GLint type){
	this->shader = newShader(file, type);
	this->type = type;
}

Shader::~Shader(){
	//glDeleteShader(this->shader);
}
GLuint newShader(std::string file, GLint type){
	GLint compile_ok = GL_FALSE;
	GLuint shader = glCreateShader(type);
	const char* source = JE::fileOpen((char*)file.c_str()).c_str();
	std::cout << "Loading shader: " << file << " of type ";
	if (type == GL_FRAGMENT_SHADER) std::cout << "fragment";
	if (type == GL_VERTEX_SHADER) std::cout << "vertex";
	std::cout << std::endl;
	std::cout << source << std::endl;
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_ok);
	if (!compile_ok){
		fprintf(stderr, "Error in shader shader\n");
		char buffer[512];
		glGetShaderInfoLog(shader, 512, NULL, buffer);
		//std::cout << buffer << std::endl;
	}
	//std::cout << "\n" << source << std::endl;
	//return shader;
	return 0;
}
GLuint newBuffer(GLint type){
	return 0;
}
GLuint newProgram(){
	//return glCreateProgram();
	return 0;
}
};};*/
