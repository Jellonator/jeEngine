#pragma once
namespace JE{
extern float dt;
class Point
{
	public:
		Point(float x = 0, float y = 0);
		virtual ~Point();
		float x;/**< \brief float x, the x position of the point. */
		float y;/**< \brief float y, the y position of the point. */
		/*float speed;
		float direction;
		float startX;
		float startY;
		float endX;
		float endY;
		float startSpeed;
		float time;
		void update(float dt);
		void setPos(float x, float y);*/
		bool moveToSmooth(float x, float y, float speed = 20, float dt = dt, float snap = 1, float dead = 0);
		bool moveToLinear(float x, float y, float speed = 20, float dt = dt, float snap = 1, float dead = 0);
		void set(float x, float y);
		float getX() const;
		float getY() const;
		//void moveTo(float x, float y);
		//void setSpeed(float speed);
		//void setDirection(float direction);
	protected:
	private:
};
};
