#pragma once
#include "jeGraphic.h"
#include <string>
#include <memory>

namespace JE{namespace GRAPHICS{
extern SDL_Renderer* renderer;
class Image;
class Texture{
public:
	Texture(SDL_Texture* tex);
	Texture(std::string file);
	virtual ~Texture();
	void getSize(int* width, int* height);
	SDL_Texture* get() const;
	void set(SDL_Texture* tex);
	void load(std::string file, SDL_Renderer* renderer = renderer);
private:
	SDL_Texture* texture;
};
class Image : public Graphic
{
	public:
		std::shared_ptr<Texture> texture;/**< The texture. */
		//SDL_RendererFlip flip;/**< Flipping. */
		int flip_x;
		int flip_y;
		SDL_Rect clip;/**< Clipping rectangle. */
		bool use_clip;
		float width;/**< The width of the image. */
		float height;/**< The height of the image. */
		Image();
		Image(std::string file);
		virtual ~Image();
        /** \brief Draw the image to the screen.
         * \param float x, the X offset.
         * \param float y, the Y offset.
         * \param Camera* camera, the Camera.
         * \param Entity* parent, the parent Entity.
         * \param SDL_Renderer* renderer, The renderer to use, defaults to the default renderer(JE::renderer)
         */
		//virtual void drawExt(float x = 0, float y = 0, Camera* camera = NULL, Entity* parent = NULL, float angle = 0, SDL_Renderer* renderer = renderer);
		virtual void draw(float x = 0, float y = 0, float angle = 0, const std::shared_ptr<Entity>& parent = NULL);
        /** \brief Loads an image as a texture.
         * \param file std::string, the file to load.
         * \param JE::renderer SDL_Renderer* renderer, the renderer to use.
         */
		void load(std::string file, SDL_Renderer* renderer = renderer);
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
		void disableSize();
        /** \brief Set the scaling factor of the image.
         * \param x float, the X scale.
         * \param -1 float y, the Y scale, defaults to the X scale.
         */
		void setScale(float x, float y = -1);
				/** \brief sets the image's texture to a new texture
				 * \param texture Texture* the new texture of the image
				 */
		void useTexture(std::shared_ptr<Texture> texture);
		void useTexture(const std::shared_ptr<Image>& image);
		void centerOrigin();
		void setColor(int r, int g, int b, int a = 255);
		void getSize(int* width, int* height);
		void drawSection(float x, float y, int section_x, int section_y, int section_width, int section_height,
		const std::shared_ptr<Entity>& entity = NULL);
		void setFlip(bool x, bool y);
	protected:
	private:
};
Image* copyImage(Image* image);
};};
