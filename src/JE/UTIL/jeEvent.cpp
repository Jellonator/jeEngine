#include "JE/UTIL/jeEvent.h"
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
	///EVENT COMPOUND
	Compound::Compound(){}
	Compound::Compound(std::vector<std::shared_ptr<Event>> event_vec){
		for (auto e : event_vec){
			this->addEvent(e);
		}
	}
	Compound::~Compound(){}
	void Compound::reset(){
		this->pressed = false;
		this->down = false;
		this->released = false;
		for (auto e : this->events){
			e->reset();
			this->down |= e->down;
		}
	}
	void Compound::test(SDL_Event* input){
		for (auto e : this->events){
			e->test(input);
			this->pressed |= e->pressed;
			this->down |= e->down;
			this->released |= e->released;
		}
	}
	void Compound::addEvent(std::shared_ptr<Event> event){
		this->events.push_back(event);
	}
	void Compound::removeEvent(std::shared_ptr<Event> event){
		for (unsigned int i = 0; i < this->events.size(); ++i){
			if(event == this->events[i]) {
				this->events[i].reset();//just making sure
				this->events.erase(i+this->events.begin());
			}
		}
	}
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
		this->direction = MOUSEWHEEL::WHEEL_NONE;
	}
	MouseWheel::MouseWheel(MOUSEWHEEL wheel_direction) : Event(){
		this->direction = wheel_direction;
	}
	void MouseWheel::test(SDL_Event* input){
		if (input->type == SDL_MOUSEWHEEL){
			this->x += input->wheel.x;
			this->y += input->wheel.y;
			
			bool done_did_it = false;
			switch(this->direction){
				case MOUSEWHEEL::WHEEL_DOWN:
					if (input->wheel.y < 0) done_did_it = true;
					break;
				case MOUSEWHEEL::WHEEL_LEFT:
					if (input->wheel.x > 0) done_did_it = true;
					break;
				case MOUSEWHEEL::WHEEL_UP:
					if (input->wheel.y > 0) done_did_it = true;
					break;
				case MOUSEWHEEL::WHEEL_RIGHT:
					if (input->wheel.x < 0) done_did_it = true;
					break;
				default:
					// Do nothing
					break;
			}
			
			if (done_did_it){
				this->pressed = true;
			}
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
		this->data1 = 0;
		this->data2 = 0;
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
		this->inside = true;
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
	///EVENT TEXT
	void Text::test(SDL_Event* input){
		if (input->type == SDL_TEXTINPUT){
			this->value += input->text.text;
		}
		if (input->type == SDL_TEXTEDITING){
			this->value += input->text.text;
		}
		if (input->type == SDL_KEYDOWN){
			if (input->key.keysym.sym == SDLK_BACKSPACE){
				if (this->value.size() > 0){
					this->value.pop_back();
				}
			}
		}
	}
	void Text::reset(){
		//this->value = "";
	}
	void Text::resetText(){
		this->value = "";
	}
	std::string Text::getValue(){
		return this->value;
	}
	Text::Text(){
		//SDL_StartTextInput();
		this->value = "";
	}
	Text::~Text(){
		//SDL_StopTextInput();
	}
	///EVENT CONTAINER
	Container::Container() : events(){

	}
	Container::~Container(){
		//JE::clearPointerVector(&this->events);
	}
	void Container::poll(){
		//remove bad weak pointers
		unsigned int index = 0;
		while (index < this->events.size()){
			if (this->events[index].expired()){
				this->events.erase(index + this->events.begin());
			} else {
				++index;
			}
		}
		
		//reset all of the events.
		for (unsigned int i = 0; i < this->events.size(); ++i){
			if (this->events[i].expired()) continue;
			this->events[i].lock()->reset();
		}
		//poll all of the inputs in the queue
		SDL_Event event;
		while(SDL_PollEvent(&event)){
			for (unsigned int i = 0; i < this->events.size(); ++i){
				if (this->events[i].expired()) continue;
				this->events[i].lock()->test(&event);
			}
		}
	}

	void Container::removeEvent(std::shared_ptr<Event> event){
		for (unsigned int i = 0; i < this->events.size(); ++i){
			if(event == this->events[i].lock()) {
				if (this->events[i].expired()) continue;
				this->events[i].reset();//just making sure
				this->events.erase(i+this->events.begin());
			}
		}
	}

	void Container::addEvent(std::shared_ptr<Event> event){
		this->events.push_back(event);
	}

	void Container::execute(){
		for (unsigned int i = 0; i < this->events.size(); ++i){
			if (this->events[i].expired()) continue;
			this->events[i].lock()->execute();
		}
	}
};};
