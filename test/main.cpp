#include "JE/JE.h"
#include "JE/jeMask.h"
#include "JE/MASK/jeHitbox.h"
#include <iostream>
#include <vector>

void drawTile(int x, int y, int r, int g, int b, bool fill = true){
	JE::GRAPHICS::setColor(r, g, b);
	JE::GRAPHICS::drawRect(x * 64 + 8, y * 64 + 8, 48, 48, fill);
}

void drawHitbox(JE::MASK::Hitbox& box, int r, int g, int b){
	JE::GRAPHICS::setColor(r, g, b);
	JE::GRAPHICS::drawRect(
		box.getLeft() * 64 + 8, 
		box.getTop() * 64 + 8, 
		48 + 64 * (box.getWidth() - 1), 
		48 + 64 * (box.getHeight() - 1), 
		true
	);
	drawTile(box.getX(), box.getY(), (r + 64) % 255, (g + 64) % 255, (b + 64) % 255, false);
}

int main(int argc, char** argv){
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
	JE::MASK::Hitbox tile(-1, -1, 1, 1);
	tile.moveTo(6, 4);
	JE::MASK::Hitbox player(-1,1, 1, 4);
	
	while(!ev_quit->pressed){
		JE::update();
		ev_cont.poll();
		
		if (ev_up->pressed)    tile.getCollide(player,  0, -1, player.ptrX(), player.ptrY());
		if (ev_left->pressed)  tile.getCollide(player, -1,  0, player.ptrX(), player.ptrY());
		if (ev_down->pressed)  tile.getCollide(player,  0,  1, player.ptrX(), player.ptrY());
		if (ev_right->pressed) tile.getCollide(player,  1,  0, player.ptrX(), player.ptrY());
		
		JE::GRAPHICS::draw();
		drawHitbox(tile, tile.containsRect(player) ? 255 : 0, 0, 255);
		drawHitbox(player, 0, 255, 0);
		JE::GRAPHICS::flip();
	}
	
	return 0;
}