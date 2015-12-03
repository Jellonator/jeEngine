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

bool do_resize_next_frame;
int new_window_width;
int new_window_height;

void initWindow(std::string name, int w, int h, int wflags){
	JE::init();
	SDL_SetHint(SDL_HINT_RENDER_OPENGL_SHADERS, "1");
	SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
	
	
	// Create window
	GRAPHICS::window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, wflags | SDL_WINDOW_OPENGL);
	if (GRAPHICS::window == nullptr) {
		std::cout << SDL_GetError() << std::endl;
	}
	
	// Set OpenGL attributes
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	
	// Create context
	GRAPHICS::glcontext = SDL_GL_CreateContext(GRAPHICS::window);
	
	// Config OpenGL
	glEnable( GL_BLEND );
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	// This is primarily a 2D game, so depth isn't needed. 
	glDisable( GL_DEPTH_TEST );
	
	// No Vsync
	SDL_GL_SetSwapInterval(0);
	
	// Enable GLEW
	glewExperimental = GL_TRUE;
	glewInit();
	
	// Set clear color to a nice blue-purple
	JE::GRAPHICS::setBackgroundColor(0.2, 0.1, 0.3, 0.0);
	
	// Necessary in order to make sure that the viewport gets resized when the
	// window is resized. Using lambdas because it's cool and futuristic.
	SDL_AddEventWatch(
	[](void* userdata, SDL_Event* event) -> int{
		if (event->type == SDL_WINDOWEVENT){
			if (event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED){
				do_resize_next_frame = true;
				new_window_height = event->window.data2;
				new_window_width = event->window.data1;
			}
		}
		return 1;
	}, nullptr);
	
	do_resize_next_frame = false;
	
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
	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0) {std::cout << "IMG_Error: " << IMG_GetError() << std::endl;}
	std::cout << "JE: Initiated Engine." << std::endl;
	SDL_version ver;
	SDL_GetVersion(&ver);
	
	std::cout << "JE: Using SDL version " << 
		(int)ver.major << "." <<
		(int)ver.minor << "." << 
		(int)ver.patch << std::endl;
	
	srand(time(nullptr));
}

void quit(){
	SDL_GL_DeleteContext(JE::GRAPHICS::glcontext);
	SDL_DestroyWindow(JE::GRAPHICS::window);
	std::cout << "JE: Quit Engine." << std::endl;
	IMG_Quit();
	SDL_Quit();
}

namespace GRAPHICS{
	void draw(){
		if (do_resize_next_frame){
			do_resize_next_frame = false;
			glViewport(0, 0, new_window_width, new_window_height);
			glScissor(0, 0, new_window_width, new_window_height);
		}
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	}
}

}