#pragma once
#include <vector>
#include <cstddef>
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <map>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>


typedef void (*function_pointer)(void);

enum JE_ORDER{JE_ORDER_NONE, JE_ORDER_HALF, JE_ORDER_FULL};
enum JE_WORLD_MODE{JE_WORLD_MODE_NONE, JE_WORLD_MODE_ALL, JE_WORLD_MODE_GROUP};
enum JE_EVENTCOMPARE_MODE{JE_EVENTCOMPARE_TYPE,JE_EVENTCOMPARE_FULL,JE_EVENTCOMPARE_AUTO};

#include "jeMask.h"
#include "jeGraphic.h"
#include "jeGroup.h"

namespace JE
{
/** \brief convert an integer to a string
 * \param number int the number to be stringified
 * \return std::string the resulting string
 */
std::string toString(int number);
int toInt(std::string string);
namespace EVENT{
	typedef SDL_Event Input;/**< \brief Naming convention for SDL_Event. */
};
namespace GRAPHICS{
	class Camera;
	class Tilemap;
	extern Color* backcolor;/**< \brief the background color */
	extern Color* forecolor;/**< \brief the foreground color */
	extern SDL_Window* window;/**< \brief SDL_Window* window, the global window. */
	extern SDL_Renderer* renderer;/**< \brief SDL_Renderer* renderer, the global renderer. */
	extern SDL_GLContext glcontext;
	void draw();/**< \brief Draws the engine and the active world. */
	void flip();/**< \brief Flips the screen. */
};
namespace TIME{
	extern int time;/**< \brief int time, the time of the current frame. */
	extern int frames;/**< \brief int frames, frame count.  Used to calculate FPS.  Reset when seconds == 1. */
	extern double seconds;/**< \brief float seconds.  Not really useful, just used to calculate FPS once a second. */
	extern int ptime;/**< \brief int ptime, the previous time. */
	extern float dt;/**< \brief float dt, the delta time.  The time between the last frame and the current frame */
	extern double _dt;/**< \brief float dt, the delta time.  The time between the last frame and the current frame */
	extern double limit;/**< \brief float limit, the delta time cap */
	extern double fps;/**< \brief float fps, the frames per second.  Used for benchmarking. */
	extern bool printFPS;/**< \brief if the engine should print the FPS every second. */
	void calculate();/**< \brief Calculates time, called automatically by jeUpdate(); */
  /** \brief sets a maximum delta time, so things don't get weird after, say, a loading sequence.
   * \param float limit the maximum the delta time can be
   */
	void setDeltaTimeLimit(double limit = 1.0f/15.0f);
};
namespace MATH{
	extern float RAD;/**< \brief number to convert degrees to radians, i.e. radians = RAD*degrees. */
	extern float DEG;/**< \brief number to convert radians to degrees, i.e. degrees = DEG*radians. */
  /** \brief returns either 1 or -1, depending on the number's sign. Returns 0 for 0.
   * \param num int the number to get the sign of
   */
	int getSign(float num);
  /** \brief returns a random number between a and b.
   * \param a float
   * \param b float
   */
	float random(float a, float b);
  /** \brief returns the distance between two points
   * \param x1 float the x of point 1
   * \param y1 float the y of point 1
   * \param x2 float the x of point 2
   * \param y2 float the y of point 2
   */
	float distance(float x1, float y1, float x2, float y2);
  /** \brief faster version of JE::MATH::distance, which can be used for comparisons(do not use for actual distance)
   * \param x1 float the x of point 1
   * \param y1 float the y of point 1
   * \param x2 float the x of point 2
   * \param y2 float the y of point 2
   */
	float squareDistance(float x1, float y1, float x2, float y2);
  /** \brief returns the x coordinate of the point of distance and angle(yes I know this is confusing it's basically short for return std::cos(RAD*angle)*distance+x;)
   * \param angle float the angle of the coordinate
   * \param distance float the distance of the coordinate
   * \param x float the base of the coordinate
   */
	float Xangle(float angle, float distance, float x = 0);
  /** \brief returns the y coordinate of the point of distance and angle(yes I know this is confusing it's basically short for return std::sin(RAD*angle)*distance+y;)
   * \param angle float the angle of the coordinate
   * \param distance float the distance of the coordinate
   * \param y float the base of the coordinate
   */
	float Yangle(float angle, float distance, float y = 0);
  /** \brief value/100 chance to return true
   * \param value float chance to return true, 0 being no chance, 100 being 100% chance
   */
	bool chance(float value);
  /** \brief a/b chance to return true(e.g. chance(3, 4) has 75% chance)
   * \param a float the numerator
   * \param b float the denominator
   */
	bool chance(float a, float b);
  /** \brief returns the angle between two points
   * \param x1 float the x of point 1
   * \param y1 float the y of point 1
   * \param x2 float the x of point 2
   * \param y2 float the y of point 2
   */
	float getAngle(float x1, float y1, float x2, float y2);
  /** \brief takes a value and moves it closer to a desired value, smoothly
   * \param pos float the beginning position
   * \param to float the destination
   * \param speed float the speed to move the position
   * \param float minSpeed the mininum speed to move the position
   * \return float the new position
   */
	float smoothTween(float pos, float to, float speed, float minSpeed = 5);
	float clamp(float value, float min, float max);
};
namespace MASK{
	class HitBox;
	class Grid;
};
class World;
class Entity;
extern World* world;/**< \brief jeWorld* world, the active world. */
void init();/**< \brief Initiates jelloEngine. */
void quit();
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
/** \brief Prints string to console output.
 * \param string s, string to print.
 */
void print(std::string s);
std::string fileOpen(std::string file);
};
#include "jeImage.h"
#include "jeParticle.h"
#include "jeCanvas.h"
#include "jeEntity.h"
#include "jeWorld.h"
#include "jePoint.h"
#include "jeMask.h"
#include "jeCamera.h"
#include "jeSpritemap.h"
#include "jeTilemap.h"
#include "jeGrid.h"
#include "jeHitBox.h"
#include "jeEvent.h"
#include "jeLine.h"
#include "jeShader.h"
#include "jeProgram.h"
#include "jeModel.h"
