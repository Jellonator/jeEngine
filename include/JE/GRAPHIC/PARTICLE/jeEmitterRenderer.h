#pragma once
#include "../jeImage.h"

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
	void draw(const EmitterType& type, const Particle& particle);
private:
	JE::GRAPHICS::Image image;
};

}}

