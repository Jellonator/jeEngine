#pragma once
#include "../jeImage.h"
#include "../SPRITEMAP/jeSpritemap.h"
#include "../jeCamera.h"

namespace JE{ namespace GRAPHICS{
class Emitter;
class EmitterType;
class Particle;

class EmitterRenderer{
public:
	EmitterRenderer();
	virtual ~EmitterRenderer();
	virtual void drawBegin(const JE::GRAPHICS::Camera& camera);
	virtual void drawEnd(const JE::GRAPHICS::Camera& camera);
	virtual void draw(const JE::GRAPHICS::Camera& camera, const Particle& particle);
};

class EmitterRendererImage : public EmitterRenderer{
public:
	EmitterRendererImage(JE::GRAPHICS::Image& image);
	virtual ~EmitterRendererImage();
	virtual void drawBegin(const JE::GRAPHICS::Camera& camera);
	virtual void drawEnd(const JE::GRAPHICS::Camera& camera);
	virtual void draw(const JE::GRAPHICS::Camera& camera, const Particle& particle);
private:
	JE::GRAPHICS::Image image;
};

class EmitterRendererSpritemap : public EmitterRenderer{
public:
	EmitterRendererSpritemap(JE::GRAPHICS::Spritemap& spritemap, const std::string& name);
	virtual ~EmitterRendererSpritemap();
	virtual void drawBegin(const JE::GRAPHICS::Camera& camera);
	virtual void drawEnd(const JE::GRAPHICS::Camera& camera);
	virtual void draw(const JE::GRAPHICS::Camera& camera, const Particle& particle);
	Spritemap& getSpritemap();
	std::string animation;
private:
	JE::GRAPHICS::Spritemap spritemap;
};

}}
