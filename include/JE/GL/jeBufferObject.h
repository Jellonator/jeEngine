#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <vector>

namespace JE{namespace GL{

template <class Type>
class BufferObject{
public:
	BufferObject(GLenum type);
	BufferObject(GLenum type, const std::vector<Type>& data);
	~BufferObject();
	
	void setData(const std::vector<Type>& data);
	void appendData(const std::vector<Type>& data);
	void prependData(const std::vector<Type>& data);
	
	void bind();
	
	void loadLocal();
	void pushLocal();
	
	GLuint getBufferSize() const;
	GLuint getLocalSize() const;
	
private:
	std::vector<Type> local_vec;
	bool is_local_loaded;
	GLuint buffer_id;
	GLuint buffer_size;
	GLenum buffer_type;
	GLenum buffer_usage;
};

template <class Type>
BufferObject<Type>::BufferObject(GLenum type){
	glGenBuffers(1, &this->buffer_id);
	this->buffer_type = type;
	this->buffer_usage = GL_STATIC_DRAW;
	this->buffer_size = 0;
	this->is_local_loaded = true;
}

template <class Type>
BufferObject<Type>::BufferObject(GLenum type, const std::vector<Type>& data){
	glGenBuffers(1, &this->buffer_id);
	this->buffer_type = type;
	this->buffer_usage = GL_STATIC_DRAW;
	this->buffer_size = 0;
	this->is_local_loaded = true;
	
	this->setData(data);
}

template <class Type>
BufferObject<Type>::~BufferObject(){
	glDeleteBuffers(1, &this->buffer_id);
}

template <class Type>
void BufferObject<Type>::bind(){
	glBindBuffer(this->buffer_type, this->buffer_id);
}

template <class Type>
void BufferObject<Type>::pushLocal(){
	if (this->is_local_loaded){
		this->bind();
		this->buffer_size = this->local_vec.size();
		glBufferData(this->buffer_type, this->buffer_size * sizeof(Type), this->local_vec.data(), this->buffer_usage);
		this->local_vec.clear();
	}
	this->is_local_loaded = false;
}

template <class Type>
void BufferObject<Type>::loadLocal(){
	if (!this->is_local_loaded){
		this->bind();
		this->local_vec.resize(this->buffer_size, 0);
		glGetBufferSubData(this->buffer_type, 0, this->buffer_size * sizeof(Type), &this->local_vec[0]);
	}
	this->is_local_loaded = true;
}

template <class Type>
void BufferObject<Type>::setData(const std::vector<Type>& data){
	//Pretend local is loaded, even though it really isn't.
	this->is_local_loaded = true;
	this->local_vec = data;
}

template <class Type>
void BufferObject<Type>::appendData(const std::vector<Type>& data){
	this->loadLocal();
	this->local_vec.insert(this->local_vec.end(), data.begin(), data.end());
}

template <class Type>
void BufferObject<Type>::prependData(const std::vector<Type>& data){
	this->loadLocal();
	this->local_vec.insert(this->local_vec.begin(), data.begin(), data.end());
}

template <class Type>
GLuint BufferObject<Type>::getLocalSize() const {
	if (this->is_local_loaded){
		return this->local_vec.size();
	} else {
		return this->buffer_size;
	}
}

template <class Type>
GLuint BufferObject<Type>::getBufferSize() const {
	return this->buffer_size;
}

}}