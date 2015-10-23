#include "JE/GRAPHIC/PARTICLE/jeEmitterType.h"
#include "JE/GRAPHIC/PARTICLE/jeParticle.h"
#include "JE/GRAPHIC/PARTICLE/jeEmitterRenderer.h"
#include "JE/GRAPHIC/jeEmitter.h"
#include "JE/GRAPHIC/jeGraphic.h"
#include "JE/UTIL/jeMath.h"

namespace JE{ namespace GRAPHICS{

EmitterRenderer::EmitterRenderer(){
	
}

EmitterRenderer::~EmitterRenderer(){
	
}

void EmitterRenderer::draw(const EmitterType& type, const Particle& particle){
	JE::GRAPHICS::setColor(255, 255, 255);
	JE::GRAPHICS::drawRect(particle.getX() - 1, particle.getY() - 1, 3, 3, true);
}

//Image renderer
EmitterRendererImage::EmitterRendererImage(JE::GRAPHICS::Image& image) : EmitterRenderer(), image(image){}

EmitterRendererImage::~EmitterRendererImage(){}

void EmitterRendererImage::draw(const EmitterType& type, const Particle& particle){
	this->image.draw(particle.getX(), particle.getY());
}

//Spritemap renderer
EmitterRendererSpritemap::EmitterRendererSpritemap(JE::GRAPHICS::Spritemap& spritemap, const std::string& name) : EmitterRenderer(),
spritemap(spritemap) {
	this->animation = name;
}

EmitterRendererSpritemap::~EmitterRendererSpritemap(){}

void EmitterRendererSpritemap::draw(const EmitterType& type, const Particle& particle){
	this->spritemap.play(this->animation);
	this->spritemap.update(particle.getTimeAlive());// really inefficient but idgaf
	this->spritemap.draw(particle.getX(), particle.getY());
}

Spritemap& EmitterRendererSpritemap::getSpritemap(){
	return this->spritemap;
}

}}