#include "JE/GL/jeTexture.h"
#include <iostream>

namespace JE{namespace GL{

Texture::Texture(const std::string& file_name){
	SDL_Surface* surface = IMG_Load(file_name.c_str());
	
	if (surface == nullptr) {
		std::cout << SDL_GetError() << std::endl;
		std::cout << IMG_GetError() << std::endl;
		this->texture_width = 1;
		this->texture_height = 1;
		
	} else {
		glGenTextures(1, &this->texture_id);
		glBindTexture(GL_TEXTURE_2D, this->texture_id);
		
		if (surface->format->format != SDL_PIXELFORMAT_ABGR8888){
			// Create a new surface that is guaranteed to have the correct format
			SDL_Surface* new_surface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_ABGR8888, 0);
			if (new_surface == nullptr){
				std::cout << SDL_GetError() << std::endl;
			}
			SDL_FreeSurface(surface);
			surface = new_surface;
		}
		
		int Mode = GL_RGB;
		if(surface->format->BytesPerPixel == 4) {
			Mode = GL_RGBA;
		}
		
		
		glTexImage2D(GL_TEXTURE_2D, 0, Mode, surface->w, surface->h, 0, Mode, GL_UNSIGNED_BYTE, surface->pixels);
		
		this->texture_width = surface->w;
		this->texture_height = surface->h;
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		
		SDL_FreeSurface(surface);
	}
}

Texture::Texture(int width, int height){
	glGenTextures(1, &this->texture_id);
	glBindTexture(GL_TEXTURE_2D, this->texture_id);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	
	this->texture_width = width;
	this->texture_height = height;
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

// Note that the user is in charge of freeing the surface argument
Texture::Texture(SDL_Surface* surface){
	bool do_free = false;
	
	if (surface->format->format != SDL_PIXELFORMAT_ABGR8888){
		// Create a new surface that is guaranteed to have the correct format
		SDL_Surface* new_surface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_ABGR8888, 0);
		if (new_surface == nullptr){
			std::cout << SDL_GetError() << std::endl;
		}
		surface = new_surface;
		do_free = true;
	}
	
	glGenTextures(1, &this->texture_id);
	glBindTexture(GL_TEXTURE_2D, this->texture_id);
	
	int Mode = GL_RGB;
	if(surface->format->BytesPerPixel == 4) {
		Mode = GL_RGBA;
	}
	
	glTexImage2D(GL_TEXTURE_2D, 0, Mode, surface->w, surface->h, 0, Mode, GL_UNSIGNED_BYTE, surface->pixels);
	
	this->texture_width = surface->w;
	this->texture_height = surface->h;
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	if (do_free){
		// Note that this is only called when 'surface*' is reassigned.
		SDL_FreeSurface(surface);
	}
}

Texture::~Texture(){
	glDeleteTextures(1, &this->texture_id);
}

void Texture::use() const{
	glBindTexture(GL_TEXTURE_2D, this->texture_id);
}

void Texture::disable() const{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::setFiltering(GLint min_filter, GLint max_filter){
	glBindTexture(GL_TEXTURE_2D, this->texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, max_filter);
}

GLfloat Texture::getWidth() const{
	return this->texture_width;
}

GLfloat Texture::getHeight() const{
	return this->texture_height;
}

GLuint Texture::getTexture() const{
	return this->texture_id;
}

void Texture::reset(SDL_Surface* surface){
	bool do_free = false;
	
	if (surface->format->format != SDL_PIXELFORMAT_ABGR8888){
		// Create a new surface that is guaranteed to have the correct format
		SDL_Surface* new_surface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_ABGR8888, 0);
		if (new_surface == nullptr){
			std::cout << SDL_GetError() << std::endl;
		}
		surface = new_surface;
		do_free = true;
	}
	
	int Mode = GL_RGB;
	if(surface->format->BytesPerPixel == 4) {
		Mode = GL_RGBA;
	}
	
	this->use();
	glTexImage2D(GL_TEXTURE_2D, 0, Mode, surface->w, surface->h, 0, Mode, GL_UNSIGNED_BYTE, surface->pixels);
	
	this->texture_width = surface->w;
	this->texture_height = surface->h;
	
	if (do_free){
		// Note that this is only called when 'surface*' is reassigned.
		SDL_FreeSurface(surface);
	}
}

void Texture::reset(int width, int height){
	this->use();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	
	this->texture_width = width;
	this->texture_height = height;
}

void Texture::reset(const std::string& file_name){
	SDL_Surface* surface = IMG_Load(file_name.c_str());
	
	if (surface == nullptr) {
		std::cout << SDL_GetError() << std::endl;
		std::cout << IMG_GetError() << std::endl;
		this->texture_width = 1;
		this->texture_height = 1;
		
	} else {
		this->reset(surface);
		
		SDL_FreeSurface(surface);
	}
}

}}