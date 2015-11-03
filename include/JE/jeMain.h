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
#include <string>
typedef void (*function_pointer)(void);

enum JE_ORDER{JE_ORDER_NONE, JE_ORDER_HALF, JE_ORDER_FULL};
enum JE_WORLD_MODE{JE_WORLD_MODE_NONE, JE_WORLD_MODE_ALL, JE_WORLD_MODE_GROUP};
enum JE_EVENTCOMPARE_MODE{JE_EVENTCOMPARE_TYPE,JE_EVENTCOMPARE_FULL,JE_EVENTCOMPARE_AUTO};

namespace JE{

/** \brief Initiates the global window and renderer.
 * \param name std::string, The name of the window.
 * \param 640 int w, the width of the window.
 * \param 480 int h, the height of the window.
 * \param 0 int wflags, the SDL window flags.
 * \param 0 int rflags, the SDL renderer flags.
 */
void initWindow(std::string name, int w, int h, int wflags = 0, int rflags = 0);
void init();/**< \brief Initiates jelloEngine. */
void quit();
void update();/**< \brief Updates the engine and the active world. */

namespace GRAPHICS{
	class Color;
	extern Color backcolor;/**< \brief the background color */
	extern Color forecolor;/**< \brief the foreground color */
	extern SDL_Window* window;/**< \brief SDL_Window* window, the global window. */
	//extern SDL_Renderer* renderer;/**< \brief SDL_Renderer* renderer, the global renderer. */
	extern SDL_GLContext glcontext;
	//void draw();/**< \brief Draws the engine and the active world. */
	//void flip();/**< \brief Flips the screen. */
};
};
