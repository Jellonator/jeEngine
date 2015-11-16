#pragma once
namespace JE{
extern float dt;
class Point
{
	public:
		Point(float x = 0, float y = 0);
		Point(const JE::Point& point);
		
		virtual ~Point();
		float x;/**< \brief float x, the x position of the point. */
		float y;/**< \brief float y, the y position of the point. */
		bool moveToSmooth(float x, float y, float speed = 20, float dt = dt, float snap = 1, float dead = 0);
		bool moveToLinear(float x, float y, float speed = 20, float dt = dt, float snap = 1, float dead = 0);
		
		void set(float x, float y);
		void setX(float value);
		void setY(float value);
		
		float getX() const;
		float getY() const;
		void getAsInt(int* x, int* y) const;
		
		//math operations
		void operator +=(const JE::Point& point);
		void operator -=(const JE::Point& point);
		void operator *=(const JE::Point& point);
		void operator /=(const JE::Point& point);
		void operator  =(const JE::Point& point);
		
		void modulate(float value);
		
		bool operator ==(const JE::Point& point);
		bool operator !=(const JE::Point& point);
	protected:
	private:
};
};
