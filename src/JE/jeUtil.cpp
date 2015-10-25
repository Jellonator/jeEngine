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
bool should_resize = false;
bool fix_resize = false;
void initGL(){
	glShadeModel( GL_SMOOTH );

	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glClearDepth( 1.0f );

	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST );
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
	//SDL_GL_SetAttribute(SDL_GL_, 4);
}
int setViewport( int width, int height ){
	glViewport( 0, 0, ( GLsizei )width, ( GLsizei )height );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	//gluPerspective( 45.0f, ratio, 0.1f, 100.0f );
	glOrtho(0.0, width, height, 0.0, 0.0, 1000.0);
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );
	return 1;
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
int resize_sdl_event(void * userdata, SDL_Event* event){
	if (event->type == SDL_WINDOWEVENT){
		if (event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED){
			GRAPHICS::resize();
		}
	}
	return 1;
}

void initWindow(std::string name, int w, int h, int wflags, int rflags){
	init();
	SDL_SetHint(SDL_HINT_RENDER_OPENGL_SHADERS, "1");
	SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
	GRAPHICS::window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, wflags | SDL_WINDOW_OPENGL);
    if (GRAPHICS::window == NULL) {std::cout << SDL_GetError() << std::endl;}
	GRAPHICS::renderer = SDL_CreateRenderer(GRAPHICS::window, -1, rflags | SDL_RENDERER_TARGETTEXTURE);
    if (GRAPHICS::renderer == NULL) {std::cout << SDL_GetError() << std::endl;}
	GRAPHICS::glcontext = SDL_GL_CreateContext(GRAPHICS::window);
	GRAPHICS::glcontext = SDL_GL_GetCurrentContext();

	GRAPHICS::setColor(255,255,255,255);
	GRAPHICS::setBackgroundColor(0,0,0,255);

	setViewport(w, h);

	//yay workarounds
	SDL_SetWindowSize(GRAPHICS::window, w, h);
	GRAPHICS::resize();
	initGL();
	/*
		Explanation for window resize work-around:
		The first resize of an application will reset the openGL context,
		all following resizes will have no effect.
		To get around this, a resize is forced to the window.
	*/
	SDL_SetEventFilter(resize_sdl_event, nullptr);
	std::cout << "JE: Initiated Window." << std::endl;
}
int target_framerate = -1;
float time_i = 0;
void setFramerate(int framerate){
	target_framerate = framerate;
	time_i = SDL_GetTicks();
}
void update(){
	TIME::calculate();
}
std::string fileOpen(std::string file){
	std::ifstream in(file.c_str());
	std::string text = "";
	std::string temp = "";
	int i = 0;
	if (!in.is_open()) {
		std::cout << "JE: File " << file << " does not exist!" << std::endl;
		text += "JE: File ";
		text += file;
		text += " does not exist!";
		return (char*)text.c_str();
	}
	while (getline (in,temp))
	{
		i ++;
		//std::cout << i << ":\t" << temp << std::endl;
		text += temp;
		text += '\n';
	}
	//std::cout << text << std::endl;
	return text;
}
namespace GRAPHICS{
	void draw(){
		//screen resizing has to be done a frame later for god knows what reason
		if (fix_resize){
			int w, h;
			SDL_GetWindowSize(window, &w, &h);
			setViewport(w, h);
			initGL();
			fix_resize = false;
		}
		if (should_resize){
			fix_resize = true;
			should_resize = false;
		}
	}
	void resize(){
		int w, h;
		SDL_GetWindowSize(JE::GRAPHICS::window, &w, &h);
		resize(w, h);
	}
	void resize(int width, int height){
		should_resize = true;
	}
}
namespace STRING{
	int toInt(std::string string){
		int numb;
		std::istringstream(string) >> numb;
		return numb;
	}
	std::vector<std::string> seperateString(std::string string, char seperator){
		std::vector<std::string> strings;
		std::istringstream ss(string);
		while (ss){
			std::string s;
			if (ss.eof()) break;
			if (!getline(ss, s, seperator)) break;
			strings.push_back(s);
		}
		return strings;
	}
}
}
