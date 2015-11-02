#include "JE/JE.h"
#include "JE/jeMask.h"
#include "JE/jeEntity.h"
#include "JE/jeGroup.h"
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
		JE::MASK::Hitbox& hitbox = this->setMask<JE::MASK::Hitbox>(0,0,63,63);
		hitbox.moveTo(x, y);
	}
	void OnUpdate(JE::Group& group, float dt){
		if (ev_left->down ) this->getMask().moveBy(-5, 0);
		if (ev_up->down   ) this->getMask().moveBy( 0,-5);
		if (ev_right->down) this->getMask().moveBy( 5, 0);
		if (ev_down->down ) this->getMask().moveBy( 0, 5);
	}
	void OnDraw(){
		this->getMask().draw(this->getX(), this->getY());
	}
};

int main(int argc, char** argv){
	
	//return 0;
	JE::initWindow("Hello", 800, 608);
	
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
	
	//float time = 0;
	JE::MASK::Grid tile(0,0, 12,9, 8,8);
	tile.addNewType<JE::MASK::Hitbox>("full",       0,0, 7,7);
	tile.addNewType<JE::MASK::Hitbox>("half-top",   0,0, 7,3);
	tile.addNewType<JE::MASK::Hitbox>("half-bottom",0,4, 7,7);
	tile.addNewType<JE::MASK::Hitbox>("half-left",  0,0, 3,7);
	tile.addNewType<JE::MASK::Hitbox>("half-right", 4,0, 7,7);
	
	JE::MASK::Multimask& slope_bottom_left = tile.addNewType<JE::MASK::Multimask>("slope-bottom-left");
	JE::MASK::Multimask& slope_bottom_right = tile.addNewType<JE::MASK::Multimask>("slope-bottom-right");
	slope_bottom_left.generateFromPoints({{0,0}, {0,7}, {7,6}});
	slope_bottom_right.generateFromPoints({{7,0}, {0,7}, {7,7}});
	
	JE::Group world;
	
	MyPlayer& player = world.add<MyPlayer>(30,0);
	
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