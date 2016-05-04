#include "JE/MOVEMENT/jeObject.h"

namespace JE{namespace MOVEMENT{

Object::Object(float x, float y) 
: state(IN_AIR)
, ground()
, ground_position(0)
, position(x, y) {}

Object::Object(std::shared_ptr<int>& ground, float position) 
: state(ON_GROUND)
, ground(ground)
, ground_position(position)
, position(0, 0) {
	///TODO: set position to actual position on ground
}

Object::~Object() {}

}}