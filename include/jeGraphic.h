#pragma once
#include "JE.h"

class jeGraphic
{
	public:
		jeGraphic();
		virtual ~jeGraphic();
		jePoint* origin;/**< \brief jePoint* point, the graphic's origin. */
		jePoint* scale;/**< \brief jePoint* point, the graphic's scale. */
		float rotation;/**< \brief float rotation, the grapic's rotation. */

        /** \brief Draws the graphic at the desired coordinates.
         * \param float x, the x position.
         * \param float y, the y position.
         */
		virtual void draw(float x = 0, float y = 0);

		/** \brief Updates the graphic. */
		virtual void update();
	protected:
	private:
};
