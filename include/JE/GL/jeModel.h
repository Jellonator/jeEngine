#pragma once

#include <GL/glew.h>
#include "jeShader.h"
#include "jeBufferObject.h"

#include <vector>
#include <map>
#include <string>

namespace JE{ namespace GL{

class Model;

class ModelAttribute{
public:
	friend Model;
	ModelAttribute();
	ModelAttribute(const std::vector<GLfloat>& data);
	~ModelAttribute();
	
	void useShader(Shader& shader);
	
	void setSize(int value);
	void setStride(int value);
	void setNormalized(bool value);
	
	void setShaderReference(const std::string& ref);
	
	BufferObject<GLfloat>& getBuffer();
	
private:
	int num_elements;
	int stride;
	bool is_normalized;
	
	std::string shader_reference_string;
	GLint shader_reference_int;
	BufferObject<GLfloat> buffer_data;
};

class Model{
public:
	Model();
	Model(const std::vector<GLfloat>& points, const std::vector<GLuint>& elements);
	~Model();
	
	void useShader(Shader& shader);
	void draw();
	void bind();
	
	void addAttribute(const std::string& name, const std::string& shader_reference);
	void addAttribute(const std::string& name, const std::string& shader_reference, const std::vector<GLfloat>& data);
	
	ModelAttribute& getAttribute(const std::string& name);
	ModelAttribute& getPointAttribute();
	
	void setDrawMode(GLenum mode);
	BufferObject<GLuint>& getElementBuffer();
	GLenum getDrawMode() const;
	GLuint getNumElements() const;
	
private:
	GLuint vao;
	GLenum draw_mode;
	
	BufferObject<GLuint> buffer_elements;
	
	ModelAttribute buffer_points;
	std::map<std::string, ModelAttribute> buffer_extra_map;
	
	std::shared_ptr<GLuint> shader_reference;
	
	bool need_update_vertex_attrib;
};

Model& getDefaultModel();
Model& getDefaultImageModel();
Model& getDefaultOutlineModel();
Model& getDefaultLineModel();
Model& getDefaultCircleModel();

}}