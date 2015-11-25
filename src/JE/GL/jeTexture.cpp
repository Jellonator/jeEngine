#include "JE/GL/jeTexture.h"
#include <iostream>

namespace JE{namespace GL{

Texture::Texture(const std::string& file_name){
	SDL_Surface* surface = IMG_Load(file_name.c_str());
	
	if (surface == nullptr) {
		std::cout << SDL_GetError() << std::endl;
	} else {
		glGenTextures(1, &this->texture_id);
		glBindTexture(GL_TEXTURE_2D, this->texture_id);
		
		int Mode = GL_RGB;
		if(surface->format->BytesPerPixel == 4) {
			Mode = GL_RGBA;
		}
		
		glTexImage2D(GL_TEXTURE_2D, 0, Mode, surface->w, surface->h, 0, Mode, GL_UNSIGNED_BYTE, surface->pixels);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
}

Texture::Texture(SDL_Surface* surface){
	glGenTextures(1, &this->texture_id);
	glBindTexture(GL_TEXTURE_2D, this->texture_id);
	
	int Mode = GL_RGB;
	if(surface->format->BytesPerPixel == 4) {
		Mode = GL_RGBA;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, Mode, surface->w, surface->h, 0, Mode, GL_UNSIGNED_BYTE, surface->pixels);
}

Texture::~Texture(){
	glDeleteTextures(1, &this->texture_id);
}

void Texture::use(){
	glBindTexture(GL_TEXTURE_2D, this->texture_id);
}

void Texture::disable(){
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::setFiltering(GLint min_filter, GLint max_filter){
	glBindTexture(GL_TEXTURE_2D, this->texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, max_filter);
}

}}