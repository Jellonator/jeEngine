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
	this->points.push_back(new ModelPoint4D(x, y, z, w));
}
void Model::addElement(int a, int b, int c){
	this->elements.push_back(new ModelElement(a, b, c));
}
void Model::push(){std::cout << std::endl;
	//vertices
	GLfloat vertices[this->points.size()*4];
	for (int i = 0; i < this->points.size(); i ++){
		vertices[i*4+0] = this->points[i]->x;
		vertices[i*4+1] = this->points[i]->y;
		vertices[i*4+2] = this->points[i]->z;
		vertices[i*4+3] = this->points[i]->w;
		//std::cout << this->points[i]->x << ", " << this->points[i]->y << ", " << this->points[i]->z << ", " << this->points[i]->w << std::endl;
	}
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//elements
	std::cout << std::endl;
	GLuint telements[this->elements.size()*3];
	for (int i = 0; i < this->elements.size(); i ++){
		telements[i*3+0] = this->elements[i]->a;
		telements[i*3+1] = this->elements[i]->b;
		telements[i*3+2] = this->elements[i]->c;
		//std::cout << this->elements[i]->a << ", " << this->elements[i]->b << ", " << this->elements[i]->c << std::endl;
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(telements), telements, GL_STATIC_DRAW);*
}
void Model::use(){
	//glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
}
};};*/
