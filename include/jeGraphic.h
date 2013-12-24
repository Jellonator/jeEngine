#pragma once

#include <SDL2/SDL_image.h>
class jeEntity;
class jeCamera;

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
