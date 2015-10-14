/*#pragma once
#include <vector>
#include "jeMain.h"
#include "jeShader.h"
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
		std::vector<GLfloat> points;
		std::vector<GLuint> elements;
		GLuint vbo;
		GLuint ebo;
		void addPoint(float x, float y, float z, float w = 1);
		void addTriangle(int a, int b, int c);
		void use();
		void push();
		Model();
		virtual ~Model();
	protected:
	private:
};
};};
*/
