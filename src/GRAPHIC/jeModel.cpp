/*#include "jeModel.h"
namespace JE{namespace GRAPHICS{ModelPoint4D::ModelPoint4D(float x, float y, float z, float w){
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}
ModelElement::ModelElement(int a, int b, int c){
	this->a = a;
	this->b = b;
	this->c = c;
}
Model::Model(){
	//glGenBuffers(1, &this->vbo);
	//glGenBuffers(1, &this->ebo);
	//glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}
Model::~Model(){
	//dtor
}
void Model::addPoint(float x, float y, float z, float w){
	//this->points.push_back(ModelPoint4D(x, y, z, w));
	this->points.push_back(x);
	this->points.push_back(y);
	this->points.push_back(z);
	this->points.push_back(w);
}
void Model::addTriangle(int a, int b, int c){
	//this->elements.push_back(ModelElement(a, b, c));
	this->elements.push_back(a);
	this->elements.push_back(b);
	this->elements.push_back(c);
}
void Model::push(){
	GLfloat vertices[this->points.size()];
	std::copy(this->points.begin(), this->points.end(), vertices);
	//glBindBufferARB(GL_ARRAY_BUFFER, this->vbo);
	//glBufferDataARB(GL_ARRAY_BUFFER, sizeof(GLfloat) * this->points.size(), vertices, GL_STATIC_DRAW);

	GLuint tris[this->elements.size()];
	std::copy(this->elements.begin(), this->elements.end(), tris);
	//glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	//glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * this->elements.size(), tris, GL_STATIC_DRAW);
}
void Model::use(){
	//glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
}
};};*/
