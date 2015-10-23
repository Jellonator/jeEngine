#pragma once
#include <string>

namespace JE{ namespace GRAPHICS{

class Particle;
class Emitter;
class EmitterType;

class Particle {
public:
	Particle(float x, float y, float life);
	virtual ~Particle();
	
	void setPosition(float x, float y);
	void setSpeed(float speed_x, float speed_y);
	void setSlow(float slow);
	void setLife(float life);
	void setAcceleration(float accel_x, float accel_y);
	
	void setTypeName(const std::string& name);
	const std::string& getTypeName() const;
	bool isDead() const;
	float getLife() const;
	float getLifePercent() const;
	float getTimeAlive() const;
	
	void update(float dt);
	float getX() const;
	float getY() const;
	
private:
	float x, y;
	float speed_x, speed_y;
	float slow;
	float life;
	float life_initial;
	float accel_x, accel_y;
	std::string type_name;
};

}}