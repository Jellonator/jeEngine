#pragma once

#include <vector>
#include <cstddef>
#include <string>
#include <iostream>
#include <cmath>
#include <cstring>
#include <map>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#define jeRAD 0.0174532925
#define jeDEG 57.295779515

typedef void (*function_pointer)(void);

enum JE_ORDER{JE_ORDER_NONE, JE_ORDER_HALF, JE_ORDER_FULL};
enum JE_WORLD_MODE{JE_WORLD_MODE_NONE, JE_WORLD_MODE_ALL, JE_WORLD_MODE_GROUP};
enum JE_EVENTCOMPARE_MODE{JE_EVENTCOMPARE_TYPE,JE_EVENTCOMPARE_FULL,JE_EVENTCOMPARE_AUTO};

#include "jeMask.h"
#include "jeGraphic.h"
#include "jeGroup.h"

namespace JE
{
#define Input SDL_Event
namespace EVENT{};
namespace GRAPHICS{
	class Camera;
	class Tilemap;
	extern Color* backcolor;/**< \brief the background color */
	extern Color* forecolor;/**< \brief the foreground color */
	extern SDL_Window* window;/**< \brief SDL_Window* window, the global window. */
	extern SDL_Renderer* renderer;/**< \brief SDL_Renderer* renderer, the global renderer. */
	void draw();/**< \brief Draws the engine and the active world. */
	void flip();/**< \brief Flips the screen. */
};
namespace TIME{
	extern int time;/**< \brief int time, the time of the current frame. */
	extern int frames;/**< \brief int frames, frame count.  Used to calculate FPS.  Reset when seconds == 1. */
	extern float seconds;/**< \brief float seconds.  Not really useful, just used to calculate FPS once a second. */
	extern int ptime;/**< \brief int ptime, the previous time. */
	extern float dt;/**< \brief float dt, the delta time.  The time between the last frame and the current frame */
	extern float fps;/**< \brief float fps, the frames per second.  Used for benchmarking. */
	void calculate();/**< \brief Calculates time, called automatically by jeUpdate(); */
};
namespace MATH{
	float getSign(float f);
};
namespace MASK{
	class HitBox;
	class Grid;
};
class World;
class Entity;
extern World* world;/**< \brief jeWorld* world, the active world. */
void init();/**< \brief Initiates jelloEngine. */
void update();/**< \brief Updates the engine and the active world. */

/** \brief Initiates the global window and renderer.
 * \param name std::string, The name of the window.
 * \param SDL_WINDOWPOS_CENTERED int x, The X position of the window.
 * \param SDL_WINDOWPOS_CENTERED int y, The Y position of the window.
 * \param 640 int w, the width of the window.
 * \param 480 int h, the height of the window.
 * \param 0 int wflags, the SDL window flags.
 * \param 0 int rflags, the SDL renderer flags.
 */
void initWindow(std::string name, int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED, int w = 640, int h = 480, int wflags = 0, int rflags = 0);
void print(std::string s);
};
#include "jeImage.h"
#include "jeCanvas.h"
#include "jeEntity.h"
#include "jeWorld.h"
#include "jePoint.h"
#include "jeMask.h"
#include "jeCamera.h"
#include "jeSpritemap.h"
#include "jeTilemap.h"
#include "jeGrid.h"
#include "jeEvent.h"
#include "jeLine.h"
#include "jeShader.h"
#include "jeProgram.h"
#include "jeModel.h"