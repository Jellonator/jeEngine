#include "JE/GRAPHIC/PARTICLE/jeEmitterType.h"
#include "JE/GRAPHIC/PARTICLE/jeParticle.h"
#include "JE/GRAPHIC/jeEmitter.h"

namespace JE{ namespace GRAPHICS{

Emitter::Emitter(int max_particles){
	this->max_particles = max_particles;
}

Emitter::~Emitter(){
	
}

EmitterType& Emitter::newType(const std::string& name){
	//Maps create objects at run time; no need to initialize object.
	return this->getType(name);
}

EmitterType& Emitter::getType(const std::string& name){
	return this->type_m.at(name);
}

void Emitter::emit(const std::string& name, int ammount, float offset_x, float offset_y, float offset_angle){
	for (int i = 0; i < ammount; ++i){
		if ((int)this->particle_v.size() < this->max_particles){
			EmitterType emitter_type = this->getType(name);
			this->particle_v.emplace_back(emitter_type.getRandomPositionX(), emitter_type.getRandomPositionY(), emitter_type.getRandomLife());
			Particle& part = this->particle_v.back();
			
			float speedx, speedy;
			emitter_type.getRandomSpeedXY(speedx, speedy);
			part.setSpeed(speedx, speedy);
			part.setAcceleration(emitter_type.getRandomAccelX(), emitter_type.getRandomAccelY());
			part.setSlow(emitter_type.getRandomSlow());
			part.setTypeName(name);
			
			
		} else if (this->emptyslot_v.size() > 0){
			Particle& part = this->particle_v.at(this->emptyslot_v.back());
			EmitterType& emitter_type = this->getType(name);
			
			float speedx, speedy;
			emitter_type.getRandomSpeedXY(speedx, speedy);
			part.setSpeed(speedx, speedy);
			part.setPosition(emitter_type.getRandomPositionX(), emitter_type.getRandomPositionY());
			part.setAcceleration(emitter_type.getRandomAccelX(), emitter_type.getRandomAccelY());
			part.setLife(emitter_type.getRandomLife());
			part.setSlow(emitter_type.getRandomSlow());
			part.setTypeName(name);
			
			this->emptyslot_v.pop_back();
			
		} else {
			//Nowhere to put in a new particle; failure.
			return;
		}
	}
}

}}