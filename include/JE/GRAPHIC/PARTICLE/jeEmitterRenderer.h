#pragma once
#include "../jeImage.h"
#include "../jeSpritemap.h"

/*
namespace JE{ namespace GRAPHICS{
class Emitter;
class EmitterType;
class Particle;

class EmitterRenderer{
public:
	EmitterRenderer();
	virtual ~EmitterRenderer();
	virtual void draw(const EmitterType& type, const Particle& particle);
};

class EmitterRendererImage : public EmitterRenderer{
public:
	EmitterRendererImage(JE::GRAPHICS::Image& image);
	virtual ~EmitterRendererImage();
	virtual void draw(const EmitterType& type, const Particle& particle);
private:
	JE::GRAPHICS::Image image;
};

class EmitterRendererSpritemap : public EmitterRenderer{
public:
	EmitterRendererSpritemap(JE::GRAPHICS::Spritemap& spritemap, const std::string& name);
	virtual ~EmitterRendererSpritemap();
	virtual void draw(const EmitterType& type, const Particle& particle);
	Spritemap& getSpritemap();
	std::string animation;
private:
	JE::GRAPHICS::Spritemap spritemap;
};

}}
*/