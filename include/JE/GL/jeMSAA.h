#pragma once

#include "jeModel.h"
#include "jeShader.h"

namespace JE{namespace GL{
	
class Multisampler {
public:
	Multisampler(int width, int height, int samples);
	virtual ~Multisampler();
	
	void resize(int width, int height);
	void setSamples(int samples);
	void setData(int width, int height, int samples);
	
	void reset();
	void bind();
	void unbind();
	void draw();
	
private:
	int width;
	int height;
	int samples;
	GLuint fbo;
	GLuint tex;
};
	
}}