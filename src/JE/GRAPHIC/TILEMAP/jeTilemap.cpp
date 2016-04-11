#include "JE/GRAPHIC/TILEMAP/jeTilemap.h"
#include "JE/GL/jeShader.h"
#include <iostream>

//this cool macro brought to you in part by https://open.gl/geometry
#define GLSL(src) "#version 330 core\n" #src

namespace JE{namespace GRAPHICS{

Tilemap::Tilemap(int width, int height) : Tilemap(0, 0, width, height) {}

Tilemap::Tilemap(float x, float y, int width, int height) : 
	JE::GRAPHICS::Graphic(x, y), width(width), height(height){
}

TileLayer& Tilemap::createLayer(const std::string& name){
	TileLayer* layer = new TileLayer(this->width, this->height);
	this->layers[name] = std::unique_ptr<TileLayer>(layer);
	return *layer;
}

TileLayer* Tilemap::getLayer(const std::string& name){
	if (this->layers.count(name) == 0) return nullptr;
	return this->layers[name].get();
}

void Tilemap::update(float dt){
	for (auto& layer : this->layers) {
		if (layer.second){
			layer.second->update(dt);
		}
	}
}

void Tilemap::drawMatrix(const glm::mat4& camera, float x, float y) const{
	glm::mat4 camera_transform = glm::translate(camera, glm::vec3(x + this->x, y + this->y, 0.0f));
	
	for (auto& layer : this->layers) {
		if (layer.second){
			layer.second->drawMatrix(camera_transform);
		}
	}
}

};};
