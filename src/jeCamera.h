#pragma once
#include "JE.h"
namespace JE{namespace GRAPHICS{
class Camera : public Point
{
	public:
		SDL_Rect* clip;
		float sx, sy;
		SDL_Point* size;

		Camera();
		virtual ~Camera();

		void setScale(float x, float y=-1);
		void pushScale(float x, float y=-1);
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

		//void moveTo(float x, float y, float step = JE::dt);
		//void moveToShake(float x, float y, float range, float intensity, float step = JE::dt);
	protected:
	private:
};
};};
