#pragma once
#include "jeGraphic.h"
#include <string>
#include <memory>

/*
namespace JE{namespace GRAPHICS{

class Image : public Graphic
{
	public:
		std::shared_ptr<Texture> texture;
		//SDL_RendererFlip flip;
		int flip_x;
		int flip_y;
		SDL_Rect clip;
		bool use_clip;
		float width;
		float height;
		Image();
		Image(std::string file);
		virtual ~Image();
		virtual void draw(float x = 0, float y = 0, float angle = 0);
		void load(std::string file, SDL_Renderer* renderer = renderer);
		void setClip(float x, float y, float w, float h);
		void setSize(float w, float h);
		void disableSize();
		void setScale(float x, float y = -1);
		void useTexture(std::shared_ptr<Texture> texture);
		void useTexture(const std::shared_ptr<Image>& image);
		void centerOrigin();
		void setColor(int r, int g, int b, int a = 255);
		void getSize(int* width, int* height);
		void drawSection(float x, float y, int section_x, int section_y, int section_width, int section_height);
		void setFlip(bool x, bool y);
	protected:
	private:
};
};};
*/