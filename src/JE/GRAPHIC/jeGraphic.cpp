#include "JE/UTIL/jeMath.h"
#include "JE/jeWorld.h"
#include "JE/GRAPHIC/jeCamera.h"
#include "JE/GRAPHIC/jeGraphic.h"
#include "JE/GRAPHIC/jeImage.h"
namespace JE{
Graphic::Graphic(float x, float y)
{
	this->x = x;
	this->y = y;
	this->angle = 0;
	this->ox = 0;
	this->oy = 0;
}

Graphic::~Graphic()
{

}

//void Graphic::drawExt(float x, float y, GRAPHICS::Camera* camera, Entity* entity, float angle, SDL_Renderer* renderer){}
void Graphic::draw(float x, float y, float angle, const std::shared_ptr<Entity>& entity){}
void Graphic::update(){}

void Graphic::setOrigin(float x, float y, bool adjustPosition){
	this->ox = x;
	this->oy = y;
	if (adjustPosition) this->set(-x, -y);
}
namespace GRAPHICS{
SDL_Window* window;
SDL_Renderer* renderer;
SDL_GLContext glcontext;
Color backcolor;
Color forecolor;
void flip(){
	SDL_GL_SwapWindow(window);
	//SDL_RenderPresent(renderer);
	glLoadIdentity();
	glClearColor(backcolor.r, backcolor.g, backcolor.b, backcolor.a);
	/* Clear The Screen And The Depth Buffer */
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}
void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a){
	/*forecolor.r = r;
	forecolor.g = g;
	forecolor.b = b;
	forecolor.a = a;
	SDL_SetRenderDrawColor(renderer, r, g, b, a);*/
	setColorF(float(r)/255.0f, float(g)/255.0f, float(b)/255.0f, float(a)/255.0f);
}
void setColorF(float r, float g, float b, float a){
	//setColor(r*255,g*255,b*255,a*255,renderer);
	forecolor.r = r;
	forecolor.g = g;
	forecolor.b = b;
	forecolor.a = a;
}
void setBackgroundColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a){
	setBackgroundColorF(float(r)/255.0f, float(g)/255.0f, float(b)/255.0f, float(a)/255.0f);
}
void setBackgroundColorF(float r, float g, float b, float a){
	backcolor.r = r;
	backcolor.g = g;
	backcolor.b = b;
	backcolor.a = a;
}
void drawRect(float x, float y, float w, float h, bool fill){
	glBegin( fill ? GL_QUADS : GL_LINE_LOOP );            /* Draw A Quad */
		glColor4f(forecolor.r, forecolor.g, forecolor.b, forecolor.a);
		glVertex3f( x  , y+h, 0.0f ); /* Bottom Left */
		glVertex3f( x+w, y+h, 0.0f ); /* Bottom Right */
		glVertex3f( x+w, y  , 0.0f ); /* Top Right */
		glVertex3f( x  , y  , 0.0f ); /* Top Left */
	glEnd( );
}

void drawRect(float x, float y, float w, float h, float angle, bool fill){
	drawRect(x, y, w, h, angle, w / 2, h / 2, fill);
}
void drawRect(float x, float y, float w, float h, float angle, float originx, float originy, bool fill){
	{
		float mat[16];
		glGetFloatv(GL_PROJECTION_MATRIX, mat);
		float x_move = mat[12] + x + originx;
		float y_move = mat[13] + y + originy;
		float z_move = mat[14];
		glPushMatrix();
		glTranslatef( x_move, y_move, z_move);
		glRotatef(angle, 0, 0, 1.0);
		glTranslatef(-x_move,-y_move,-z_move);
	}
	
	glBegin( fill ? GL_QUADS : GL_LINE_LOOP );
		glColor4f(forecolor.r, forecolor.g, forecolor.b, forecolor.a);
		glVertex3f( x  , y  , 0.0f );
		glVertex3f( x+w, y  , 0.0f );
		glVertex3f( x+w, y+h, 0.0f );
		glVertex3f( x  , y+h, 0.0f );
	glEnd( );
	
	glPopMatrix();
}

void drawLine(float x1, float y1, float x2, float y2){
	glBegin(GL_LINES);
		glColor4f(forecolor.r, forecolor.g, forecolor.b, forecolor.a);
		glVertex3f( x1, y1, 0.0f);
		//glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
		glVertex3f( x2, y2, 0.0f);
	glEnd();
}

void drawCircle(float x, float y, float radius, int points, bool fill){
	if (points <= 2) return;
	glBegin(fill ? GL_POLYGON : GL_LINE_LOOP);
		glColor4f(forecolor.r, forecolor.g, forecolor.b, forecolor.a);
		for (int i = 0; i < points; i ++){
			float a = float(i) / float(points) * 360;
			glVertex3f(JE::MATH::Xangle(a, radius, x), JE::MATH::Yangle(a, radius, y), 0.0f);
		}
	glEnd();
}

void drawImgRectStretch(const std::shared_ptr<Image>& image, float x, float y, float w, float h,
	float tileWidth, float tileHeight, const std::shared_ptr<Entity>& entity){
//store texture width
	int tw, th;
	image->texture->getSize(&tw, &th);
	//make sure image is big enough
	if (tw >= tileWidth*2 && th >= tileHeight*2){
	//store temporary information
		SDL_Rect temprect = image->clip;
		bool tempbool = image->use_clip;
		float tempWidth = image->width;
		float tempHeight = image->height;
		//Set size to corner
		image->setSize(tileWidth,tileHeight);
	//Drawing operations
		//upper left
		image->setClip(0,0,tileWidth,tileHeight);
		image->draw(x, y, 0, entity);
		//upper right
		image->setClip(tw-tileWidth, 0,tileWidth,tileHeight);
		image->draw(x+w-tileWidth, y, 0, entity);
		//lower left
		image->setClip(0,th-tileHeight, tileWidth,tileHeight);
		image->draw(x, y+h-tileHeight, 0, entity);
		//lower right
		image->setClip(tw-tileWidth, th-tileHeight,tileWidth,tileHeight);
		image->draw(x+w-tileWidth, y+h-tileHeight, 0, entity);
	//Now draw the sides
	//top/bottom size
		if (h > tileHeight*2){
			image->setSize(w-tileWidth*2,tileHeight);
			//top side
			image->setClip(tileWidth,0,tw-tileWidth*2,tileHeight);
			image->draw(x+tileWidth,y, 0, entity);
			//bottom side
			image->setClip(tileWidth,th-tileHeight,tw-tileWidth*2,tileHeight);
			image->draw(x+tileWidth,y+h-tileHeight, 0, entity);
		}
	//left/right sizes
		if (w > tileWidth*2){
			image->setSize(tileWidth, h-tileHeight*2);
			//left side
			image->setClip(0,tileHeight,tileWidth,tw-tileHeight*2);
			image->draw(x,y+tileHeight, 0, entity);
			//right side
			image->setClip(tw-tileWidth,tileHeight,tileWidth,tw-tileHeight*2);
			image->draw(x+w-tileWidth,y+tileHeight, 0, entity);
		}
	//and the center
		if (h > tileHeight*2 && w > tileWidth*2){
			image->setSize(w-tileWidth*2,h-tileHeight*2);
			image->setClip(tileWidth,tileHeight,tw-tileWidth*2,th-tileHeight*2);
			image->draw(x+tileWidth,y+tileHeight, 0, entity);
		}
	//Reset image
		image->clip = temprect;
		image->width = tempWidth;
		image->height = tempHeight;
		image->use_clip = tempbool;
	}
}
}
}
