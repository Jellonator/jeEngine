#include "JE/GRAPHIC/jeGraphic.h"
#include "JE/UTIL/jeString.h"
#include "JE/UTIL/jeMath.h"
#include "JE/UTIL/jeTime.h"
#include "JE/jeUtil.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glu.h>
#include <time.h>

namespace JE{

void initWindow(std::string name, int w, int h, int wflags, int rflags){
	init();
	SDL_SetHint(SDL_HINT_RENDER_OPENGL_SHADERS, "1");
	SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	
	GRAPHICS::window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, wflags | SDL_WINDOW_OPENGL);
	if (GRAPHICS::window == NULL) {std::cout << SDL_GetError() << std::endl;}
	//GRAPHICS::renderer = SDL_CreateRenderer(GRAPHICS::window, -1, rflags | SDL_RENDERER_TARGETTEXTURE);
	//if (GRAPHICS::renderer == NULL) {std::cout << SDL_GetError() << std::endl;}
	GRAPHICS::glcontext = SDL_GL_CreateContext(GRAPHICS::window);
	//GRAPHICS::glcontext = SDL_GL_GetCurrentContext();

	GRAPHICS::setColor(255,255,255,255);
	GRAPHICS::setBackgroundColor(0,0,0,255);
	
	SDL_GL_SetSwapInterval(1);
}

int target_framerate = -1;
float time_i = 0;
void setFramerate(int framerate){
	target_framerate = framerate;
	time_i = SDL_GetTicks();
}
void update(){
	TIME::calculate();
	JE::TIME::dt = JE::TIME::_dt;
}
void init(){
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {std::cout << SDL_GetError() << std::endl;}
	if (IMG_Init(IMG_INIT_PNG) != 0) {std::cout << SDL_GetError() << std::endl;}
	std::cout << "JE: Initiated Engine." << std::endl;
	SDL_version ver;
	SDL_GetVersion(&ver);
	std::cout << "JE: Using SDL version " << (int)ver.major << "." <<
		(int)ver.minor << "." << (int)ver.patch << std::endl;
	
	srand(time(nullptr));
}

void quit(){
	//SDL_GL_DeleteContext(GRAPHICS::glcontext);
	std::cout << "JE: Quit Engine." << std::endl;
	IMG_Quit();
	SDL_Quit();
}

namespace GRAPHICS{
	void draw(){
		//screen resizing has to be done a frame later for god knows what reason
	}
}

}