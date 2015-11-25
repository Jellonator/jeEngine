#include "JE/GRAPHIC/PARTICLE/jeEmitterType.h"
#include "JE/GRAPHIC/PARTICLE/jeParticle.h"
#include "JE/GRAPHIC/PARTICLE/jeEmitterRenderer.h"
#include "JE/GRAPHIC/jeEmitter.h"
#include "JE/GRAPHIC/jeGraphic.h"
#include "JE/UTIL/jeMath.h"

/*
namespace JE{ namespace GRAPHICS{

EmitterType::EmitterType(){
	this->x1 = 0;
	this->x2 = 0;
	this->y1 = 0;
	this->y2 = 0;
	
	this->angle1 = 0;
	this->angle2 = 0;
	
	this->speed1 = 0;
	this->speed2 = 0;
	
	this->slow1 = 0;
	this->slow2 = 0;
	
	this->life1 = 1;
	this->life2 = 1;
}

EmitterType::~EmitterType(){
	
}

//setters
void EmitterType::setPosition(float x1, float y1, float x2, float y2){
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
}

void EmitterType::setPosition(float x, float y){
	this->x1 = x;
	this->x2 = x;
	this->y1 = y;
	this->y2 = y;
}

void EmitterType::setSpeed(float speed_min, float speed_max){
	this->speed1 = speed_min;
	this->speed2 = speed_max;
}

void EmitterType::setSpeed(float speed){
	this->speed1 = speed;
	this->speed2 = speed;
}

void EmitterType::setSlow(float slow_min, float slow_max){
	this->slow1 = slow_min;
	this->slow2 = slow_max;
}

void EmitterType::setSlow(float slow){
	this->slow1 = slow;
	this->slow2 = slow;
}

void EmitterType::setLife(float life_min, float life_max){
	this->life1 = life_min;
	this->life2 = life_max;
}

void EmitterType::setLife(float life){
	this->life1 = life;
	this->life2 = life;
}

void EmitterType::setAngle(float angle_min, float angle_max){
	this->angle1 = angle_min;
	this->angle2 = angle_max;
}

void EmitterType::setAngle(float angle){
	this->angle1 = angle;
	this->angle2 = angle;
}

void EmitterType::setAcceleration(float accel_x1, float accel_y1, float accel_x2, float accel_y2){
	this->accel_x1 = accel_x1;
	this->accel_y1 = accel_y1;
	this->accel_x2 = accel_x2;
	this->accel_y2 = accel_y2;
}

void EmitterType::setAcceleration(float accel_x, float accel_y){
	this->accel_y1 = accel_y;
	this->accel_y2 = accel_y;
	this->accel_x1 = accel_x;
	this->accel_x2 = accel_x;
}

//getters
void EmitterType::getPosition(float* x1, float* y1, float* x2, float* y2) const{
	if (x1) *x1 = this->x1;
	if (x2) *x2 = this->x2;
	if (y1) *y1 = this->y1;
	if (y2) *y2 = this->y2;
}

void EmitterType::getSpeed(float* speed_min, float* speed_max) const{
	if (speed_min) *speed_min = this->speed1;
	if (speed_max) *speed_max = this->speed2;
}

void EmitterType::getSlow(float* slow_min, float* slow_max) const{
	if (slow_min) *slow_min = this->slow1;
	if (slow_max) *slow_max = this->slow2;
}

void EmitterType::getLife(float* life_min, float* life_max) const{
	if (life_min) *life_min = this->life1;
	if (life_max) *life_max = this->life2;
}

void EmitterType::getAngle(float* angle_min, float* angle_max) const{
	if (angle_min) *angle_min = this->angle1;
	if (angle_max) *angle_max = this->angle2;
}

void EmitterType::getAcceleration(float* accel_x1, float* accel_y1, float* accel_x2, float* accel_y2) const{
	if (accel_x1) *accel_x1 = this->accel_x1;
	if (accel_x2) *accel_x2 = this->accel_x2;
	if (accel_y1) *accel_y1 = this->accel_y1;
	if (accel_y2) *accel_y2 = this->accel_y2;
}

float EmitterType::getRandomPositionX() const{
	return JE::MATH::random(this->x1, this->x2);
}

float EmitterType::getRandomPositionY() const{
	return JE::MATH::random(this->y1, this->y2);
}

float EmitterType::getRandomSpeed() const{
	return JE::MATH::random(this->speed1, this->speed2);
}

float EmitterType::getRandomSlow() const{
	return JE::MATH::random(this->slow1, this->slow2);
}

float EmitterType::getRandomLife() const{
	return JE::MATH::random(this->life1, this->life2);
}

float EmitterType::getRandomAngle() const{
	return JE::MATH::random(this->angle1, this->angle2);
}

float EmitterType::getRandomAccelX() const{
	return JE::MATH::random(this->accel_x1, this->accel_x2);
}

float EmitterType::getRandomAccelY() const{
	return JE::MATH::random(this->accel_y1, this->accel_y2);
}

void EmitterType::getRandomSpeedXY(float& speed_x, float& speed_y) const{
	float angle = this->getRandomAngle(); 
	float speed = this->getRandomSpeed();
	speed_x = JE::MATH::Xangle(angle, speed);
	speed_y = JE::MATH::Yangle(angle, speed);
}

//Particle functions
void EmitterType::update(Particle& particle, float dt){
	particle.x += particle.speed_x * dt;
	particle.y += particle.speed_y * dt;
	particle.life -= dt;
}

void EmitterType::draw(Particle& particle){
	if (this->renderer){
		this->renderer->draw(*this, particle);
	}
}

}}
*/