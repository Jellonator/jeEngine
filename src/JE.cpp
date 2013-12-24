#include "JE.h"
void jePrint(std::string s){std::cout << s << std::endl;}

namespace JE
{
	#ifdef _SDL_H
	SDL_Window* window;
	SDL_Renderer* renderer;
	#endif
    int time = 0;
	int frames = 0;
	float seconds = 0;
	int ptime = 0;
	float dt = 0;
	float fps = 0;
	jeWorld* world;/**< \brief jeWorld* world, the active world. */
}

void jeInit(){
	jeWorld::set(new jeWorld());
	#ifdef _SDL_H
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {std::cout << SDL_GetError() << std::endl;}
	#endif // _SDL_H
}
#ifdef _SDL_H
void jeInitWindow(std::string name, int x, int y, int w, int h, int wflags, int rflags){
	jeInit();
	JE::window = SDL_CreateWindow(name.c_str(), x, y, w, h, wflags);
    if (JE::window == NULL) {std::cout << SDL_GetError() << std::endl;}
	JE::renderer = SDL_CreateRenderer(JE::window, -1, rflags);
    if (JE::renderer == NULL) {std::cout << SDL_GetError() << std::endl;}
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
#endif // _SDL_H
void jeUpdate(){
	#ifdef _SDL_H
	jeCalcTime();
	#endif // _SDL_H
	JE::world->update();
}
void jeDraw(){
	#ifdef _SDL_H
	SDL_RenderClear(JE::renderer);
	#endif // _SDL_H
	JE::world->draw();
	#ifdef _SDL_H
	SDL_RenderPresent(JE::renderer);
	#endif
}
