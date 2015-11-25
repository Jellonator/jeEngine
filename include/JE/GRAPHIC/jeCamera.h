#pragma once
#include "../jePoint.h"
#include "../jeMain.h"
#include <SDL2/SDL_image.h>

#define GLM_FORCE_RADIANS
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace JE{namespace GRAPHICS{

class Camera : public JE::Point{
public:
	Camera(float x, float y);
	Camera(const Camera&);
	Camera();
	
	void setAngle(float value);
	void setScale(float x, float y);
	void setScale(float value);
	void pushScale(float x, float y);
	void pushScale(float value);
	
	glm::mat4 getTranform() const;
	
private:
	float angle;
	float scale_x;
	float scale_y;
	
	float origin_x;
	float origin_y;
	
	float left;
	float right;
	float top;
	float bottom;
	
	float near;
	float far;
};

};};
