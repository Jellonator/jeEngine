#pragma once

#include <vector>
#include <tuple>
#include "../jePoint.h"

namespace JE{namespace MOVEMENT{

class Ground {
public:
	Ground(const std::vector<JE::Point>& points, bool is_loop = false);
	Ground(const std::vector<std::pair<float, float>>& points, bool is_loop = false);
	~Ground();
	
	const JE::Point& getPoint(int index);
	JE::Point getPointf(float index);
	bool isLoop() const;
private:
	std::vector<JE::Point> points;
	bool is_loop;
};

}}