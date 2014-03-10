#pragma once

#include "jeGraphic.h"
#include <string>
#include "jeData.h"
namespace JE{
	extern SDL_Renderer* renderer;
}
class jeImage;
class jeTexture : public jeData{
	public:
	jeTexture(void* owner = NULL);
	SDL_Texture* texture;
	virtual ~jeTexture();
	void load(std::string file, SDL_Renderer* renderer = JE::renderer);
};

class jeImage : public jeGraphic
{
	public:
		jeTexture* texture;/**< The texture. */
		SDL_RendererFlip flip;/**< Flipping. */
		SDL_Rect* clip;/**< Clipping rectangle. */
		float w;/**< The width of the image. */
		float h;/**< The height of the image. */
		jeImage();
		virtual ~jeImage();
        /** \brief Draw the image to the screen.
         * \param 0 float x, the X offset.
         * \param 0 float y, the Y offset.
         * \param NULL jeCamera* camera, the Camera.
         * \param NULL jeEntity* parent, the parent Entity.
         * \param JE::renderer SDL_Renderer* renderer, The renderer to use, defaults to the default renderer(JE::renderer)
         */
		virtual void draw(float x = 0, float y = 0, jeCamera* camera = NULL, jeEntity* parent = NULL, SDL_Renderer* renderer = JE::renderer);
        /** \brief Loads an image as a texture.
         * \param file std::string, the file to load.
         * \param JE::renderer SDL_Renderer* renderer, the renderer to use.
         */
		void load(std::string file, SDL_Renderer* renderer = JE::renderer);
        /** \brief Set the image clipping.
         * \param x float, the x position.
         * \param y float, the y position.
         * \param w float, the width.
         * \param h float, the height.
         */
		void setClip(float x, float y, float w, float h);
        /** \brief set the size of the image.
         * \param w float, the width.
         * \param h float, the height.
         */
		void setSize(float w, float h);
        /** \brief Set the scaling factor of the image.
         * \param x float, the X scale.
         * \param -1 float y, the Y scale, defaults to the X scale.
         */
		void setScale(float x, float y = -1);
		void useTexture(jeTexture* texture);
	protected:
	private:
};

jeImage* jeCopyImage(jeImage* image);
