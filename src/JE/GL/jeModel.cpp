#include "JE/GL/jeModel.h"

#include <iostream>

namespace JE{ namespace GL{

GLuint generateOneVertexArrayBuffer(){
	GLuint val;
	glGenVertexArrays(1, &val);
	return val;
}

ModelAttribute::ModelAttribute() :
 buffer_data(GL_ARRAY_BUFFER){
	this->shader_reference_int = 0;
	this->stride = 0;
	this->is_normalized = false;
	this->num_elements = 1;
}

ModelAttribute::ModelAttribute(const std::vector<GLfloat>& data) :
 buffer_data(GL_ARRAY_BUFFER, data){
	this->shader_reference_int = 0;
	this->stride = 0;
	this->is_normalized = false;
	this->num_elements = 1;
}

ModelAttribute::~ModelAttribute(){
	glDisableVertexAttribArray(this->shader_reference_int);
}

void ModelAttribute::setSize(int value){
	this->num_elements = value;
}

void ModelAttribute::setNormalized(bool value){
	this->is_normalized = value;
}

void ModelAttribute::setStride(int value){
	this->stride = value;
}

void ModelAttribute::setShaderReference(const std::string& ref){
	this->shader_reference_string = ref;
}

void ModelAttribute::useShader(Shader& shader){
	this->shader_reference_int = shader.getAttributePosition(this->shader_reference_string);
	this->buffer_data.bind();
	this->buffer_data.pushLocal();
	
	glEnableVertexAttribArray(this->shader_reference_int);
	glVertexAttribPointer(
		this->shader_reference_int,
		this->num_elements,
		GL_FLOAT,
		this->is_normalized ? GL_TRUE : GL_FALSE,
		this->stride,
		nullptr
	);
}

Model::Model() :
 vao(generateOneVertexArrayBuffer()),
 buffer_elements(GL_ELEMENT_ARRAY_BUFFER),
 buffer_points() {
	this->buffer_points.setSize(3);
	this->draw_mode = GL_TRIANGLES;
	this->useShader(JE::GL::getDefaultShader());
	this->need_update_vertex_attrib = true;
}

Model::Model(const std::vector<GLfloat>& points, const std::vector<GLuint>& elements) : 
 vao(generateOneVertexArrayBuffer()),
 buffer_elements(GL_ELEMENT_ARRAY_BUFFER, elements),
 buffer_points(points) {
	this->buffer_points.setSize(3);
	this->draw_mode = GL_TRIANGLES;
	this->useShader(JE::GL::getDefaultShader());
	this->need_update_vertex_attrib = true;
}

Model::~Model(){
	glDeleteVertexArrays(1, &this->vao);
}

void Model::useShader(Shader& shader){
	// Only update buffers if the new shader is different or new buffers have
	// been added since last time.
	if (shader.getProgramPtr() != this->shader_reference 
	 || this->need_update_vertex_attrib){
		this->bind();
		
		this->buffer_points.useShader(shader);
		for (auto& buffer : this->buffer_extra_map){
			buffer.second.useShader(shader);
		}
		
		this->shader_reference = shader.getProgramPtr();
		this->need_update_vertex_attrib = false;
	}
}

void Model::setDrawMode(GLenum mode){
	this->draw_mode = mode;
}

void Model::draw(){
	if (this->shader_reference == nullptr) return;
	
	this->bind();
	this->buffer_elements.pushLocal();
	glUseProgram(*this->shader_reference);
	
	glDrawElements(
		this->draw_mode,
		this->buffer_elements.getBufferSize(),
		GL_UNSIGNED_INT,
		0
	);
}

void Model::addAttribute(const std::string& name, const std::string& shader_reference){
	this->buffer_extra_map[name].shader_reference_string = shader_reference;
	this->need_update_vertex_attrib = true;
}

void Model::addAttribute(const std::string& name, const std::string& shader_reference, const std::vector<GLfloat>& data){
	this->buffer_extra_map[name].shader_reference_string = shader_reference;
	this->buffer_extra_map[name].buffer_data.setData(data);
	this->need_update_vertex_attrib = true;
}

ModelAttribute& Model::getAttribute(const std::string& name){
	return this->buffer_extra_map[name];
}

ModelAttribute& Model::getPointAttribute(){
	return this->buffer_points;
}

void Model::bind(){
	glBindVertexArray(this->vao);
	this->buffer_elements.bind();
}

Model* default_model = nullptr;
Model* default_outline_model = nullptr;

Model& getDefaultModel(){
	if (default_model == nullptr){
		default_model = new Model(
			{
				0.0f, 0.0f, 0.0f, // top left
				1.0f, 0.0f, 0.0f, // top right
				1.0f, 1.0f, 0.0f, // bottom right
				0.0f, 1.0f, 0.0f, // bottom left
			},{
				0, 1, 3, // top left
				2, 1, 3, // bottom right
			}
		);
		default_model->getPointAttribute().setShaderReference("in_Position");
		default_model->useShader(JE::GL::getDefaultShader());
	}
	
	return *default_model;
}

Model& getDefaultOutlineModel(){
	if (default_outline_model == nullptr){
		default_outline_model = new Model(
			{
				0.0f, 0.0f, 0.0f, // top left
				1.0f, 0.0f, 0.0f, // top right
				1.0f, 1.0f, 0.0f, // bottom right
				0.0f, 1.0f, 0.0f, // bottom left
			},{
				0, 1, 2, 3
			}
		);
		default_outline_model->setDrawMode(GL_LINE_LOOP);
		default_outline_model->getPointAttribute().setShaderReference("in_Position");
		default_outline_model->useShader(JE::GL::getDefaultShader());
	}
	
	return *default_outline_model;
}

}}