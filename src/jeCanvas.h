#pragma once
#include "jeImage.h"
namespace JE{namespace GRAPHICS{
class Canvas : public Image
{
	public:
        /** \brief A graphical class you can draw to, and then display later.
         * \param width int, The width of the canvas.
         * \param height int, The height of the canvas
         */
		Canvas(int width, int height);
		virtual ~Canvas();
		void bind();/**< \brief Begin drawing operations. */
		void unbind();/**< \brief Stop drawing operations. */
	protected:
	private:
};
};};
