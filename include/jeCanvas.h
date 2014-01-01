#pragma once
#include "jeImage.h"

class jeCanvas : public jeImage
{
	public:
        /** \brief A graphical class you can draw to, and then display later.
         * \param width int, The width of the canvas.
         * \param height int, The height of the canvas
         */
		jeCanvas(int width, int height);
		virtual ~jeCanvas();
		void bind();/**< \brief Begin drawing operations. */
		void unbind();/**< \brief Stop drawing operations. */
	protected:
	private:
};
