#include "JE/GL/jeShader.h"
#include "JE/jeUtil.h"
#include <iostream>
#include <sstream>

namespace JE{namespace GL{

void program_deleter(GLuint* program){
	glDeleteProgram(*program);
}

void shader_deleter(GLuint* shader){
	glDeleteShader(*shader);
}

Shader::Shader(){
	this->program_id.reset(new GLuint(glCreateProgram()), program_deleter);
}

Shader::Shader(std::vector<std::pair<std::string, GLenum>> shader_list, bool is_file){
	this->program_id.reset(new GLuint(glCreateProgram()), program_deleter);
	
	int i = 0;
	for (auto& shader_pair : shader_list){
		if (is_file){
			const std::string& file = std::get<0>(shader_pair);
			GLenum stype = std::get<1>(shader_pair);
			this->addShaderFromFile(file, file, stype);
			
		} else {
			std::stringstream s;
			s << i;
			const std::string& data = std::get<0>(shader_pair);
			GLenum stype = std::get<1>(shader_pair);
			this->addShaderFromData(s.str(), data, stype);
			++ i;
		}
	}
	
	this->linkShaders();
}

Shader::~Shader(){
	this->shaders_vec.clear();
	this->shaders_map.clear();
}

GLuint Shader::addShaderFromFile(const std::string& name, const std::string& file_name, GLenum shader_type){
	GLuint ret = 0;
	if (!this->_addShader(name, JE::fileOpen(file_name), shader_type, &ret)){
		this->_logError(ret, "Error loading shader \"" + file_name + "\"");
	}
	return ret;
}

GLuint Shader::addShaderFromData(const std::string& name, const std::string& source, GLenum shader_type){
	GLuint ret = 0;
	if (!this->_addShader(name, source, shader_type, &ret)){
		this->_logError(ret, "Error loading shader.");
	}
	return ret;
}

bool Shader::linkShaders(){
	glLinkProgram(*this->program_id);
	
	GLint did_error = 0;
	glGetProgramiv(*this->program_id, GL_LINK_STATUS, &did_error);
	if(did_error == GL_FALSE){
		GLint log_len = 0;
		glGetProgramiv(*this->program_id, GL_INFO_LOG_LENGTH, &did_error);
		
		char infolog[log_len];
		glGetProgramInfoLog(*this->program_id,log_len,&log_len,infolog);
		
		std::cout << "The program failed to link" << std::endl;
		std::cout << "====================================" << std::endl;
		std::cout << infolog << std::endl;
		std::cout << "------------------------------------" << std::endl;
		
		return false;
	}
	return true;
}

void Shader::use(){
	glUseProgram(*this->program_id);
}

GLuint Shader::getShader(const std::string& name){
	if (this->shaders_map.count(name) == 0) return 0;
	return this->shaders_map[name];
}

GLuint Shader::getProgram(){
	return *this->program_id;
}

bool Shader::_addShader(const std::string& name, const std::string& source, GLenum shader_type, GLuint* shader_ret){
	int32_t shader_len = source.length();
	const GLchar* shader_source = (const GLchar*) source.c_str();
	
	int32_t shader_id = glCreateShader(shader_type);
	glShaderSource(shader_id, 1, &shader_source, &shader_len);
	glCompileShader(shader_id);
	*shader_ret = shader_id;
	
	GLint did_error = 0;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &did_error);
	if(did_error == GL_FALSE) {
		//glDeleteShader(shader_id);
		return false;
	}
	
	glAttachShader(*this->program_id, shader_id);
	this->shaders_vec.push_back(std::shared_ptr<GLuint>(new GLuint(shader_id), shader_deleter));
	this->shaders_map[name] = shader_id;
	
	return true;
}

void Shader::_logError(GLuint shader_id, const std::string& error_name){
	GLint log_len;
	glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_len);
	if (log_len <= 0) return;
	
	char infolog[log_len];
	
	glGetShaderInfoLog(shader_id, log_len, &log_len, infolog);
	std::cerr << error_name << std::endl;
	std::cerr << "====================================" << std::endl;
	std::cerr << infolog << std::endl;
	std::cerr << "------------------------------------" << std::endl;
}

GLint Shader::getUniformPosition(const std::string& uniform){
	return glGetUniformLocation(*this->program_id, uniform.c_str());
}

