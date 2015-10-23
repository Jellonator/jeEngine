#include "JE/JE.h"
#include <iostream>

int main(int argc, char** argv){
	JE::initWindow("Hello", 640, 480);
	JE::GRAPHICS::Spritemap spritemap("test.png");	
	JE::GRAPHICS::Anim& anim = spritemap.newAnim("foo", 2.0f);
	spritemap.newFrame(16, 0, 32, 32, 1.0f);
	JE::TIME::setDeltaTimeLimit();
	
	for (int i = 0; i < 4; ++i){
		unsigned int frame_id = spritemap.newFrame(i*32, 0, 32, 32);
		anim.addFrame(frame_id);
		//frame.setSize(i*32, 0, 8, 32);
		//std::cout << "Anim has frames: " << anim.getFrameCount() << std::endl;
		std::cout << "ID of new frame: " << frame_id << std::endl;
	}
	spritemap.play("foo");
	
	JE::GRAPHICS::Emitter emitter;
	JE::GRAPHICS::EmitterType& emitter_basic = emitter.newType("foo");
	emitter_basic.setSpeed(300, 400);
	emitter_basic.setAngle(60, 120);
	emitter_basic.setSlow(350);
	emitter_basic.setLife(10);
	emitter_basic.setPosition(-25, -25, 25, 25);
	emitter_basic.setAcceleration(450, -50, 450, 50);
	JE::GRAPHICS::Image image("sparkles.png");
	emitter_basic.setRenderer<JE::GRAPHICS::EmitterRendererSpritemap>(spritemap, "foo");
	
	JE::EVENT::Container ev_cont;
	std::shared_ptr<JE::EVENT::Quit> ev_quit = std::make_shared<JE::EVENT::Quit>();
	ev_cont.addEvent(ev_quit);
	
	float time = 0;
	while(!ev_quit->pressed){
		JE::update();
		ev_cont.poll();
		time -= JE::TIME::dt;
		while (time < 0){
			time += 0.01f;
			emitter.create("foo", 2, 100, 100);
		}
		spritemap.update(JE::TIME::dt);
		emitter.update(JE::TIME::dt);
		
		JE::GRAPHICS::draw();
		spritemap.draw();
		emitter.draw();
		JE::GRAPHICS::flip();
	}
	
	return 0;
}