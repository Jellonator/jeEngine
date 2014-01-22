#pragma once
#include <SDL2/SDL_image.h>
class jeEntity;
class jeCamera;
struct jeColor{
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
};
namespace JE{
	extern SDL_Renderer* renderer;
	extern jeColor* backcolor;
	extern jeColor* forecolor;
}
class jeGraphic
{
	public:
		jeGraphic();
		virtual ~jeGraphic();
		float x;/**< \brief float x, the graphic's X position */
		float y;/**< \brief float y, the graphic's Y position */
		float ox;/**< \brief float ox, the graphic's X origin. */
		float oy;/**< \brief float oy, the graphic's Y origin. */
		float angle;/**< \brief float rotation, the grapic's rotation. */

        /** \brief Draws the graphic at the desired coordinates.
         * \param float x, the x position.
         * \param float y, the y position.
         */
		virtual void draw(float x = 0, float y = 0, jeCamera* camera = NULL, jeEntity* parent = NULL);

		/** \brief Updates the graphic. */

		virtual void update();

        /** \brief Set's the graphic's origin.
         * \param float x, the X origin.
         * \param float y, the Y origin.
         */
		void setOrigin(float x, float y);

};

void jeSetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, SDL_Renderer* renderer = JE::renderer);
void jeSetColorF(float r, float g, float b, float a = 1.0f, SDL_Renderer* renderer = JE::renderer);

void jeSetBackgroundColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, SDL_Renderer* renderer = JE::renderer);
void jeSetBackgroundColorF(float r, float g, float b, float a = 1.0f, SDL_Renderer* renderer = JE::renderer);
