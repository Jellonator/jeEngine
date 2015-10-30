#include "JE/JE.h"
#include "JE/jeMask.h"
#include "JE/MASK/jeHitbox.h"
#include "JE/MASK/jeMultimask.h"
#include <iostream>
#include <vector>
#include "JE/GRAPHIC/jeCamera.h"

class MyBase{
	
};

class MyChild{
	
};

int main(int argc, char** argv){
	
	//return 0;
	JE::initWindow("Hello", 800, 608);
	
	JE::EVENT::Container ev_cont;
	std::shared_ptr<JE::EVENT::Quit> ev_quit = std::make_shared<JE::EVENT::Quit>();
	std::shared_ptr<JE::EVENT::Keyboard> ev_up = std::make_shared<JE::EVENT::Keyboard>(SDLK_UP, true);
	std::shared_ptr<JE::EVENT::Keyboard> ev_left = std::make_shared<JE::EVENT::Keyboard>(SDLK_LEFT, true);
	std::shared_ptr<JE::EVENT::Keyboard> ev_down = std::make_shared<JE::EVENT::Keyboard>(SDLK_DOWN, true);
	std::shared_ptr<JE::EVENT::Keyboard> ev_right = std::make_shared<JE::EVENT::Keyboard>(SDLK_RIGHT, true);
	ev_cont.addEvent(ev_quit);
	ev_cont.addEvent(ev_up);
	ev_cont.addEvent(ev_left);
	ev_cont.addEvent(ev_down);
	ev_cont.addEvent(ev_right);
	
	//float time = 0;
	JE::MASK::Multimask tile(32, 32);
	tile.generateFromPoints(0,0, 15,0, 0,31);
	JE::MASK::Multimask player(0,0);
	player.generateFromPoints(0,-6, 6,4, -6,4);
	
	JE::GRAPHICS::Camera camera;
	camera.setScale(8);
	
	while(!ev_quit->pressed){
		JE::update();
		ev_cont.poll();
		
		if (ev_up->pressed)    tile.getCollide(player,  0, -1, player.ptrX(), player.ptrY());
		if (ev_left->pressed)  tile.getCollide(player, -1,  0, player.ptrX(), player.ptrY());
		if (ev_down->pressed)  tile.getCollide(player,  0,  1, player.ptrX(), player.ptrY());
		if (ev_right->pressed) tile.getCollide(player,  1,  0, player.ptrX(), player.ptrY());
		
		JE::GRAPHICS::draw();
		camera.push();
		
		JE::GRAPHICS::setColorF(1, 0, 0);
		tile.draw(0, 0);
		JE::GRAPHICS::setColorF(0, 1, 0);
		player.draw(0, 0);
		
		camera.pop();
		JE::GRAPHICS::flip();
	}
	
	return 0;
}