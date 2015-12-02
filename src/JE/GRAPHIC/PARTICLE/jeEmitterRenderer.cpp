#include "JE/GRAPHIC/PARTICLE/jeEmitterType.h"
#include "JE/GRAPHIC/PARTICLE/jeParticle.h"
#include "JE/GRAPHIC/PARTICLE/jeEmitterRenderer.h"
#include "JE/GRAPHIC/jeEmitter.h"
#include "JE/GRAPHIC/jeGraphic.h"
#include "JE/UTIL/jeMath.h"
#include "JE/GL/jeModel.h"
#include "JE/GL/jeShader.h"

namespace JE{ namespace GRAPHICS{

EmitterRenderer::EmitterRenderer(){
	
}

EmitterRenderer::~EmitterRenderer(){
	
}

void EmitterRenderer::draw(const JE::GRAPHICS::Camera& camera, const Particle& particle){
	//JE::GRAPHICS::drawRect(camera, true, , particle.getY() - 1, 3, 3);
	
	JE::GL::Model& model = JE::GL::getDefaultModel();// : JE::GL::getDefaultOutlineModel();
	JE::GL::Shader& shader = JE::GL::getDefaultShader();
	
	glm::mat4x4 transform = camera.getTranform();
	transform = glm::translate(transform, glm::vec3(particle.getX() - 1, particle.getY() - 1, 0.0f));
	transform = glm::scale(transform, glm::vec3(3, 3, 1.0f));
	
	glUniformMatrix4fv(shader.getUniformPosition("in_Transform"), 1, false, glm::value_ptr(transform));
	//shader.setUniformMat("in_Transform", transform);
	//std::cout << "Num elements: " << model.getElementBuffer().getBufferSize() << std::endl;
	
	glDrawElements(
		model.getDrawMode(),
		model.getNumElements(),
		GL_UNSIGNED_INT,
		0
	);
}

void EmitterRenderer::drawBegin(){
	JE::GRAPHICS::setColor(1, 1, 1);

	JE::GL::Model& model = JE::GL::getDefaultModel();
	JE::GL::Shader& shader = JE::GL::getDefaultShader();
	
	model.bind();
}

void EmitterRenderer::drawEnd(){
	
}

//Image renderer
EmitterRendererImage::EmitterRendererImage(JE::GRAPHICS::Image& image) : EmitterRenderer(), image(image){}

EmitterRendererImage::~EmitterRendererImage(){}

void EmitterRendererImage::draw(const JE::GRAPHICS::Camera& camera, const Particle& particle){
	JE::GL::Shader& shader = JE::GL::getDefaultImageShader();
	JE::GL::Model& model = JE::GL::getDefaultImageModel();
	
	// Get drawing transformations
	glm::mat4x4 transform = camera.getTranform();
	transform = glm::translate(transform, glm::vec3(particle.getX(), particle.getY(), 0.0f));
	transform *= this->image.getTransform();
	
	// Send transformations
	shader.setUniformMat("in_Transform", transform);
	
	// Actual draw call
	glDrawElements(
		model.getDrawMode(),
		model.getNumElements(),
		GL_UNSIGNED_INT,
		0
	);
}

void EmitterRendererImage::drawBegin(){
	JE::GL::Model& model = JE::GL::getDefaultImageModel();
	JE::GL::Shader& shader = JE::GL::getDefaultImageShader();
	
	model.bind();
	
	// Transformation for texture coordinates
	glm::mat4 texcoord_transform = this->image.getTexcoordTransform();
	shader.setUniformMat("in_TexcoordTransform", texcoord_transform);
	
	if (!this->image.hasTexture()) return;
	this->image.getTexture().use();
}

void EmitterRendererImage::drawEnd(){
	this->image.getTexture().disable();
}

//Spritemap renderer
EmitterRendererSpritemap::EmitterRendererSpritemap(JE::GRAPHICS::Spritemap& spritemap, const std::string& name) : EmitterRenderer(),
spritemap(spritemap) {
	this->animation = name;
}

EmitterRendererSpritemap::~EmitterRendererSpritemap(){}

void EmitterRendererSpritemap::draw(const JE::GRAPHICS::Camera& camera, const Particle& particle){
	this->spritemap.play(this->animation);
	this->spritemap.update(particle.getTimeAlive());// really inefficient but idgaf
	this->spritemap.draw(camera, particle.getX(), particle.getY());
}

Spritemap& EmitterRendererSpritemap::getSpritemap(){
	return this->spritemap;
}

void EmitterRendererSpritemap::drawBegin(){
	
}

void EmitterRendererSpritemap::drawEnd(){
	
}

}}
