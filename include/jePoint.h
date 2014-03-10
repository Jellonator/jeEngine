#pragma once
#include "JE.h"

class jePoint
{
	public:
		jePoint();
		virtual ~jePoint();
		float x;/**< \brief float x, the x position of the point. */
		float y;/**< \brief float y, the y position of the point. */
		float speed;
		float direction;
		float startX;
		float startY;
		float endX;
		float endY;
		float startSpeed;
		float time;
		void update(float dt);
		void setPos(float x, float y);
		void moveTo(float x, float y, float speed);
		void moveToT(float x, float y, float time);
		//void setSpeed(float speed);
		//void setDirection(float direction);
	protected:
	private:
};
