#include "JE/GL/jeMSAA.h"

namespace JE{namespace GL{

Multisampler::Multisampler(int width, int height, int samples)
 : width(width), height(height), samples(samples) {
	glGenFramebuffers(1, &this->fbo);
	glGenTextures(1, &this->tex);
	
	this->bind();
	
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, this->samples, GL_RGB8, this->width, this->height, false);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, this->tex, 0);
	
	this->unbind();
}

Multisampler::~Multisampler() {
	glDeleteFramebuffers(1, &this->fbo);
	glDeleteTextures(1, &this->tex);
}

void Multisampler::resize(int width, int height){
	this->setData(width, height, this->samples);
}

void Multisampler::setSamples(int samples){
	this->setData(this->width, this->height, samples);
}

void Multisampler::reset(){
	this->bind();
	
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, this->samples, GL_RGB8, this->width, this->height, false);
	
	this->unbind();
}

void Multisampler::setData(int width, int height, int samples) {
	this->width = width;
	this->height = height;
	this->samples = samples;
	
	this->reset();
}

void Multisampler::bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, this->fbo);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, this->tex);
}

void Multisampler::unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
}

void Multisampler::draw(){
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);   // Make sure no FBO is set as the draw framebuffer
	glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo); // Make sure your multisampled FBO is the read framebuffer
	glDrawBuffer(GL_BACK);                       // Set the back buffer as the draw buffer
	glBlitFramebuffer(0, 0, this->width, this->width, 0, 0, this->width, this->width, GL_COLOR_BUFFER_BIT, GL_NEAREST);
}

}}