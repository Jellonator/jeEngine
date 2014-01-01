#pragma once

#include <vector>
#include <cstddef>
#include <string>
#include <iostream>
#include <cmath>
#include <cstring>
#include <SDL2/SDL_image.h>
void jePrint(std::string s);

enum JE_ORDER{JE_ORDER_NONE, JE_ORDER_HALF, JE_ORDER_FULL};
enum JE_WORLD_MODE{JE_WORLD_MODE_NONE, JE_WORLD_MODE_ALL, JE_WORLD_MODE_GROUP};
enum JE_MASK_TYPE{JE_MASK_NONE, JE_MASK_BOX, JE_MASK_GRID, JE_MASK_LIST};

class jeWorld;
class jeEntity;
class jePoint;
class jeHitBox;
class jeCamera;
class jeTilemap;
class jeGrid;
#include "jeMask.h"
#include "jeGraphic.h"
#include "jeGroup.h"

namespace JE
{
	extern SDL_Window* window;/**< \brief SDL_Window* window, the global window. */
	extern SDL_Renderer* renderer;/**< \brief SDL_Renderer* renderer, the global renderer. */
	extern SDL_Renderer* _renderer;
    extern int time;/**< \brief int time, the time of the current frame. */
	extern int frames;/**< \brief int frames, frame count.  Used to calculate FPS.  Reset when seconds == 1. */
	extern float seconds;/**< \brief float seconds.  Not really useful, just used to calculate FPS once a second. */
	extern int ptime;/**< \brief int ptime, the previous time. */
	extern float dt;/**< \brief float dt, the delta time.  The time between the last frame and the current frame */
	extern float fps;/**< \brief float fps, the frames per second.  Used for benchmarking. */
	extern jeWorld* world;/**< \brief jeWorld* world, the active world. */
};
#include "jeImage.h"
#include "jeCanvas.h"
void jeInit();/**< \brief Initiates jelloEngine. */
void jeCalcTime();/**< \brief Calculates time, called automatically by jeUpdate(); */
void jeUpdate();/**< \brief Updates the engine and the active world. */
void jeDraw();/**< \brief Draws the engine and the active world. */
void jeFlip();/**< \brief Flips the screen. */
/** \brief Initiates the global window and renderer.
 * \param name std::string, The name of the window.
 * \param SDL_WINDOWPOS_CENTERED int x, The X position of the window.
 * \param SDL_WINDOWPOS_CENTERED int y, The Y position of the window.
 * \param 640 int w, the width of the window.
 * \param 480 int h, the height of the window.
 * \param 0 int wflags, the SDL window flags.
 * \param 0 int rflags, the SDL renderer flags.
 */
void jeInitWindow(std::string name, int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED, int w = 640, int h = 480, int wflags = 0, int rflags = 0);
#include "jeEntity.h"
#include "jeWorld.h"
#include "jePoint.h"
#include "jeMask.h"
#include "jeCamera.h"
#include "jeSpritemap.h"
#include "jeTilemap.h"
#include "jeGrid.h"

