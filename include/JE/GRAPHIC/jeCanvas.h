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
		void clear();
				/** \brief resizes the canvas
				 * \param width int the new width of the canvas.
				 * \param height int the new height of the canvas.
				 * \return bool whether the canvas actually resized. If it did, you may want to re-render.
				 */
		bool resize(int width, int height);
		bool binded;
		void setPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
		void setPixelf(int x, int y, float r, float g, float b, float a = 1.0);
	protected:
	private:
		void setPixelp(int x, int y);
};
};};
