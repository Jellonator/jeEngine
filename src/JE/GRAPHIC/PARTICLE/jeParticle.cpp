#include "JE/GRAPHIC/PARTICLE/jeEmitterType.h"
#include "JE/GRAPHIC/PARTICLE/jeParticle.h"
#include "JE/GRAPHIC/jeEmitter.h"

namespace JE{ namespace GRAPHICS{
	
Particle::Particle(float x, float y, float life){
	this->x = x;
	this->y = y;
	this->speed_x = 0;
	this->speed_y = 0;
	this->life = life;
	this->accel_x = 0;
	this->accel_y = 0;
	this->slow = 0;
}

Particle::~Particle(){
	
}

void Particle::setPosition(float x, float y){
	this->x = x;
	this->y = y;
}

void Particle::setSpeed(float speed_x, float speed_y){
	this->speed_x = speed_x;
	this->speed_y = speed_y;
}

void Particle::setSlow(float slow){
	this->slow = slow;
}

void Particle::setLife(float life){
	this->life = life;
}

void Particle::setAcceleration(float accel_x, float accel_y){
	this->accel_x = accel_x;
	this->accel_y = accel_y;
}

void Particle::update(float dt){
	
}

void Particle::setTypeName(const std::string& name){
	this->type_name = name;
}

float Particle::getX(){
	return this->x;
}

float Particle::getY(){
	return this->y;
}

const std::string& Particle::getTypeName() const{
	return this->type_name;
}

bool Particle::isDead() const {
	return (this->life <= 0);
}

}}