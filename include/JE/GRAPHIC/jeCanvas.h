#pragma once
#include "jeImage.h"
#include "jeCamera.h"

namespace JE{namespace GRAPHICS{

class Canvas : public JE::GRAPHICS::Image{
public:
	Canvas(int width, int height);
	virtual ~Canvas();
	void clear();
	void drawGraphic(const JE::GRAPHICS::Graphic& graphic, const JE::GRAPHICS::Camera& camera, float x = 0, float y = 0);
	void drawGraphic(const JE::GRAPHICS::Graphic& graphic, const glm::mat4& transform, float x = 0, float y = 0);
	const JE::GRAPHICS::Camera& getCamera() const;
	void bind();
	void unbind();
	
private:
	GLuint framebuffer_object;
	GLuint depthbuffer_object;
	int render_width;
	int render_height;
	JE::GRAPHICS::Camera draw_camera;
};

};};
