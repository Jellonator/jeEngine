#pragma once
#include "../jeCamera.h"
#include <memory>
#include <vector>

namespace JE{ namespace GRAPHICS{

class Particle;
class Emitter;
class EmitterType;
class EmitterRenderer;

class EmitterType {
public:
	EmitterType();
	virtual ~EmitterType();
	
	//setters
	void setPosition(float x1, float y1, float x2, float y2);
	void setPosition(float x, float y);
	
	void setSpeed(float speed_min, float speed_max);
	void setSpeed(float speed);
	
	void setSlow(float slow_min, float slow_max);
	void setSlow(float slow);
	
	void setLife(float life_min, float life_max);
	void setLife(float life);
	
	void setAngle(float angle_min, float angle_max);
	void setAngle(float angle);
	
	void setAcceleration(float accel_x1, float accel_y1, float accel_x2, float accel_y2);
	void setAcceleration(float accel_x, float accel_y);
	
	//getters
	void getPosition(float* x1 = nullptr, float* y1 = nullptr, float* x2 = nullptr, float* y2 = nullptr) const;
	void getSpeed(float* speed_min = nullptr, float* speed_max = nullptr) const;
	void getSlow(float* slow_min = nullptr, float* slow_max = nullptr) const;
	void getLife(float* life_min = nullptr, float* life_max = nullptr) const;
	void getAngle(float* angle_min = nullptr, float* angle_max = nullptr) const;
	void getAcceleration(float* accel_x1 = nullptr, float* accel_y1 = nullptr, float* accel_x2 = nullptr, float* accel_y2 = nullptr) const;
	
	void getRandomSpeedXY(float& speed_x, float& speed_y) const;
	float getRandomPositionX() const;
	float getRandomPositionY() const;
	float getRandomAccelX() const;
	float getRandomAccelY() const;
	float getRandomSpeed() const;
	float getRandomSlow() const;
	float getRandomLife() const;
	float getRandomAngle() const;
	
	//Particle functions
	void create(float offset_x = 0, float offset_y = 0, float offset_angle = 0);
	int update(float dt);
	void draw(const JE::GRAPHICS::Camera& camera);
	
	template <class RType, class... Args>
	void setRenderer(Args... arguments){
		std::unique_ptr<RType> ptr(new RType(arguments...));
		this->renderer = std::move(ptr);
	}
	
private:
	float x1, y1, x2, y2;
	float angle1, angle2;
	float speed1, speed2;
	float slow1, slow2;
	float life1, life2;
	float accel_x1, accel_y1, accel_x2, accel_y2;
	std::unique_ptr<EmitterRenderer> renderer;
	std::vector<Particle> particle_v;
	std::vector<std::vector<Particle>::size_type> emptyslot_v;
	std::vector<std::vector<Particle>::size_type> active_v;
};

}}