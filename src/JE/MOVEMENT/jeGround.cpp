#include "JE/MOVEMENT/jeGround.h"
#include <cmath>

namespace JE{namespace MOVEMENT{

Ground::Ground(const std::vector<JE::Point>& points, bool is_loop)
: points(points)
, is_loop(is_loop) {}

Ground::Ground(const std::vector<std::pair<float, float>>& points, bool is_loop)
: points([points]() -> std::vector<JE::Point> {
	std::vector<JE::Point> ret;
	ret.reserve(ret.size());
	for (auto& p : points){
		ret.push_back(JE::Point(p.first, p.second));
	}
	return ret;
}())
, is_loop(is_loop) {}

Ground::~Ground() {}

const JE::Point& Ground::getPoint(int index) {
	if (index < 0) return this->points.back();
	if (index >= (int)this->points.size()) return this->points.front();
	return this->points.at(index);
}

JE::Point Ground::getPointf(float index) {
	float integral;
	float fraction = std::modf(index, &integral);
	int id = integral;
	const JE::Point& start = this->getPoint(id);
	const JE::Point& end = this->getPoint(id + 1);
	return start.lerp(end, fraction);
}

bool Ground::isLoop() const {
	return this->is_loop;
}

}}