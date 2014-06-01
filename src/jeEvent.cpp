#include "jeEvent.h"
namespace JE{
///EVENTS
Event::~Event(){}
Event::Event(){
	#ifndef JE_NO_EVENT_FUNCTIONS
	this->during = NULL;
	this->start = NULL;
	this->end = NULL;
	#endif // JE_NO_EVENT_FUNCTIONS
	this->down = false;
	this->released = false;
	this->pressed = false;
	this->x = 0;
	this->y = 0;
}
void Event::test(EVENT::Input* input){}
void Event::execute(){
	#ifndef JE_NO_EVENT_FUNCTIONS
	if (this->start != NULL && pressed) this->start();
	if (this->end   != NULL && released) this->end();
	if (this->during!= NULL && down) this->during();
	#endif
}
void Event::reset(){
	this->pressed = this->released = false;
}
#ifndef JE_NO_EVENT_FUNCTIONS
void Event::setDuring(function_pointer f){this->during = f;}
void Event::setStart(function_pointer f){this->start = f;}
void Event::setEnd(function_pointer f){this->end = f;}
#else
void Event::setDuring(function_pointer f){}
void Event::setStart(function_pointer f){}
void Event::setEnd(function_pointer f){}
#endif
namespace EVENT{
	///EVENT KEYBOARD
	Keyboard::~Keyboard(){}
	Keyboard::Keyboard(SDL_Scancode key, bool repeat) : Event(){
		this->is_scan = true;
		this->repeat = repeat;
		this->scancode = key;
	}
	Keyboard::Keyboard(SDL_Keycode key, bool repeat) : Event(){
		this->is_scan = false;
		this->repeat = repeat;
		this->keycode = key;
	}
	void Keyboard::test(SDL_Event* input){
		if (input->type == SDL_KEYDOWN || input->type == SDL_KEYUP){
			if ((input->key.keysym.scancode == this->scancode && this->is_scan) || (input->key.keysym.sym == this->keycode && !this->is_scan)){
				if (input->type == SDL_KEYDOWN){
					if (input->key.repeat == 0 || this->repeat == true){
						this->pressed = true;
						this->down = true;
					}
				}else{
					if (this->down == true){
						this->down = false;
						this->released = true;
					}
				}
			}
		}
	}
	///EVENT MOUSE BUTTON
	MouseButton::~MouseButton(){}
	MouseButton::MouseButton(int button, bool doubleclick) : Event(){
		this->button = button;
		this->doubleclick = doubleclick;
	}
	void MouseButton::test(SDL_Event* input){
		if (input->type == SDL_MOUSEBUTTONDOWN || input->type == SDL_MOUSEBUTTONUP){
			if (input->button.button == this->button && (input->button.clicks > 1 || !this->doubleclick)){
				if (input->type == SDL_MOUSEBUTTONDOWN){
					this->pressed = true;
					this->down = true;
				}else{
					if (this->down == true){
						this->down = false;
						this->released = true;
					}
				}
			}
		}
	}
	///EVENT MOUSE WHEEL
	MouseWheel::~MouseWheel(){}
	MouseWheel::MouseWheel() : Event(){

	}
	void MouseWheel::test(SDL_Event* input){
		if (input->type == SDL_MOUSEWHEEL){
			this->x += input->wheel.x;
			this->y += input->wheel.y;
		}
	}
	void MouseWheel::reset(){
		Event::reset();
		this->x = 0;
		this->y = 0;
	}
	///EVENT WINDOW
	Window::~Window(){}
	Window::Window(int event, SDL_Window* window) : Event(){
		this->type = event;
		this->use_data = false;
		if (window == NULL) this->ID = 0; else this->ID = SDL_GetWindowID(window);
	}
	Window::Window(int event, int data1, int data2, SDL_Window* window) : Event(){
		this->type = event;
		this->use_data = true;
		this->data1 = data1;
		this->data2 = data2;
		if (window == NULL) this->ID = 0; else this->ID = SDL_GetWindowID(window);
	}
	void Window::test(SDL_Event* input){
		if (input->type == SDL_WINDOWEVENT){
			if (input->window.event == this->type){
				if (!this->use_data || (this->data1 == input->window.data1 && this->data2 == input->window.data2)) {
					this->pressed = true;
					this->x = input->window.data1;
					this->y = input->window.data2;
				}
			}
		}
	}
	///EVENT QUIT
	Quit::~Quit(){}
	Quit::Quit() : Event(){

	}
	void Quit::test(SDL_Event* input){
		if (input->type == SDL_QUIT){
			this->pressed = true;
		}
	}
	///EVENT MOUSE AREA
	MouseArea::~MouseArea(){}
	MouseArea::MouseArea(int x1, int y1, int x2, int y2) : Event(){
		this->x = this->y = 0;
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
	}
	void MouseArea::test(SDL_Event* input){
		if (input->type == SDL_MOUSEMOTION){
			if (input->motion.x >= this->x1 &&
				input->motion.y >= this->y1 &&
				input->motion.x <= this->x2 &&
				input->motion.y <= this->y2){
					if (this->down == false) this->pressed = true;
					this->down = true;
				} else {
					if (this->down == true) this->released = true;
					this->down = false;
				}
		}
	}
	///EVENT CONTAINER
	void Container::poll(){
		//reset all of the events.
		for (unsigned int i = 0; i < this->events.size(); ++i){
			this->events[i]->reset();
		}
		//poll all of the inputs in the queue
		SDL_Event event;
		while(SDL_PollEvent(&event)){
			for (unsigned int i = 0; i < this->events.size(); ++i){
				this->events[i]->test(&event);
			}
		}
	}

	void Container::removeEvent(Event* event){
		for (unsigned int i = 0; i < this->events.size(); ++i){
			if(event == this->events[i]) {
				this->events.erase(i+this->events.begin());
			}
		}
		delete event;
	}

	void Container::addEvent(Event* event){
		this->events.push_back(event);
	}

	void Container::execute(){
		for (unsigned int i = 0; i < this->events.size(); ++i){
			this->events[i]->execute();
		}
	}
};};
