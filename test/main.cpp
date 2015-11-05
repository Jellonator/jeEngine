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
	int velocity_x;
	int velocity_y;
	int gravity_x;
	int gravity_y;
	float draw_pos_speed;
	int max_speed;
	int move_speed;
	int terminal_velocity;
	int jump_speed;
	int friction;
	bool is_jumping;
	
	JE::Point draw_pos;
	MyPlayer(int x, int y) : JE::Entity(){
		/*JE::MASK::Hitbox& hitbox = */
		this->setMask<JE::MASK::Hitbox>(0,0,63,63);
		this->velocity_x = 0;
		this->velocity_y = 0;
		this->gravity_x = 0;
		this->gravity_y = 2;
		this->draw_pos_speed = 0;
		this->max_speed = 10;
		this->terminal_velocity = 16;
		this->jump_speed = 35;
		this->move_speed = 1;
		this->friction = 3;
		this->is_jumping = false;
		
		this->draw_pos.set(x, y);
	}
	
	void OnUpdate(JE::Group& group, float dt){
		//Gravity
		this->velocity_y += this->gravity_y;
		
		//Terminal velocity
		if (this->velocity_y > this->terminal_velocity) this->velocity_y = terminal_velocity;
		
		//Left and Right movement
		if (ev_left->down) {
			this->velocity_x = -move_speed;
			
		} else if (ev_right->down) {
			this->velocity_x = +move_speed;
			
		} else {
			this->velocity_x = 0;
		}
		
		//Left and Right limit
		this->velocity_x = JE::MATH::clamp(this->velocity_x, -this->max_speed, +this->max_speed);
		
		if(ev_up->released){
			if (this->velocity_y < -this->terminal_velocity){
				this->velocity_y = -this->terminal_velocity;
			}
			this->is_jumping = false;
			this->gravity_y = 6;
			
		} else if (this->velocity_y > 0){
			this->is_jumping = false;
			this->gravity_y = 4;
		}
		
		//Get movement
		int move_x = this->velocity_x;
		int move_y = JE::MATH::clamp(this->velocity_y, -this->terminal_velocity, this->terminal_velocity);
		
		//Stop on wall
//		if (this->velocity_x > 0 && group.getCollideEntityGroup(*this, 1, 0, nullptr, nullptr, "solid")){
//			this->velocity_x = 0;
//		}
//		if (this->velocity_x < 0 && group.getCollideEntityGroup(*this,-1, 0, nullptr, nullptr, "solid")){
//			this->velocity_x = 0;
//		}
		
		bool on_ground = false;
		if (group.getCollideEntityGroup(*this, 0, 1, nullptr, nullptr, "solid")){
			if (this->velocity_y >= 0) {
				this->velocity_y = 0;
			}
			
			on_ground = true;
			
			//Jumping
			if (ev_up->pressed) {
				this->velocity_y = -this->jump_speed;
				this->gravity_y = 2;
				this->is_jumping = true;
			}
		}
		if (this->velocity_y < 0 && group.getCollideEntityGroup(*this, 0,-1, nullptr, nullptr, "solid")){
			this->velocity_y = 0;
		}
		
		//set drawing position to previous position
		this->draw_pos.set(this->getMask()->getX(), this->getMask()->getY());
		
		//Do movement
		if (on_ground){
			group.getCollideEntityGroup(*this, 0, -4, this->getMask()->ptrX(), this->getMask()->ptrY(), "solid");
		}
		
		group.getCollideEntityGroup(*this, move_x, move_y, this->getMask()->ptrX(), this->getMask()->ptrY(), "solid");
		
		if (on_ground){
			group.getCollideEntityGroup(*this, 0,  4, this->getMask()->ptrX(), this->getMask()->ptrY(), "solid");
		}
		
//		if (on_ground && group.getCollideEntityGroup(*this, 0,std::abs(move_x)*2, nullptr, nullptr, "solid")){
//			group.getCollideEntityGroup(*this, 0, std::abs(move_x)*2+1, this->getMask()->ptrX(), this->getMask()->ptrY(), "solid");
//		}
		
		//Set draw movement speed
		this->draw_pos_speed = JE::MATH::distance(
			(float)this->draw_pos.getX(), (float)this->draw_pos.getY(), 
			(float)this->getMask()->getX(), (float)this->getMask()->getY()
		) / dt;
	}
	void OnDraw(){
		this->draw_pos.moveToLinear(this->getMask()->getX(), this->getMask()->getY(), this->draw_pos_speed, JE::TIME::dt, 0.1f);
		JE::GRAPHICS::setColor(0,255,0);
		//this->getMask()->draw(0, 0);
		JE::GRAPHICS::drawRect(this->draw_pos.getX(), this->draw_pos.getY(), 64, 64, true);
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
		{//Bottom left slope
			JE::MASK::Grid& grid_tile = grid.addNewType<JE::MASK::Grid>("bottom-left", 0,0, 32,32, 1,1);
			grid_tile.addNewType<JE::MASK::PointMask>("solid");
			grid_tile.generateFromPoints("solid", {{0,0}, {31,31}}, 0, 0);
		}
		{//Bottom right slope
			JE::MASK::Grid& grid_tile = grid.addNewType<JE::MASK::Grid>("bottom-right", 0,0, 32,32, 1,1);
			grid_tile.addNewType<JE::MASK::PointMask>("solid");
			grid_tile.generateFromPoints("solid", {{0,31}, {31,0}}, 0, 0);
		}
		
		//25 x 19
		grid.setRect("solid", 0,16, 24,18);
		grid.emptyRect(4,16, 20,17);
		
		grid.setRect("solid", 6,10, 18,11);
		grid.emptyRect(8,10, 16,10);
		grid.setTile("bottom-left", 8, 10);
		grid.setTile("bottom-right", 16, 10);
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
//	world.add<MySolid>(100,100, 200,100);
//	world.add<MySolid>(500,300, 100,200);
//	world.add<MyNonSolid>(100,100, 200,200);
//	world.add<MyNonSolid>(400,300, 200,200);
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