GLint Shader::getAttributePosition(const std::string& attribute){
	return glGetAttribLocation(*this->program_id, attribute.c_str());
}

GLenum Shader::getUniformType(const std::string& uniform){
	GLint pos = this->getUniformPosition(uniform);
	char name [32];
	GLint size;
	GLsizei length;
	GLenum type;
	glGetActiveUniform(*this->program_id, pos, 32, &length, &size, &type, name);
	return type;
}

std::shared_ptr<GLuint>& Shader::getProgramPtr(){
	return this->program_id;
}

bool Shader::setUniformVec(const std::string& uniform, const glm::vec2& vec){
	GLenum uniform_type = this->getUniformType(uniform);
	
	if (uniform_type == GL_FLOAT_VEC2){
		GLint uniform_pos = this->getUniformPosition(uniform);
		this->use();
		glUniform2fv(uniform_pos, 1, glm::value_ptr(vec));
		return true;
	}
	
	return false;
}

bool Shader::setUniformVec(const std::string& uniform, const glm::vec3& vec){
	GLenum uniform_type = this->getUniformType(uniform);
	
	if (uniform_type == GL_FLOAT_VEC3){
		GLint uniform_pos = this->getUniformPosition(uniform);
		this->use();
		glUniform3fv(uniform_pos, 1, glm::value_ptr(vec));
		return true;
	}
	
	return false;
}

bool Shader::setUniformVec(const std::string& uniform, const glm::vec4& vec){
	GLenum uniform_type = this->getUniformType(uniform);
	
	if (uniform_type == GL_FLOAT_VEC4){
		GLint uniform_pos = this->getUniformPosition(uniform);
		this->use();
		glUniform4fv(uniform_pos, 1, glm::value_ptr(vec));
		return true;
	}
	
	return false;
}

bool Shader::setUniformMat(const std::string& uniform, const glm::mat2x2& mat){
	GLenum uniform_type = this->getUniformType(uniform);
	
	if (uniform_type == GL_FLOAT_MAT2){
		GLint uniform_pos = this->getUniformPosition(uniform);
		this->use();
		glUniformMatrix2fv(uniform_pos, 1, GL_FALSE, glm::value_ptr(mat));
		return true;
	}
	
	return false;
}

bool Shader::setUniformMat(const std::string& uniform, const glm::mat2x3& mat){
	GLenum uniform_type = this->getUniformType(uniform);
	
	if (uniform_type == GL_FLOAT_MAT2x3){
		GLint uniform_pos = this->getUniformPosition(uniform);
		this->use();
		glUniformMatrix2x3fv(uniform_pos, 1, GL_FALSE, glm::value_ptr(mat));
		return true;
	}
	
	return false;
}

bool Shader::setUniformMat(const std::string& uniform, const glm::mat2x4& mat){
	GLenum uniform_type = this->getUniformType(uniform);
	
	if (uniform_type == GL_FLOAT_MAT2x4){
		GLint uniform_pos = this->getUniformPosition(uniform);
		this->use();
		glUniformMatrix2x4fv(uniform_pos, 1, GL_FALSE, glm::value_ptr(mat));
		return true;
	}
	
	return false;
}

bool Shader::setUniformMat(const std::string& uniform, const glm::mat3x2& mat){
	GLenum uniform_type = this->getUniformType(uniform);
	
	if (uniform_type == GL_FLOAT_MAT3x2){
		GLint uniform_pos = this->getUniformPosition(uniform);
		this->use();
		glUniformMatrix3x2fv(uniform_pos, 1, GL_FALSE, glm::value_ptr(mat));
		return true;
	}
	
	return false;
}

bool Shader::setUniformMat(const std::string& uniform, const glm::mat3x3& mat){
	GLenum uniform_type = this->getUniformType(uniform);
	
	if (uniform_type == GL_FLOAT_MAT3){
		GLint uniform_pos = this->getUniformPosition(uniform);
		this->use();
		glUniformMatrix3fv(uniform_pos, 1, GL_FALSE, glm::value_ptr(mat));
		return true;
	}
	
	return false;
}

bool Shader::setUniformMat(const std::string& uniform, const glm::mat3x4& mat){
	GLenum uniform_type = this->getUniformType(uniform);
	
	if (uniform_type == GL_FLOAT_MAT3x4){
		GLint uniform_pos = this->getUniformPosition(uniform);
		this->use();
		glUniformMatrix3x4fv(uniform_pos, 1, GL_FALSE, glm::value_ptr(mat));
		return true;
	}
	
	return false;
}

