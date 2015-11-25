#pragma once

#include <GL/glew.h>
#include <SDL2/SDL_image.h>

#include <string>

namespace JE{namespace GL{

class Texture{
public:
	Texture(const std::string& file_name);
	Texture(SDL_Surface* surface);
	~Texture();
	
	void use();
	void disable();
	
	void setFiltering(GLint min_filter, GLint max_filter);
	
private:
	GLuint texture_id;
};

}}