#include "JE/GRAPHIC/PARTICLE/jeEmitterType.h"
#include "JE/GRAPHIC/PARTICLE/jeParticle.h"
#include "JE/GRAPHIC/jeEmitter.h"
#include <iostream>

namespace JE{ namespace GRAPHICS{

Emitter::Emitter(int max_particles){
	this->max_particles = max_particles;
}

Emitter::~Emitter(){
	
}

EmitterType& Emitter::newType(const std::string& name){
	return this->type_m[name];
}

EmitterType& Emitter::getType(const std::string& name){
	return this->type_m.at(name);
}

void Emitter::create(const std::string& name, int ammount, float offset_x, float offset_y, float offset_angle){
	for (int i = 0; i < ammount; ++i){
		if (this->emptyslot_v.size() > 0){
			auto position = this->emptyslot_v.back();
			Particle& part = this->particle_v.at(position);
			EmitterType& emitter_type = this->getType(name);
			this->active_v.push_back(position);
			this->emptyslot_v.pop_back();
			
			float speedx, speedy;
			emitter_type.getRandomSpeedXY(speedx, speedy);
			part.setSpeed(speedx, speedy);
			part.setPosition(emitter_type.getRandomPositionX() + offset_x, emitter_type.getRandomPositionY() + offset_y);
			part.setAcceleration(emitter_type.getRandomAccelX(), emitter_type.getRandomAccelY());
			part.setLife(emitter_type.getRandomLife());
			part.setSlow(emitter_type.getRandomSlow());
			part.setTypeName(name);
			//std::cout << "Recycling!" << std::endl;
			//std::cout << "There are " << this->emptyslot_v.size() << " slots left." << std::endl; 
		
		} else if ((int)this->particle_v.size() < this->max_particles){
			EmitterType& emitter_type = this->getType(name);
			this->particle_v.emplace_back(
				emitter_type.getRandomPositionX() + offset_x, 
				emitter_type.getRandomPositionY() + offset_y, 
				emitter_type.getRandomLife()
			);
			Particle& part = this->particle_v.back();
			this->active_v.push_back(this->particle_v.size()-1);
			
			float speedx, speedy;
			emitter_type.getRandomSpeedXY(speedx, speedy);
			part.setSpeed(speedx, speedy);
			part.setAcceleration(emitter_type.getRandomAccelX(), emitter_type.getRandomAccelY());
			part.setSlow(emitter_type.getRandomSlow());
			part.setTypeName(name);
			//std::cout << "Creating new!" << std::endl;
			
		} else {
			//Nowhere to put in a new particle; failure.
			return;
		}
		//std::cout << "There are now " << this->active_v.size() << " active particles" << std::endl;
	}
}

void Emitter::update(float dt){
	std::vector<std::vector<Particle>::size_type>::iterator i = this->active_v.begin();
	while (i != this->active_v.end()){
		Particle& part = this->particle_v.at(*i);
		part.update(dt);
		if (part.isDead()){
			this->emptyslot_v.push_back(*i);
			i = this->active_v.erase(i);
			//std::cout << "Removed particle." << std::endl;
			//std::cout << "There are now " << this->emptyslot_v.size() << " slots left." << std::endl; 
			//std::cout << "There are now " << this->active_v.size() << " active particles" << std::endl;
		} else {
			++i;
		}
	}
}

void Emitter::draw(){
	for (auto& index : this->active_v){
		Particle& part = this->particle_v[index];
		EmitterType& etype = this->type_m[part.getTypeName()];
		etype.draw(part);
	}
}

}}