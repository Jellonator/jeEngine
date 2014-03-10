#include "jeEvent.h"

int jeTestEvent(jeInput* a, jeEvent* b, int mode){
	if(a->type == b->type){
		switch(a->type){
			case SDL_WINDOWEVENT:
				if (mode == JE_EVENTCOMPARE_AUTO) mode = JE_EVENTCOMPARE_TYPE;
				if (a->window.event == b->stype){
					if (mode == JE_EVENTCOMPARE_TYPE) return 1;
					if(a->window.windowID == b->ID && a->window.data1 == b->x && a->window.data2 == b->y) return 1;
				}
				return -1;
			break;
			case SDL_MOUSEMOTION:
				if (mode == JE_EVENTCOMPARE_AUTO) mode = JE_EVENTCOMPARE_FULL;
				if (mode == JE_EVENTCOMPARE_TYPE) return 1;
				if ((b->x <= a->motion.x && a->motion.x <= b->x2) && (b->y <= a->motion.y && a->motion.y <= b->y2)) return 1;
			break;
			case SDL_MOUSEWHEEL:
				if (mode == JE_EVENTCOMPARE_AUTO) mode = JE_EVENTCOMPARE_FULL;
				if (mode == JE_EVENTCOMPARE_TYPE) return 1;
				b->wheel = a->wheel.y;
				if((a->wheel.y > b->y && b->y >= 0) || (a->wheel.y < b->y && b->y <= 0)) return a->wheel.y - b->y;
			break;
			case SDL_QUIT:
				return 1;
			break;
		}
	}
	if ((a->type == SDL_KEYDOWN || a->type == SDL_KEYUP) && b->type == SDL_KEYDOWN){
		if (mode == JE_EVENTCOMPARE_AUTO) mode = JE_EVENTCOMPARE_FULL;
		if (mode == JE_EVENTCOMPARE_TYPE) return 1;
		if (a->key.repeat != 0 && b->repeat == false) return 0;
		if ((a->key.keysym.mod != b->mod) && b->mod >= 0) return 0;
		if ((a->key.keysym.scancode == b->scancode && a->key.keysym.scancode != 0 )||( a->key.keysym.sym == b->symbol && a->key.keysym.sym != 0)) return (a->type == SDL_KEYDOWN) ? 1 : -1;
	}
	if ((a->type == SDL_MOUSEBUTTONDOWN || a->type == SDL_MOUSEBUTTONUP) && b->type == SDL_MOUSEBUTTONDOWN){
		if (mode == JE_EVENTCOMPARE_AUTO) mode = JE_EVENTCOMPARE_FULL;
		if (mode == JE_EVENTCOMPARE_TYPE) return 1;
		if (a->button.button == b->button) return (a->type == SDL_MOUSEBUTTONDOWN) ? 1 : -1;
	}
	return 0;
}

jeEvent::jeEvent(){
	#ifndef JE_NO_EVENT_FUNCTIONS
	this->during = NULL;
	this->start = NULL;
	this->end = NULL;
	#endif // JE_NO_EVENT_FUNCTIONS
	this->pressed = this->released = this->down = false;
	this->value = -1;
	this->pvalue = -1;
}

jeEvent::~jeEvent(){

}

jeEvent* jeNewKeyboardEvent(SDL_Keycode key, bool repeat){
	jeEvent* e = new jeEvent();
	e->type = SDL_KEYDOWN;
	e->symbol = key;
	e->scancode = SDL_GetScancodeFromKey(key);
	e->repeat = repeat;
	e->mod = -1;
	return e;
}

jeEvent* jeNewKeyboardEvent(SDL_Scancode key, bool repeat){
	jeEvent* e = new jeEvent();
	e->type = SDL_KEYDOWN;
	e->scancode = key;
	e->symbol = SDL_GetKeyFromScancode(key);
	e->repeat = repeat;
	e->mod = -1;
	return e;
}

jeEvent* jeNewQuitEvent(){
	jeEvent* e = new jeEvent();
	e->type = SDL_QUIT;
	return e;
}

jeEvent* jeNewMouseAreaEvent(int x, int y, int x2, int y2){
	jeEvent* e = new jeEvent();
	e->type = SDL_MOUSEMOTION;
	e->x = x;
	e->y = y;
	e->x2 = x2;
	e->y2 = y2;
	return e;
}

jeEvent* jeNewMouseButtonEvent(int button){
	jeEvent* e = new jeEvent();
	e->type = SDL_MOUSEBUTTONDOWN;
	e->button = button;
	return e;
}

jeEvent* jeNewWindowEvent(int type){
	jeEvent* e = new jeEvent();
	e->type = SDL_WINDOWEVENT;
	e->stype = type;
	return e;
}

jeEvent* jeNewMouseWheelEvent(){
	jeEvent* e = new jeEvent();
	e->type = SDL_MOUSEWHEEL;
	e->y = 0;
	return e;
}

void jeEventContainer::poll(){
	//reset all of the events.
	for (unsigned int i = 0; i < this->events.size(); ++i){
		this->events[i]->reset();
	}
	//poll all of the inputs in the queue
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		for (unsigned int i = 0; i < this->events.size(); ++i){
			jeEvent* e = this->events[i];
			int p = e->value;
			int v = jeTestEvent(&event, e);
			//If the returned value is not 0, then update the event.
			if (v != 0){
				e->value = v;
				e->pvalue = p;
				e->update();
			}
		}
	}
	//Then execute all of the events(if applicable)
	#ifndef JE_NO_EVENT_FUNCTIONS
	for (unsigned int i = 0; i < this->events.size(); ++i){
		this->events[i]->execute();
	}
	#endif // JE_NO_EVENT_FUNCTIONS
}

void jeEventContainer::removeEvent(jeEvent* event){
	for (unsigned int i = 0; i < this->events.size(); ++i){
		if(event == this->events[i]) {
			this->events.erase(i+this->events.begin());
		}
	}
	delete event;
}

void jeEventContainer::addEvent(jeEvent* event){
	this->events.push_back(event);
}

void jeEvent::reset(){
	this->wheel = 0;
	if (this->type == SDL_QUIT){this->down = false; this->value = 0;}
	this->pressed = this->released = false;
}

void jeEvent::update(){
	if (value == 1 && pvalue <= 0) pressed = true;
	if (value == -1 && pvalue >= 0) released = true;
	if (value > 0) down = true;
	if (value <= 0) down = false;
}

void jeEvent::execute(){
	#ifndef JE_NO_EVENT_FUNCTIONS
	if (start != NULL && pressed) start();
	if (end   != NULL && released) end();
	if (during!= NULL && down) during();
	#endif
}
#ifndef JE_NO_EVENT_FUNCTIONS
void jeEvent::setDuring(function_pointer f){this->during = f;}
void jeEvent::setStart(function_pointer f){this->start = f;}
void jeEvent::setEnd(function_pointer f){this->end = f;}
#else
void jeEvent::setDuring(function_pointer f){}
void jeEvent::setStart(function_pointer f){}
void jeEvent::setEnd(function_pointer f){}
#endif
