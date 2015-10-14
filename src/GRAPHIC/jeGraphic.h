#pragma once
#include "../jeMain.h"
#include "../jePoint.h"
#include <memory>
namespace JE{
class Entity;
namespace MASK{
	class Line;
}
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
};
class Graphic : public JE::Point
{
	public:
		Graphic(float x = 0, float y = 0);
		virtual ~Graphic();
		//float x;/**< \brief float x, the graphic's X position */
		//float y;/**< \brief float y, the graphic's Y position */
		float ox;/**< \brief float ox, the graphic's X origin. */
		float oy;/**< \brief float oy, the graphic's Y origin. */
		float angle;/**< \brief float rotation, the grapic's rotation. */

        /** \brief Draws a graphic, slightly more advanced
         * \param float x, the x position to draw at
         * \param float y, the y position to draw at
         * \param jeGRAPHICS::Camera* camera, the camera to use
         * \param jeEntity* parent, the grapic's parent entity
         * \param float angle, the angle to draw with
         * \param SDL_Renderer* renderer, the renderer to draw to
         */
		//virtual void drawExt(float x = 0, float y = 0, GRAPHICS::Camera* camera = NULL, Entity* parent = NULL, float angle = 0, SDL_Renderer* renderer = GRAPHICS::renderer);
        /** \brief Draws a graphic, does not use angles.
         * \param float x, the x position to draw at
         * \param float y, the y position to draw at
         * \param jeGRAPHICS::Camera* camera, the camera to use
         * \param jeEntity* parent, the grapic's parent entity
         */
		virtual void draw(float x = 0, float y = 0, float angle = 0, const std::shared_ptr<Entity>& parent = NULL);

		/** \brief Updates the graphic. */

		virtual void update();

        /** \brief Set's the graphic's origin.
         * \param float x, the X origin.
         * \param float y, the Y origin.
         */
		void setOrigin(float x, float y, bool adjustPosition = false);
};
namespace GRAPHICS{
    /** \brief Set the color for drawing operations.
     * \param r Uint8, Red value(0-255)
     * \param g Uint8, Green value(0-255)
     * \param b Uint8, Blue value(0-255)
     * \param a Uint8, Alpha value(defaults to 255)
     * \param SDL_Renderer* renderer, the renderer to set the color of.
     */
	void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
    /** \brief Set the color for drawing operations.
     * \param r float, Red value(0-1)
     * \param g float, Green value(0-1)
     * \param b float, Blue value(0-1)
     * \param a float, Alpha value(defaults to 1)
     * \param SDL_Renderer* renderer, the renderer to set the color of.
     */
	void setColorF(float r, float g, float b, float a = 1.0f);

    /** \brief Set the color of the background.
     * \param r Uint8, Red value(0-255)
     * \param g Uint8, Green value(0-255)
     * \param b Uint8, Blue value(0-255)
     * \param a Uint8, Alpha value(defaults to 255)
     * \param SDL_Renderer* renderer, the renderer to set the background color of.
     */
	void setBackgroundColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
    /** \brief Set the color of the background.
     * \param r float, Red value(0-1)
     * \param g float, Green value(0-1)
     * \param b float, Blue value(0-1)
     * \param a float, Alpha value(defaults to 1)
     * \param SDL_Renderer* renderer, the renderer to set the background color of.
     */
	void setBackgroundColorF(float r, float g, float b, float a = 1.0f);

    /** \brief Draw a rectangle.
     * \param x float, the x position of the rectangle.
     * \param y float, the y position of the rectangle.
     * \param w float, the width of the rectangle.
     * \param h float, the height of the rectangle.
     */
	void drawRect(float x, float y, float w, float h, bool fill);
	
	void drawRect(float x, float y, float w, float h, float angle, bool fill);
	void drawRect(float x, float y, float w, float h, float angle, float originx, float originy, bool fill);
	
	void drawLine(float x1, float y1, float x2, float y2);
	
	void drawCircle(float x, float y, float radius, int points, bool fill);

	class Image;
	void drawImgRectStretch(const std::shared_ptr<Image>& image, float x, float y, float w, float h,
		float tileWidth, float tileHeight, const std::shared_ptr<Entity>& entity = NULL);/**< \brief experimental */
	//void drawImgRectRepeat(Image* image, float x, float y, float w, float h, float tileWidth, float tileHeight, GRAPHICS::Camera* camera = NULL, Entity* entity = NULL);
	//void drawImgRectSmart(Image* image, float x, float y, float w, float h, float tileWidth, float tileHeight, GRAPHICS::Camera* camera = NULL, Entity* entity = NULL);
	void resize(int width, int height);
	void resize();
};};
