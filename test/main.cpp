#include "JE/JE.h"
#include "JE/jeMask.h"
#include "JE/MASK/jeHitbox.h"
#include "JE/MASK/jeMultimask.h"
#include "JE/MASK/jeGrid.h"
#include <iostream>
#include <vector>
#include "JE/GRAPHIC/jeCamera.h"

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
	
	//tile.setRect("full", 2,4, 8,6);
	//tile.setRect("half-bottom", 3,4, 7,4);
	tile.setTile("slope-bottom-left", 3,4);
	tile.setTile("slope-bottom-right", 7,4);
	//tile.emptyRect(4,4, 6,4);
	
	JE::MASK::Multimask player(0,0);
	player.generateFromPoints({{0,-6}, {10,-2}, {5,8}, {12,12}, {-6,12}});
	
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
		
		JE::GRAPHICS::setColorF(1, 0, 0, 0.6);
		tile.draw(0, 0);
		JE::GRAPHICS::setColorF(0, 1, 0, 0.6);
		player.draw(0, 0);
		
		camera.pop();
		JE::GRAPHICS::flip();
	}
	
	return 0;
}