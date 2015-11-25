#pragma once

#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat2x2.hpp>
#include <glm/mat2x3.hpp>
#include <glm/mat2x4.hpp>
#include <glm/mat3x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat3x4.hpp>
#include <glm/mat4x2.hpp>
#include <glm/mat4x3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
 
#include <map>
#include <string>
#include <vector>
#include <tuple>
#include <memory>

namespace JE{ namespace GL{

class Shader{
public:
	Shader();
	Shader(std::vector<std::pair<std::string, GLenum>> shader_list, bool is_file);
	~Shader();
	
	GLuint addShaderFromFile(const std::string& name, const std::string& file_name, GLenum shader_type);
	GLuint addShaderFromData(const std::string& name, const std::string& source, GLenum shader_type);
	
	GLuint getShader(const std::string& name);
	GLuint getProgram();
	std::shared_ptr<GLuint>& getProgramPtr();
	
	bool linkShaders();
	void use();
	
	GLint getUniformPosition(const std::string& uniform);
	GLenum getUniformType(const std::string& uniform);
	
	GLint getAttributePosition(const std::string& attribute);
	GLenum getAttributeType(const std::string& attribute);
	
	template<class Type> 
	bool setUniform(const std::string& uniform, Type value);
	template<class Type> 
	bool setUniform(const std::string& uniform, Type value1, Type value2);
	template<class Type> 
	bool setUniform(const std::string& uniform, Type value1, Type value2, Type value3);
	template<class Type> 
	bool setUniform(const std::string& uniform, Type value1, Type value2, Type value3, Type value4);
	
	bool setUniformVec(const std::string& uniform, const glm::vec2& vec);
	bool setUniformVec(const std::string& uniform, const glm::vec3& vec);
	bool setUniformVec(const std::string& uniform, const glm::vec4& vec);
	
	bool setUniformMat(const std::string& uniform, const glm::mat2x2& mat);
	bool setUniformMat(const std::string& uniform, const glm::mat2x3& mat);
	bool setUniformMat(const std::string& uniform, const glm::mat2x4& mat);
	bool setUniformMat(const std::string& uniform, const glm::mat3x2& mat);
	bool setUniformMat(const std::string& uniform, const glm::mat3x3& mat);
	bool setUniformMat(const std::string& uniform, const glm::mat3x4& mat);
	bool setUniformMat(const std::string& uniform, const glm::mat4x2& mat);
	bool setUniformMat(const std::string& uniform, const glm::mat4x3& mat);
	bool setUniformMat(const std::string& uniform, const glm::mat4x4& mat);
	
private:
	std::map<std::string, GLuint> shaders_map;
	std::vector<std::shared_ptr<GLuint>> shaders_vec;
	std::shared_ptr<GLuint> program_id;
	
	void _logError(GLuint shader_id, const std::string& error_name);
	bool _addShader(const std::string& name, const std::string& source, GLenum shader_type, GLuint* shader_ret);
};

Shader& getDefaultOutlineShader();
Shader& getDefaultShader();
Shader& getDefaultImageShader();

template <class Type>
bool Shader::setUniform(const std::string& uniform, Type value){
	GLenum uniform_type = this->getUniformType(uniform);
	GLint uniform_pos = this->getUniformPosition(uniform);
	if (uniform_pos < 0) return false;
	
	switch (uniform_type){
		case GL_FLOAT:
			glUniform1f(uniform_pos, value);
		break;
		case GL_INT:
			glUniform1i(uniform_pos, value);
		break;
		case GL_DOUBLE:
			glUniform1d(uniform_pos, value);
		break;
		case GL_UNSIGNED_INT:
			glUniform1ui(uniform_pos, value);
		break;
		default:
			return false;
		break;
	}
	
	return true;
}

template <class Type>
bool Shader::setUniform(const std::string& uniform, Type value1, Type value2){
	GLenum uniform_type = this->getUniformType(uniform);
	GLint uniform_pos = this->getUniformPosition(uniform);
	if (uniform_pos < 0) return false;
	
	switch (uniform_type){
		case GL_FLOAT_VEC2:
			glUniform2f(uniform_pos, value1, value2);
		break;
		case GL_INT_VEC2:
			glUniform2i(uniform_pos, value1, value2);
		break;
		case GL_DOUBLE_VEC2:
			glUniform2d(uniform_pos, value1, value2);
		break;
		case GL_UNSIGNED_INT_VEC2:
			glUniform2ui(uniform_pos, value1, value2);
		break;
		default:
			return false;
		break;
	}
	
	return true;
}

template <class Type>
bool Shader::setUniform(const std::string& uniform, Type value1, Type value2, Type value3){
	GLenum uniform_type = this->getUniformType(uniform);
	GLint uniform_pos = this->getUniformPosition(uniform);
	if (uniform_pos < 0) return false;
	
	switch (uniform_type){
		case GL_FLOAT_VEC3:
			glUniform3f(uniform_pos, value1, value2, value3);
		break;
		case GL_INT_VEC3:
			glUniform3i(uniform_pos, value1, value2, value3);
		break;
		case GL_DOUBLE_VEC3:
			glUniform3d(uniform_pos, value1, value2, value3);
		break;
		case GL_UNSIGNED_INT_VEC3:
			glUniform3ui(uniform_pos, value1, value2, value3);
		break;
		default:
			return false;
		break;
	}
	
	return true;
}

template <class Type>
bool Shader::setUniform(const std::string& uniform, Type value1, Type value2, Type value3, Type value4){
	GLenum uniform_type = this->getUniformType(uniform);
	GLint uniform_pos = this->getUniformPosition(uniform);
	if (uniform_pos < 0) return false;
	
	switch (uniform_type){
		case GL_FLOAT_VEC4:
			glUniform4f(uniform_pos, value1, value2, value3, value4);
		break;
		case GL_INT_VEC4:
			glUniform4i(uniform_pos, value1, value2, value3, value4);
		break;
		case GL_DOUBLE_VEC4:
			glUniform4d(uniform_pos, value1, value2, value3, value4);
		break;
		case GL_UNSIGNED_INT_VEC4:
			glUniform4ui(uniform_pos, value1, value2, value3, value4);
		break;
		default:
			return false;
		break;
	}
	
	return true;
}

}}