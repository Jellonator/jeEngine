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
	void draw();
	
	EmitterType& newType(const std::string& name);
	EmitterType& getType(const std::string& name);
	
private:
	std::map<std::string, EmitterType> type_m;
	std::vector<Particle> particle_v;
	std::vector<std::vector<Particle>::size_type> emptyslot_v;
	std::vector<std::vector<Particle>::size_type> active_v;
	int max_particles;
};

}}