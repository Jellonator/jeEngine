#include "JE/JE.h"
#include "JE/jeMask.h"
#include "JE/jeEntity.h"
#include "JE/jeGroup.h"
#include "JE/GRAPHIC/jeGraphic.h"
#include "JE/MASK/jeHitbox.h"
#include "JE/MASK/jeMultimask.h"
#include "JE/MASK/jeGrid.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "JE/GRAPHIC/jeCamera.h"

JE::EVENT::Container ev_cont;
std::shared_ptr<JE::EVENT::Quit> ev_quit;
std::shared_ptr<JE::EVENT::Keyboard> ev_up;
std::shared_ptr<JE::EVENT::Keyboard> ev_left;
std::shared_ptr<JE::EVENT::Keyboard> ev_down;
std::shared_ptr<JE::EVENT::Keyboard> ev_right;

class MyPlayer : public JE::Entity{
public:
	MyPlayer(int x, int y) : JE::Entity(){
		JE::MASK::Grid& hitbox = this->setMask<JE::MASK::Grid>(0,0, 100,100, 4,4);
		hitbox.addNewType<JE::MASK::Hitbox>("solid", 0, 0, 3, 3);
		hitbox.generateFromPoints("solid", {{0,-10}, {2,-2}, {10,0}, {2,2}, {0,10}, {-2,2}, {-10,0}, {-2,-2}}, 10, 10);
		hitbox.updateGetters();
	}
	void OnUpdate(JE::Group& group, float dt){
		int speed = 5;
		int move_x = 0;
		int move_y = 0;
		if (ev_left->down ) move_x = -speed;
		if (ev_up->down   ) move_y = -speed;
		if (ev_right->down) move_x =  speed;
		if (ev_down->down ) move_y =  speed;
		
		group.getCollideEntityGroup(*this, move_x, move_y, this->getMask()->ptrX(), this->getMask()->ptrY(), "solid");
	}
	void OnDraw(){
		JE::GRAPHICS::setColor(0,255,0);
		this->getMask()->draw(0, 0);
	}
};

class MySolid : public JE::Entity {
public:
	MySolid(int x, int y, int w, int h) : JE::Entity(){
		this->setMask<JE::MASK::Hitbox>(x, y, x+w-1, y+h-1);
	}
	void OnAdd(JE::Group& group){
		group.addToGroup("solid", *this);
	}
	void OnDraw(){
		JE::GRAPHICS::setColor(255,0,0);
		this->getMask()->draw(0, 0);
	}
};

class MyNonSolid : public JE::Entity {
public:
	MyNonSolid(int x, int y, int w, int h) : JE::Entity(){
		this->setMask<JE::MASK::Hitbox>(x, y, x+w-1, y+h-1);
		this->setLayer(-10);
	}
	void OnDraw(){
		JE::GRAPHICS::setColor(50,50,50);
		this->getMask()->draw(0, 0);
	}
};

class MyGrid : public JE::Entity {
public:
	MyGrid() : JE::Entity(){
		JE::MASK::Grid& grid = this->setMask<JE::MASK::Grid>(0,0, 25, 19, 32,32);
		grid.addNewType<JE::MASK::Hitbox>("solid", 0,0, 31,31);
		//25 x 19
		grid.setRect("solid", 0,16, 24,18);
		grid.setRect("solid", 4,10, 20,11);
		grid.emptyRect(2,16, 22,17);
		grid.emptyRect(6,10, 18,10);
	}
	void OnAdd(JE::Group& group){
		group.addToGroup("solid", *this);
	}
	void OnDraw(){
		JE::GRAPHICS::setColor(200, 0, 0);
		this->getMask()->draw(0, 0);
	}
};

int main(int argc, char** argv){
	
	//return 0;
	JE::initWindow("Hello", 800, 608);
	JE::TIME::printFPS = true;
	
	ev_quit = std::make_shared<JE::EVENT::Quit>();
	ev_up = std::make_shared<JE::EVENT::Keyboard>(SDLK_UP);
	ev_left = std::make_shared<JE::EVENT::Keyboard>(SDLK_LEFT);
	ev_down = std::make_shared<JE::EVENT::Keyboard>(SDLK_DOWN);
	ev_right = std::make_shared<JE::EVENT::Keyboard>(SDLK_RIGHT);
	ev_cont.addEvent(ev_quit);
	ev_cont.addEvent(ev_up);
	ev_cont.addEvent(ev_left);
	ev_cont.addEvent(ev_down);
	ev_cont.addEvent(ev_right);
	
	JE::Group world;
	
	MyPlayer& player = world.add<MyPlayer>(30,0);
	world.add<MySolid>(100,100, 200,100);
	world.add<MySolid>(500,300, 100,200);
	world.add<MyNonSolid>(100,100, 200,200);
	world.add<MyNonSolid>(400,300, 200,200);
	world.add<MyGrid>();
	
	float time = 0;
	float inv_fps = 1.0f/60.0f;
	int maximum_frame_buildup = 3;
	while(!ev_quit->pressed){
		
		JE::update();
		time += JE::TIME::dt;
		time = std::min(time, maximum_frame_buildup * inv_fps);
		while (time >= inv_fps){
			ev_cont.poll();
			world.update(inv_fps);
			time -= inv_fps;
		}
		
		JE::GRAPHICS::draw();
		//camera.push();
		world.draw();
		//6camera.pop();
		JE::GRAPHICS::flip();
	}
	
	return 0;
}