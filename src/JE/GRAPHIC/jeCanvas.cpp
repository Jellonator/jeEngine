#include "JE/GRAPHIC/jeCanvas.h"
#include <iostream>

namespace JE{namespace GRAPHICS{
	
Canvas::Canvas(int width, int height) : Image(width, height){
	this->render_width = width;
	this->render_height = height;
	
	// Generate framebuffer
	glGenFramebuffers(1, &this->framebuffer_object);
	glBindFramebuffer(GL_FRAMEBUFFER, this->framebuffer_object);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, this->getTexture().getTexture(), 0);
	
	// Generate render buffer
	glGenRenderbuffers(1, &this->depthbuffer_object);
	glBindRenderbuffer(GL_RENDERBUFFER, this->depthbuffer_object);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	
	// Use texture
	this->getTexture().use();
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, this->depthbuffer_object);
	
	// Check status
	GLenum status;
	status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE){
		std::cout << "Framebuffer failed to create!" << std::endl;
	}
	
	// Configure camera
	this->draw_camera.setBounds(0.0, 0.0, width, height);
	
	// unbindall
	this->unbind();
	
	// Flip canvas(since things are rendered up-side-down)
	this->setFlipY(true);
	this->setOrigin(width/2, height/2);
}

const JE::GRAPHICS::Camera& Canvas::getCamera() const{
	return this->draw_camera;
}

void Canvas::clear(){
	this->bind();
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(backcolor.r, backcolor.g, backcolor.b, backcolor.a);
	this->unbind();
}

void Canvas::drawGraphic(const JE::GRAPHICS::Graphic& graphic, const JE::GRAPHICS::Camera& camera, float x, float y){
	this->drawGraphic(graphic, camera.getTranform(), x, y);
}

void Canvas::drawGraphic(const JE::GRAPHICS::Graphic& graphic, const glm::mat4& transform, float x, float y){
	this->bind();
	
	glm::mat4 matrix = transform;
	matrix = matrix * this->getCamera().getTranform();
	
	graphic.drawMatrix(matrix, x, y);
	
	this->unbind();
}

void Canvas::bind(){
	glBindFramebuffer(GL_FRAMEBUFFER, this->framebuffer_object);
	glViewport(0, 0, this->render_width, this->render_height);
}

void Canvas::unbind(){
	this->getTexture().disable();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	int w, h;
	SDL_GetWindowSize(JE::GRAPHICS::window, &w, &h);
	glViewport(0, 0, w, h);
}

Canvas::~Canvas(){
	this->unbind();
	glDeleteFramebuffers(1, &this->framebuffer_object);
	glDeleteRenderbuffers(1, &this->depthbuffer_object);
}

}}