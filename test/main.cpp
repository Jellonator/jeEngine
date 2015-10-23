#include "JE/JE.h"
#include <iostream>

int main(int argc, char** argv){
	JE::initWindow("Hello", 640, 480);
	JE::GRAPHICS::Spritemap spritemap("test.png");	
	JE::GRAPHICS::Anim& anim = spritemap.newAnim("foo");
	spritemap.newFrame(16, 0, 32, 32, 1.0f);
	
	for (int i = 0; i < 4; ++i){
		unsigned int frame_id = spritemap.newFrame(i*32, 0, 32, 32, 1.0f, i*3);
		anim.addFrame(frame_id);
		//frame.setSize(i*32, 0, 8, 32);
		//std::cout << "Anim has frames: " << anim.getFrameCount() << std::endl;
		std::cout << "ID of new frame: " << frame_id << std::endl;
	}
	spritemap.play("foo");
	
	JE::GRAPHICS::Emitter emitter;
	JE::GRAPHICS::EmitterType& emitter_basic = emitter.newType("foo");
	emitter_basic.setSpeed(50, 200);
	
	JE::EVENT::Container ev_cont;
	std::shared_ptr<JE::EVENT::Quit> ev_quit = std::make_shared<JE::EVENT::Quit>();
	ev_cont.addEvent(ev_quit);
	
	float time = 0;
	while(!ev_quit->pressed){
		JE::update();
		ev_cont.poll();
		time -= JE::TIME::dt;
		while (time < 0){
			time += 0.1f;
			emitter.create("foo", 1, 100, 100);
		}
		spritemap.update(JE::TIME::dt);
		emitter.update(JE::TIME::dt);
		
		JE::GRAPHICS::draw();
		spritemap.draw();
		JE::GRAPHICS::flip();
	}
	
	return 0;
}