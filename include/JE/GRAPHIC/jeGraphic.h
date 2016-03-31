#pragma once
#include "../jeMain.h"
#include "../jePoint.h"
#include <memory>

#define GLM_FORCE_RADIANS
#include <glm/mat4x4.hpp>

namespace JE{
class Entity;
namespace GRAPHICS{

class Color;
extern Color backcolor;/**< \brief the background color */
extern Color forecolor;/**< \brief the foreground color */
extern SDL_Window* window;/**< \brief SDL_Window* window, the global window. */
extern SDL_Renderer* renderer;/**< \brief SDL_Renderer* renderer, the global renderer. */
extern SDL_GLContext glcontext;
void draw();/**< \brief Draws the engine and the active world. */
void flip();/**< \brief Flips the screen. */
struct Color{
	float r;
	float g;
	float b;
	float a;
};
class Camera;
extern Color backcolor;
extern Color forecolor;
	
class Graphic : public JE::Point{
public:
	Graphic(float x = 0, float y = 0);
	virtual ~Graphic();
	
	virtual void update(float dt);
	
	void draw(const JE::GRAPHICS::Camera& camera, float x = 0, float y = 0) const;
	virtual void drawMatrix(const glm::mat4& camera, float x = 0, float y = 0) const;
};

/** \brief Set the color for drawing operations.
 * \param r float, Red value(0-1)
 * \param g float, Green value(0-1)
 * \param b float, Blue value(0-1)
 * \param a float, Alpha value(defaults to 1)
 * \param SDL_Renderer* renderer, the renderer to set the color of.
 */
void setColor(float r, float g, float b, float a = 1.0f);

/** \brief Set the color of the background.
 * \param r float, Red value(0-1)
 * \param g float, Green value(0-1)
 * \param b float, Blue value(0-1)
 * \param a float, Alpha value(defaults to 1)
 * \param SDL_Renderer* renderer, the renderer to set the background color of.
 */
void setBackgroundColor(float r, float g, float b, float a = 1.0f);

/** \brief Draw a rectangle.
 * \param x float, the x position of the rectangle.
 * \param y float, the y position of the rectangle.
 * \param w float, the width of the rectangle.
 * \param h float, the height of the rectangle.
 */
void drawRect(const JE::GRAPHICS::Camera& camera, bool fill, float x, float y, float w, float h);
void drawRect(const JE::GRAPHICS::Camera& camera, bool fill, float x, float y, float w, float h, float angle);
void drawRect(const JE::GRAPHICS::Camera& camera, bool fill, float x, float y, float w, float h, float angle, float originx, float originy);

void drawLine(const JE::GRAPHICS::Camera& camera, float x1, float y1, float x2, float y2);

void drawCircle(const JE::GRAPHICS::Camera& camera, float x, float y, float radius);
void drawCircle(const JE::GRAPHICS::Camera& camera, float x, float y, float radius, float thickness);
void setCircleAngleBounds(float angle1, float angle2);
void resetCircleAngleBounds();

class Image;
void drawImgRectStretch(Image& image, float x, float y, float w, float h, float tileWidth, float tileHeight);/**< \brief experimental */
//void drawImgRectRepeat(Image* image, float x, float y, float w, float h, float tileWidth, float tileHeight, GRAPHICS::Camera* camera = NULL, Entity* entity = NULL);
//void drawImgRectSmart(Image* image, float x, float y, float w, float h, float tileWidth, float tileHeight, GRAPHICS::Camera* camera = NULL, Entity* entity = NULL);

};};
