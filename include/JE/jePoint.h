#pragma once
namespace JE{
extern float dt;
class Point
{
	public:
		Point(float x = 0, float y = 0);
		Point(const JE::Point& point);
		
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
		
		//math operations with other point
		void operator +=(const JE::Point& point);
		void operator -=(const JE::Point& point);
		void operator *=(const JE::Point& point);
		void operator /=(const JE::Point& point);
		void operator  =(const JE::Point& point);
		
		friend JE::Point operator +(const JE::Point& a, const JE::Point& b);
		friend JE::Point operator -(const JE::Point& a, const JE::Point& b);
		friend JE::Point operator *(const JE::Point& a, const JE::Point& b);
		friend JE::Point operator /(const JE::Point& a, const JE::Point& b);
		friend JE::Point operator !(const JE::Point& a);
		friend bool operator !=(const JE::Point& a, const JE::Point& b);
		friend bool operator ==(const JE::Point& a, const JE::Point& b);
		
		//math operations with numbers
		friend JE::Point operator *(const JE::Point& a, float b);
		friend JE::Point operator /(const JE::Point& a, float b);
		friend JE::Point operator *(float a, const JE::Point& b);
		friend JE::Point operator /(float a, const JE::Point& b);
		void operator *=(float value);
		void operator /=(float value);
		void modulate(float value);
		
		//distance
		float getDistance();
		float getDistance(float x, float y);
		float getDistance(JE::Point& p);
		
	protected:
	private:
};
};
