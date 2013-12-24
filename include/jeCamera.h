#pragma once
#include "JE.h"
#ifdef _SDL_H

class jeCamera
{
	public:
		SDL_Rect* clip;
		float sx, sy;
		SDL_Point* size;
		float x, y;

		jeCamera();
		virtual ~jeCamera();

		void setScale(float x, float y);
		void setClip(float x, float y, float w, float h);
		void setPosition(float x, float y);
		void setSize(float w, float h);
		void disableSize();
		void disableClip();
		void reset();

		void zoom(float w, float h, float x = 0.5, float y = 0.5);
		void letterbox(float width, float height, float x = 0.5, float y = 0.5);

		void border(float x, float y = -1);

		void getRatio(float* x, float* y);
	protected:
	private:
};
#else
class jeCamera
{

}
#endif // _SDL_H
