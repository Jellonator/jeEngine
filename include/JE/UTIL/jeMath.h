#pragma once
#include <cmath>
#include <algorithm>
namespace JE{
namespace MATH{
	extern float RAD;/**< \brief number to convert degrees to radians, i.e. radians = RAD*degrees. */
	extern float DEG;/**< \brief number to convert radians to degrees, i.e. degrees = DEG*radians. */
	extern float PI;
	inline bool isClose(float value1, float value2 = 0.0f, float epsilon = 1e-5){
		return (std::abs(value2 - value1) <= epsilon);
	}
  /** \brief returns either 1 or -1, depending on the number's sign. Returns 0 for 0.
   * \param num int the number to get the sign of
   */
	template<typename Type>
	int getSign(Type num){
		if (num == 0) return 0;
		return (num > 0) ? 1 : -1;
	}
  /** \brief returns a random number between a and b.
   * \param a float
   * \param b float
   */
	float random(float a, float b);
  /** \brief returns the distance between two points
   * \param x1 float the x of point 1
   * \param y1 float the y of point 1
   * \param x2 float the x of point 2
   * \param y2 float the y of point 2
   */
	float distance(float x1, float y1, float x2, float y2);
  /** \brief returns the distance between two points squared, faster for comparisons than JE::MATH::distance()
   * \param x1 float the x of point 1
   * \param y1 float the y of point 1
   * \param x2 float the x of point 2
   * \param y2 float the y of point 2
   */
	float squareDistance(float x1, float y1, float x2, float y2);
	/** \brief returns true if the distance between the two points is larger than 'distance,' otherwise, it will return false.
   * \param x1 float the x of point 1
   * \param y1 float the y of point 1
   * \param x2 float the x of point 2
   * \param y2 float the y of point 2
	 */
	bool compareDistanceFast(float x1, float y1, float x2, float y2, float distance);
  /** \brief returns the x coordinate of the point of distance and angle(yes I know this is confusing it's basically short for return std::cos(RAD*angle)*distance+x;)
   * \param angle float the angle of the coordinate
   * \param distance float the distance of the coordinate
   * \param x float the base of the coordinate
   */
	float Xangle(float angle, float distance, float x = 0);
  /** \brief returns the y coordinate of the point of distance and angle(yes I know this is confusing it's basically short for return std::sin(RAD*angle)*distance+y;)
   * \param angle float the angle of the coordinate
   * \param distance float the distance of the coordinate
   * \param y float the base of the coordinate
   */
	float Yangle(float angle, float distance, float y = 0);
  /** \brief value/100 chance to return true
   * \param value float chance to return true, 0 being no chance, 100 being 100% chance
   */
	bool chance(float value);
  /** \brief a/b chance to return true(e.g. chance(3, 4) has 75% chance)
   * \param a float the numerator
   * \param b float the denominator
   */
	bool chance(float a, float b);
  /** \brief returns the angle between two points
   * \param x1 float the x of point 1
   * \param y1 float the y of point 1
   * \param x2 float the x of point 2
   * \param y2 float the y of point 2
   */
	float getAngle(float x1, float y1, float x2, float y2);
  /** \brief takes a value and moves it closer to a desired value, smoothly
   * \param pos float the beginning position
   * \param to float the destination
   * \param speed float the speed to move the position
   * \param float minSpeed the mininum speed to move the position
   * \return float the new position
   */
	float smoothTween(float pos, float to, float speed, float minSpeed = 5);
	
	template<typename Type>
	Type linearTween(Type pos, Type to, Type speed){
		bool is_left = (pos < to);
		if (pos < to) pos += speed;
		else if (pos > to) pos -= speed;
		if (!is_left != !(pos < to)) pos = to;
		return pos;
	}
	
	template<typename Type>
	Type clamp(Type value, Type min, Type max){
		if (min > max) {std::swap(min, max);}
		if (value < min) return min;
		if (value > max) return max;
		return value;
	}
	template<typename Type>
	Type normalize(Type value, Type min, Type max, Type to_min = 0, Type to_max = 1, bool clamp = true){
		Type a = (to_max - to_min) / (max - min);
		Type b = to_max - a * max;
		value = a * value + b;
		if (clamp)return JE::MATH::clamp(value, to_min, to_max);
		return value;
	}
	template <typename Type>
	Type mod(Type value, Type divisor){
		return value - std::floor(value/divisor) * divisor;
	}
	template <typename Type>
	Type angleDifference(Type angle1, Type angle2){
		while (angle1 < 0) {
			angle1 += 360;
		}
		while (angle1 > 360) {
			angle1 -= 360;
		}
		while (angle2 < 0) {
			angle2 += 360;
		}
		while (angle2 > 360) {
			angle2 -= 360;
		}
		Type a = angle2 - angle1;
		a = JE::MATH::mod(a + (Type)180, (Type)360) - (Type)180;
		return std::abs(a);
	}
	template <typename Type>
	Type angleTo(Type from, Type to, Type speed){
		while (from < 0) {
			from += 360;
		}
		while (from > 360) {
			from -= 360;
		}
		while (to < 0) {
			to += 360;
		}
		while (to > 360) {
			to -= 360;
		}
		Type dis = JE::MATH::angleDifference(from, to);
		if (std::abs(dis) <= speed) {
			return to;
		}
		Type angle = from;
		if ((from > to && from < to + 180) || (from > to - 360 && from < to - 180) || (from > to + 360 && from < to + 540)) {
			angle -= speed;
		} else {
			angle += speed;
		}
		return angle;
	}
	template <typename Type>
	bool compareAngle(Type a, Type b){
		while (a < 0) {
			a += 360;
		}
		while (a > 360) {
			a -= 360;
		}
		while (b < 0) { 
			b += 360;
		}
		while (b > 360) {
			b -= 360;
		}
		return ((a > b && a < b + 180) || (a > b - 360 && a < b - 180) || (a > b + 360 && a < b + 540));
	}
	template <typename Type>
	Type angleMix(Type from, Type to, double mix){
		Type speed = JE::MATH::angleDifference(from, to) * mix;
		Type angle = from;
		angle = JE::MATH::angleTo(from, to, speed);
		return angle;
	}
};};
