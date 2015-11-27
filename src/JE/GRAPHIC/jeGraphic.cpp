#include "JE/UTIL/jeMath.h"
#include "JE/GRAPHIC/jeCamera.h"
#include "JE/GRAPHIC/jeGraphic.h"
#include "JE/GRAPHIC/jeImage.h"

#include "JE/GL/jeShader.h"
#include "JE/GL/jeModel.h"

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

namespace JE{namespace GRAPHICS{
	
Graphic::Graphic(float x, float y) : JE::Point(x, y){}
Graphic::~Graphic(){}
void Graphic::draw(const JE::GRAPHICS::Camera& camera, float x, float y)const{}
void Graphic::update(float dt){}

SDL_Window* window;
SDL_Renderer* renderer;
SDL_GLContext glcontext;
Color backcolor;
Color forecolor;
void flip(){
	SDL_GL_SwapWindow(window);
}

void setColor(float r, float g, float b, float a){
	forecolor.r = r;
	forecolor.g = g;
	forecolor.b = b;
	forecolor.a = a;
	JE::GL::getDefaultShader().setUniform("in_Color", r, g, b, a);
	JE::GL::getDefaultCircleShader().setUniform("in_Color", r, g, b, a);
}

void setBackgroundColor(float r, float g, float b, float a){
	backcolor.r = r;
	backcolor.g = g;
	backcolor.b = b;
	backcolor.a = a;
	glClearColor(r, g, b, a);
}

void drawRect(const JE::GRAPHICS::Camera& camera, bool fill, float x, float y, float w, float h){
	JE::GL::Model& model = fill ? JE::GL::getDefaultModel() : JE::GL::getDefaultOutlineModel();
	JE::GL::Shader& shader = JE::GL::getDefaultShader();
	
	glm::mat4x4 transform = camera.getTranform();
	transform = glm::translate(transform, glm::vec3(x, y, 0.0f));
	transform = glm::scale(transform, glm::vec3(w, h, 1.0f));
	
	shader.setUniformMat("in_Transform", transform);
	
	model.draw();
}

void drawRect(const JE::GRAPHICS::Camera& camera, bool fill, float x, float y, float w, float h, float angle){
	drawRect(camera, fill, x, y, w, h, angle, w / 2, h / 2);
}

void drawRect(const JE::GRAPHICS::Camera& camera, bool fill, float x, float y, float w, float h, float angle, float originx, float originy){
	JE::GL::Model& model = fill ? JE::GL::getDefaultModel() : JE::GL::getDefaultOutlineModel();
	JE::GL::Shader& shader = JE::GL::getDefaultShader();
	
	glm::mat4x4 transform = camera.getTranform();
	transform = glm::translate(transform, glm::vec3(x, y, 0.0f));
	transform = glm::translate(transform, glm::vec3(originx, originy, 0.0f));
	transform = glm::rotate(transform, angle, glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::translate(transform, glm::vec3(-originx, -originy, 0.0f));
	transform = glm::scale(transform, glm::vec3(w, h, 1.0f));
	
	shader.setUniformMat("in_Transform", transform);
	
	model.draw();
}

void drawLine(float x1, float y1, float x2, float y2){
	
}

void drawCircle(const JE::GRAPHICS::Camera& camera, float x, float y, float radius){
	JE::GL::Model& model = JE::GL::getDefaultCircleModel();
	JE::GL::Shader& shader = JE::GL::getDefaultCircleShader();
	
	glm::mat4x4 transform = camera.getTranform();
	transform = glm::translate(transform, glm::vec3(x, y, 0.0f));
	transform = glm::scale(transform, glm::vec3(radius, radius, 1.0f));
	
	shader.setUniformMat("in_Transform", transform);
	shader.setUniform("in_RadiusInner", 0.0f);
	
	model.draw();
}

void drawCircle(const JE::GRAPHICS::Camera& camera, float x, float y, float radius, float thickness){
	thickness = std::max(thickness, camera.getPixelSize());
	
	JE::GL::Model& model = JE::GL::getDefaultCircleModel();
	JE::GL::Shader& shader = JE::GL::getDefaultCircleShader();
	
	glm::mat4x4 transform = camera.getTranform();
	transform = glm::translate(transform, glm::vec3(x, y, 0.0f));
	transform = glm::scale(transform, glm::vec3(radius, radius, 1.0f));
	
	shader.setUniformMat("in_Transform", transform);
	shader.setUniform("in_RadiusInner", 1.0f-thickness/radius);
	
	model.draw();
}
/*
void drawImgRectStretch(Image& image, float x, float y, float w, float h, float tileWidth, float tileHeight){
//store texture width
	int tw, th;
	image.texture->getSize(&tw, &th);
	//make sure image is big enough
	if (tw >= tileWidth*2 && th >= tileHeight*2){
	//store temporary information
		SDL_Rect temprect = image.clip;
		bool tempbool = image.use_clip;
		float tempWidth = image.width;
		float tempHeight = image.height;
		//Set size to corner
		image.setSize(tileWidth,tileHeight);
	//Drawing operations
		//upper left
		image.setClip(0,0,tileWidth,tileHeight);
		image.draw(x, y, 0);
		//upper right
		image.setClip(tw-tileWidth, 0,tileWidth,tileHeight);
		image.draw(x+w-tileWidth, y, 0);
		//lower left
		image.setClip(0,th-tileHeight, tileWidth,tileHeight);
		image.draw(x, y+h-tileHeight, 0);
		//lower right
		image.setClip(tw-tileWidth, th-tileHeight,tileWidth,tileHeight);
		image.draw(x+w-tileWidth, y+h-tileHeight, 0);
	//Now draw the sides
	//top/bottom size
		if (h > tileHeight*2){
			image.setSize(w-tileWidth*2,tileHeight);
			//top side
			image.setClip(tileWidth,0,tw-tileWidth*2,tileHeight);
			image.draw(x+tileWidth,y, 0);
			//bottom side
			image.setClip(tileWidth,th-tileHeight,tw-tileWidth*2,tileHeight);
			image.draw(x+tileWidth,y+h-tileHeight, 0);
		}
	//left/right sizes
		if (w > tileWidth*2){
			image.setSize(tileWidth, h-tileHeight*2);
			//left side
			image.setClip(0,tileHeight,tileWidth,tw-tileHeight*2);
			image.draw(x,y+tileHeight, 0);
			//right side
			image.setClip(tw-tileWidth,tileHeight,tileWidth,tw-tileHeight*2);
			image.draw(x+w-tileWidth,y+tileHeight, 0);
		}
	//and the center
		if (h > tileHeight*2 && w > tileWidth*2){
			image.setSize(w-tileWidth*2,h-tileHeight*2);
			image.setClip(tileWidth,tileHeight,tw-tileWidth*2,th-tileHeight*2);
			image.draw(x+tileWidth,y+tileHeight, 0);
		}
	//Reset image
		image.clip = temprect;
		image.width = tempWidth;
		image.height = tempHeight;
		image.use_clip = tempbool;
	}
}*/

}}