bool Shader::setUniformMat(const std::string& uniform, const glm::mat4x2& mat){
	GLenum uniform_type = this->getUniformType(uniform);
	
	if (uniform_type == GL_FLOAT_MAT4x2){
		GLint uniform_pos = this->getUniformPosition(uniform);
		this->use();
		glUniformMatrix4x2fv(uniform_pos, 1, GL_FALSE, glm::value_ptr(mat));
		return true;
	}
	
	return false;
}

bool Shader::setUniformMat(const std::string& uniform, const glm::mat4x3& mat){
	GLenum uniform_type = this->getUniformType(uniform);
	
	if (uniform_type == GL_FLOAT_MAT4x3){
		GLint uniform_pos = this->getUniformPosition(uniform);
		this->use();
		glUniformMatrix4x3fv(uniform_pos, 1, GL_FALSE, glm::value_ptr(mat));
		return true;
	}
	
	return false;
}

bool Shader::setUniformMat(const std::string& uniform, const glm::mat4x4& mat){
	GLenum uniform_type = this->getUniformType(uniform);
	
	if (uniform_type == GL_FLOAT_MAT4){
		GLint uniform_pos = this->getUniformPosition(uniform);
		this->use();
		glUniformMatrix4fv(uniform_pos, 1, GL_FALSE, glm::value_ptr(mat));
		return true;
	}
	
	return false;
}

// Textureless
std::string default_shader_vertex =
"#version 330\n"
"in vec3 in_Position;\n"
"uniform mat4 in_Transform;\n"
"void main(void) {\n"
"	gl_Position = in_Transform * vec4(in_Position, 1.0);\n"
"}\n";

std::string default_shader_fragment =
"#version 330\n"
"precision highp float;\n"
"uniform vec4 in_Color;\n"
"void main(void) {\n"
"	gl_FragColor = in_Color;\n"
"}\n";
	
// Textured
std::string default_image_shader_vertex =
"#version 330\n"
"in vec3 in_Position;\n"
"in vec2 in_Texcoord;\n"
"uniform mat4 in_Transform;\n"
"out vec2 ex_Texcoord;\n"
"void main(void) {\n"
"	gl_Position = in_Transform * vec4(in_Position, 1.0);\n"
"	ex_Texcoord = in_Texcoord;\n"
"}\n";

std::string default_image_shader_fragment =
"#version 330\n"
"precision highp float;\n"
"in vec2 ex_Texcoord;\n"
"uniform sampler2D texture;\n"
"uniform vec4 in_Color;\n"
"void main(void) {\n"
"	gl_FragColor = in_Color * texture2D(texture, ex_Texcoord);\n"
"}\n";

Shader* default_image_shader = nullptr;
Shader* default_shader = nullptr;

Shader& getDefaultShader(){
	if (default_shader == nullptr){
		std::cout << "Generating shader" << std::endl;
		default_shader = new Shader(
			{
				{default_shader_vertex, GL_VERTEX_SHADER},
				{default_shader_fragment, GL_FRAGMENT_SHADER},
			}, 
			false
		);
		if (!default_shader->linkShaders()){
			std::cout << "Failed to link shaders!" << std::endl;
		}
		if (!default_shader->setUniform("in_Color", 1.0, 1.0, 1.0, 1.0)){
			std::cout << "Failed to set Color" << std::endl;
		}
		if (!default_shader->setUniformMat("in_Transform", glm::mat4x4())){
			std::cout << "Failed to set Transform" << std::endl;
		}
	}
	
	return *default_shader;
}

Shader& getDefaultImageShader(){
	if (default_image_shader == nullptr){
		default_image_shader = new Shader(
			{
				{default_image_shader_vertex, GL_VERTEX_SHADER},
				{default_image_shader_fragment, GL_FRAGMENT_SHADER},
			}, 
			false
		);
		default_image_shader->linkShaders();
		default_image_shader->setUniform("in_Color", 1.0, 1.0, 1.0, 1.0);
		default_image_shader->setUniformMat("in_Transform", glm::mat4x4());
	}
	
	return *default_image_shader;
}

}}