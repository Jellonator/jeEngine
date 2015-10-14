/*#include "jeProgram.h"
namespace JE{namespace GRAPHICS{
Program::Program(){
	this->program = glCreateProgram();
}

Program::~Program(){
	glDeleteProgram(this->program);
}

void Program::addShader(std::shared_ptr<Shader> shader){
	this->shaders.push_back(shader);
	glAttachShader(this->program, shader->shader);
}

void Program::addShader(std::string file, GLint type){
	auto shader = std::make_shared<Shader>(file, type);
	this->addShader(shader);
}

void Program::addVertexShader(std::string file){
	this->addShader(file, GL_VERTEX_SHADER);
}

void Program::addFragmentShader(std::string file){
	this->addShader(file, GL_FRAGMENT_SHADER);
}

void Program::link(){
	GLint status;
	glLinkProgram(this->program);
	glUseProgram(this->program);
	glGetProgramiv(this->program, GL_LINK_STATUS, &status);
  if (!status) {
    //std::cout << "glLinkProgram: " << this->program << std::endl;
		GLint log_length = 0;
		glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &log_length);

		char* log = (char*)malloc(log_length);
		glGetProgramInfoLog(this->program, log_length, NULL, log);
		fprintf(stderr, "%s", log);
		free(log);
  }
}
void Program::use(){
	glUseProgram(this->program);
}
};};
*/
