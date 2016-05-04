#pragma once
#include <memory>
#include "../jePoint.h"

namespace JE{namespace MOVEMENT{

class Object {
public:
	Object(float x, float y);
	Object(std::shared_ptr<int>& ground, float position);
	~Object();
	
	//get status
	bool isInAir() const;
	bool isOnGround() const;
	
private:
	enum { ON_GROUND, IN_AIR } state; // Pretending that C++ has algebraic types
	
	// Value of enum determines which is used
	std::weak_ptr<int> ground; 
	float ground_position;
	JE::Point position;
};

}}