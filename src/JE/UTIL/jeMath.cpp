#include "JE/UTIL/jeMath.h"
#include "JE/UTIL/jeTime.h"
#include "JE/jeMain.h"
#include <cmath>
#include <algorithm>
namespace JE{
namespace MATH{
	float RAD = 0.0174532925f;
	float DEG = 57.295779515f;
	float PI = 3.1415926535;
	float random(float a, float b){
    float random = ((float)rand())/(float)RAND_MAX;
    float d = b-a;
    float r = random * d;
    return a + r;
	}
	float distance(float x1, float y1, float x2, float y2){
		return std::sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
	}
	float squareDistance(float x1, float y1, float x2, float y2){
		return (x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1);
	}
	bool compareDistanceFast(float x1, float y1, float x2, float y2, float distance){
		//square distance is faster than distance. However, it returns the distance squared.
		//By comparing the squared distance to the square of the comparing distance, 
		//comparing distance is a little faster than using std::sqrt
		return (squareDistance(x1, y1, x2, y2) > distance*distance);
	}
	float Xangle(float angle, float distance, float x){return std::cos(RAD*angle)*distance+x;}
	float Yangle(float angle, float distance, float y){return std::sin(RAD*angle)*distance+y;}
	bool chance(float value){
		float num = JE::MATH::random(0, 100);
		if (value >= num) return true;
		return false;
	}
	bool chance(float a, float b){
		if (b == 0) return true;
		float c = a / b;
		c *= 100;
		return chance(c);
	}
	float getAngle(float x1, float y1, float x2, float y2){
		return std::atan2(y2 - y1, x2 - x1)*DEG;
	}
	float smoothTween(float pos, float to, float speed, float minSpeed){
		bool left = (pos < to);
		float distance = std::sqrt(std::abs(pos - to));
		speed *= distance;
		speed = std::max(speed, minSpeed);
		pos += speed * JE::TIME::dt * ((pos > to)? -1 : 1);
		if (!left != !(pos < to)) pos = to;
		return pos;
	}
};
}
