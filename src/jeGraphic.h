#pragma once
#include <SDL2/SDL_image.h>
namespace JE{
class Entity;
namespace GRAPHICS{
	struct Color{
		Uint8 r;
		Uint8 g;
		Uint8 b;
		Uint8 a;
	};
	class Camera;
	extern SDL_Renderer* renderer;
	extern Color* backcolor;
	extern Color* forecolor;
};
class Graphic
{
	public:
		Graphic();
		virtual ~Graphic();
		float x;/**< \brief float x, the graphic's X position */
		float y;/**< \brief float y, the graphic's Y position */
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
		virtual void drawExt(float x = 0, float y = 0, GRAPHICS::Camera* camera = NULL, Entity* parent = NULL, float angle = 0, SDL_Renderer* renderer = GRAPHICS::renderer);
        /** \brief Draws a graphic, does not use angles.
         * \param float x, the x position to draw at
         * \param float y, the y position to draw at
         * \param jeGRAPHICS::Camera* camera, the camera to use
         * \param jeEntity* parent, the grapic's parent entity
         */
		virtual void draw(float x = 0, float y = 0, GRAPHICS::Camera* camera = NULL, Entity* parent = NULL);

		/** \brief Updates the graphic. */

		virtual void update();

        /** \brief Set's the graphic's origin.
         * \param float x, the X origin.
         * \param float y, the Y origin.
         */
		void setOrigin(float x, float y);

};
namespace GRAPHICS{
    /** \brief Set the color for drawing operations.
     * \param r Uint8, Red value(0-255)
     * \param g Uint8, Green value(0-255)
     * \param b Uint8, Blue value(0-255)
     * \param a Uint8, Alpha value(defaults to 255)
     * \param SDL_Renderer* renderer, the renderer to set the color of.
     */
	void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, SDL_Renderer* renderer = GRAPHICS::renderer);
    /** \brief Set the color for drawing operations.
     * \param r float, Red value(0-1)
     * \param g float, Green value(0-1)
     * \param b float, Blue value(0-1)
     * \param a float, Alpha value(defaults to 1)
     * \param SDL_Renderer* renderer, the renderer to set the color of.
     */
	void setColorF(float r, float g, float b, float a = 1.0f, SDL_Renderer* renderer = GRAPHICS::renderer);

    /** \brief Set the color of the background.
     * \param r Uint8, Red value(0-255)
     * \param g Uint8, Green value(0-255)
     * \param b Uint8, Blue value(0-255)
     * \param a Uint8, Alpha value(defaults to 255)
     * \param SDL_Renderer* renderer, the renderer to set the background color of.
     */
	void setBackgroundColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, SDL_Renderer* renderer = GRAPHICS::renderer);
    /** \brief Set the color of the background.
     * \param r float, Red value(0-1)
     * \param g float, Green value(0-1)
     * \param b float, Blue value(0-1)
     * \param a float, Alpha value(defaults to 1)
     * \param SDL_Renderer* renderer, the renderer to set the background color of.
     */
	void setBackgroundColorF(float r, float g, float b, float a = 1.0f, SDL_Renderer* renderer = GRAPHICS::renderer);

    /** \brief Draw a rectangle.
     * \param x float, the x position of the rectangle.
     * \param y float, the y position of the rectangle.
     * \param w float, the width of the rectangle.
     * \param h float, the height of the rectangle.
     * \param camera Camera*, the camera to use for transformations.
     */
	void drawRect(float x, float y, float w, float h, GRAPHICS::Camera* camera = NULL);
    /** \brief Draw a filled rectangle.
     * \param x float, the x position of the rectangle.
     * \param y float, the y position of the rectangle.
     * \param w float, the width of the rectangle.
     * \param h float, the height of the rectangle.
     * \param camera Camera*, the camera to use for transformations.
     */
	void fillRect(float x, float y, float w, float h, GRAPHICS::Camera* camera = NULL);

	class Image;
	void drawImgRectStretch(Image* image, float x, float y, float w, float h, float tileWidth, float tileHeight, GRAPHICS::Camera* camera = NULL, Entity* entity = NULL);/**< \brief experimental */
	//void drawImgRectRepeat(Image* image, float x, float y, float w, float h, float tileWidth, float tileHeight, GRAPHICS::Camera* camera = NULL, Entity* entity = NULL);
	//void drawImgRectSmart(Image* image, float x, float y, float w, float h, float tileWidth, float tileHeight, GRAPHICS::Camera* camera = NULL, Entity* entity = NULL);
};};
