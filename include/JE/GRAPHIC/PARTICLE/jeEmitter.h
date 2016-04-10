#pragma once
#include <vector>
#include <string>
#include <map>

namespace JE{ namespace GRAPHICS{

class Particle;
class Emitter;
class EmitterType;

class Emitter {
public:
	Emitter(int max_particles = 2500);
	virtual ~Emitter();
	
	void create(const std::string& name, int ammount = 1, float offset_x = 0, float offset_y = 0, float offset_angle = 0);
	void update(float dt);
	void draw(const JE::GRAPHICS::Camera& camera);
	
	EmitterType& newType(const std::string& name);
	EmitterType& getType(const std::string& name);
	bool hasType(const std::string& name) const;
	
private:
	std::map<std::string, EmitterType> type_m;
	int max_particles;
	int current_count;
};

}}