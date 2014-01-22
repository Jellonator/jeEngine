#include "JE.h"
void jePrint(std::string s){std::cout << s << std::endl;}

namespace JE
{
	#ifdef _SDL_H
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Renderer* _renderer;
	#endif
    int time = 0;
	int frames = 0;
	float seconds = 0;
	int ptime = 0;
	float dt = 0;
	float fps = 0;
	jeWorld* world;/**< \brief jeWorld* world, the active world. */
	jeColor* backcolor;
	jeColor* forecolor;
}

void jeInit(){
	jeWorld::set(new jeWorld());
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {std::cout << SDL_GetError() << std::endl;}
	JE::backcolor = new jeColor();
	JE::forecolor = new jeColor();
	jeSetColor(255,255,255,255);
	jeSetBackgroundColor(0,0,0,255);
}

void jeInitWindow(std::string name, int x, int y, int w, int h, int wflags, int rflags){
	jeInit();
	JE::window = SDL_CreateWindow(name.c_str(), x, y, w, h, wflags);
    if (JE::window == NULL) {std::cout << SDL_GetError() << std::endl;}
	JE::renderer = SDL_CreateRenderer(JE::window, -1, rflags);
    if (JE::renderer == NULL) {std::cout << SDL_GetError() << std::endl;}
    JE::_renderer = JE::renderer;
}
void jeCalcTime(){
	JE::frames ++;
	JE::time = SDL_GetTicks();
	JE::dt = float(JE::time - JE::ptime)/1000;
	if (JE::dt > 0){
		JE::seconds += JE::dt;
		JE::fps = (float(JE::frames)/float(JE::seconds));
	}
	if (JE::seconds > 1){
		//cout << "FPS:  " << JE::fps << endl;
		JE::seconds = 0;
		JE::frames = 0;
	}
	//cout << time << endl;
	JE::ptime = JE::time;
}

void jeUpdate(){

	jeCalcTime();

	JE::world->update();
}
void jeDraw(){
	SDL_SetRenderDrawColor(JE::renderer,JE::backcolor->r,JE::backcolor->g,JE::backcolor->b,JE::backcolor->a);
	SDL_RenderClear(JE::renderer);
	SDL_SetRenderDrawColor(JE::renderer,JE::forecolor->r,JE::forecolor->g,JE::forecolor->b,JE::forecolor->a);
	JE::world->draw();
}
void jeFlip(){
	SDL_RenderPresent(JE::renderer);
}

float jeGetSign(float f){
    if (f == 0) return 0;
    return (f > 0) ? 1 : -1;
}
