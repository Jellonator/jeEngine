#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL2/SDL_image.h>

#include <string>

namespace JE{namespace GL{

class Texture{
public:
	Texture(const std::string& file_name);
	Texture(int width, int height);
	Texture(SDL_Surface* surface);
	~Texture();
	
	void use() const;
	void disable() const;
	
	void setFiltering(GLint min_filter, GLint max_filter);
	
	void reset(SDL_Surface* surface);
	void reset(int width, int height);
	void reset(const std::string& file_name);
	
	GLfloat getWidth() const;
	GLfloat getHeight() const;
	GLuint getTexture() const;
	
private:
	GLfloat texture_width;
	GLfloat texture_height;
	GLuint texture_id;
};

}}