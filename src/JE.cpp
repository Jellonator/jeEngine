#include "JE.h"
namespace JE{
void print(std::string s){std::cout << s << std::endl;}
namespace GRAPHICS{
	SDL_Window* window;
	SDL_Renderer* renderer;
	Color* backcolor;
	Color* forecolor;
	void draw(){
		SDL_SetRenderDrawColor(renderer,backcolor->r,backcolor->g,backcolor->b,backcolor->a);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer,forecolor->r,forecolor->g,forecolor->b,forecolor->a);
		world->draw();
	}
	void flip(){
		SDL_RenderPresent(renderer);
	}
};
namespace TIME{
	int time = 0;
	int frames = 0;
	float seconds = 0;
	int ptime = 0;
	float dt = 0;
	float fps = 0;
	float limit = -1;
	void setDeltaTimeLimit(float limit){
		JE::TIME::limit = limit;
	}
	void calculate(){
		//add 1 to frame count; get the time.
		frames ++;
		time = SDL_GetTicks();
		//calculate the delta time.
		dt = float(time - ptime)/1000;
		//if dt is non-zero
		if (dt != 0){
			//add dt to seconds, then calculate the FPS(This is why dt must be non-zero)
			seconds += dt;
		}
		//If a second has passed, then reset seconds and frames to 0.
		if (seconds > 1){
			fps = (float(frames)/float(seconds));
			//std::cout << fps << std::endl;
			seconds = 0;
			frames = 0;
		}
		//cout << time << endl;
		ptime = time;
		if (dt > limit && limit > 0) dt = limit;
	}
};
namespace MATH{
	float RAD = 0.0174532925f;
	float DEG = 57.295779515f;
	float getSign(float f){
		if (f == 0) return 0;
		return (f > 0) ? 1 : -1;
	}
	float random(float a, float b){// -10 to 10
    float random = ((float)rand())/(float)RAND_MAX;//random number between 0 and 1
    float d = b-a;//D is now 20
    float r = random * d; //between 0 and 20
    return a + r; //return -10 plus 0 through 20
	}
	float distance(float x1, float y1, float x2, float y2){
			return std::sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
	}
	float Xangle(float angle, float speed){return std::cos(RAD*angle)*speed;}
	float Yangle(float angle, float speed){return std::sin(RAD*angle)*speed;}
	bool chance(float value){
		float num = JE::MATH::random(0, 100);
		if (value >= num) return true;
		return false;
	}
	bool chance(float a, float b){
		if (b == 0) return true;
		float c = a / b;
		c *= 100;
		return chance(c);
	}
	float getAngle(float x1, float y1, float x2, float y2){
		return std::atan2(y2 - y1, x2 - x1)*JE::MATH::DEG;
	}
};
World* world;/**< \brief jeWorld* world, the active world. */
void init(){
	setWorld(new World());
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {std::cout << SDL_GetError() << std::endl;}

}

void initWindow(std::string name, int x, int y, int w, int h, int wflags, int rflags){
	init();
	SDL_SetHint(SDL_HINT_RENDER_OPENGL_SHADERS, "1");
	SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
	GRAPHICS::window = SDL_CreateWindow(name.c_str(), x, y, w, h, wflags);
    if (GRAPHICS::window == NULL) {std::cout << SDL_GetError() << std::endl;}
	GRAPHICS::renderer = SDL_CreateRenderer(GRAPHICS::window, -1, rflags);
    if (GRAPHICS::renderer == NULL) {std::cout << SDL_GetError() << std::endl;}
	GRAPHICS::backcolor = new GRAPHICS::Color();
	GRAPHICS::forecolor = new GRAPHICS::Color();
	GRAPHICS::setColor(255,255,255,255);
	GRAPHICS::setBackgroundColor(0,0,0,255);
    SDL_SetRenderDrawBlendMode(GRAPHICS::renderer, SDL_BLENDMODE_BLEND);
	//SDL_GL_CreateContext(GRAPHICS::window);
}

void update(){
	TIME::calculate();
	world->update();
}
};
