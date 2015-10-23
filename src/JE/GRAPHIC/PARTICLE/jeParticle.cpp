#include "JE/GRAPHIC/PARTICLE/jeEmitterType.h"
#include "JE/GRAPHIC/PARTICLE/jeParticle.h"
#include "JE/GRAPHIC/jeEmitter.h"
#include "JE/UTIL/jeMath.h"

namespace JE{ namespace GRAPHICS{
	
Particle::Particle(float x, float y, float life){
	this->x = x;
	this->y = y;
	this->speed_x = 0;
	this->speed_y = 0;
	this->life = life;
	this->life_initial = life;
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
	this->life_initial = life;
}

void Particle::setAcceleration(float accel_x, float accel_y){
	this->accel_x = accel_x;
	this->accel_y = accel_y;
}

void Particle::update(float dt){
	this->life -= dt;
	this->x += this->speed_x * dt;
	this->y += this->speed_y * dt;
	
	this->speed_x += this->accel_x * dt;
	this->speed_y += this->accel_y * dt;
	
	if (!JE::MATH::isClose(this->slow, 0.0f)){
		float angle = JE::MATH::getAngle(0, 0, this->speed_x, this->speed_y);
		float speed = JE::MATH::distance(0, 0, this->speed_x, this->speed_y);
		speed = JE::MATH::linearTween(speed, 0.0f, dt * this->slow);
		this->speed_x = JE::MATH::Xangle(angle, speed);
		this->speed_y = JE::MATH::Yangle(angle, speed);
	}
}

void Particle::setTypeName(const std::string& name){
	this->type_name = name;
}

float Particle::getX() const{
	return this->x;
}

float Particle::getY() const{
	return this->y;
}

const std::string& Particle::getTypeName() const{
	return this->type_name;
}

bool Particle::isDead() const {
	return (this->life <= 0);
}

float Particle::getLife() const {
	return this->life;
}

float Particle::getLifePercent() const {
	return this->life / this->life_initial;
}

float Particle::getTimeAlive() const {
	return this->life_initial - this->life;
}

}}