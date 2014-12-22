/*#pragma once
#include "JE.h"
namespace JE{namespace GRAPHICS{
class Program;
struct ModelElement{
	ModelElement(int a, int b, int c);
	int a;
	int b;
	int c;
};
struct ModelPoint4D{
	ModelPoint4D(float x, float y, float z, float w);
	float x;
	float y;
	float z;
	float w;
};
class Model{
	public:
		std::vector<ModelPoint4D*> points;
		std::vector<ModelElement*> elements;
		GLuint vbo;
		GLuint ebo;
		void addPoint(float x, float y, float z, float w = 1);
		void addElement(int a, int b, int c);
		void use();
		void push();
		Model();
		virtual ~Model();
	protected:
	private:
};
};};
*/
