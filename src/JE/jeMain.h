#pragma once
#define GL_GLEXT_PROTOTYPES
#define GLEW_STATIC
//#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
//#include <GL/glx.h>
//#include <GL/glext.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>
typedef void (*function_pointer)(void);

enum JE_ORDER{JE_ORDER_NONE, JE_ORDER_HALF, JE_ORDER_FULL};
enum JE_WORLD_MODE{JE_WORLD_MODE_NONE, JE_WORLD_MODE_ALL, JE_WORLD_MODE_GROUP};
enum JE_EVENTCOMPARE_MODE{JE_EVENTCOMPARE_TYPE,JE_EVENTCOMPARE_FULL,JE_EVENTCOMPARE_AUTO};

namespace JE{
namespace GRAPHICS{
	class Color;
	extern Color backcolor;/**< \brief the background color */
	extern Color forecolor;/**< \brief the foreground color */
	extern SDL_Window* window;/**< \brief SDL_Window* window, the global window. */
	extern SDL_Renderer* renderer;/**< \brief SDL_Renderer* renderer, the global renderer. */
	extern SDL_GLContext glcontext;
	//void draw();/**< \brief Draws the engine and the active world. */
	//void flip();/**< \brief Flips the screen. */
};
};
