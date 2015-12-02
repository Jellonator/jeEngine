#include "JE/GRAPHIC/PARTICLE/jeEmitterType.h"
#include "JE/GRAPHIC/PARTICLE/jeParticle.h"
#include "JE/GRAPHIC/jeEmitter.h"
#include <iostream>

namespace JE{ namespace GRAPHICS{

Emitter::Emitter(int max_particles){
	this->max_particles = max_particles;
	this->current_count = 0;
}

Emitter::~Emitter(){
	
}

EmitterType& Emitter::newType(const std::string& name){
	return this->type_m[name];
}

EmitterType& Emitter::getType(const std::string& name){
	return this->type_m.at(name);
}

bool Emitter::hasType(const std::string& name) const{
	return (this->type_m.count(name) > 0);
}

void Emitter::create(const std::string& name, int ammount, float offset_x, float offset_y, float offset_angle){
	for (int i = 0; i < ammount; ++i){
		if (current_count >= this->max_particles) break;
		
		if (this->hasType(name)){
			this->getType(name).create(name, offset_x, offset_y, offset_angle);
			this->current_count += 1;
		}
	}
}

void Emitter::update(float dt){
	for (auto& emitter_type : this->type_m){
		int removed_count = emitter_type.second.update(dt);
		this->current_count -= removed_count;
	}
}

void Emitter::draw(const JE::GRAPHICS::Camera& camera){
	for (auto& emitter_type : this->type_m){
		emitter_type.second.draw(camera);
	}
}

}}
