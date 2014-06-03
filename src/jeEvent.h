#pragma once
#include "JE.h"
namespace JE{
struct Event{public:
	Event();
	virtual ~Event();
	#ifndef JE_NO_EVENT_FUNCTIONS
	function_pointer during;/**< \brief function called every frame that the event is active. */
	function_pointer start;/**< \brief function called when the event starts */
	function_pointer end;/**< \brief function called when the event stops */
	#endif
	bool down;
	bool released;
	bool pressed;
	int x;
	int y;
    /** \brief sets the function that is called every frame the event is active
     * \param f function_pointer the pointer to the function to call(Must be void, no arguments.)
     */
	void setDuring(function_pointer f);
    /** \brief sets the function that is called when the event starts
     * \param f function_pointer the pointer to the function to call(Must be void, no arguments.)
     */
	void setStart(function_pointer f);
    /** \brief sets the function that is called when the event ends
     * \param f function_pointer; the pointer to the function to call(Must be void, no arguments.)
     */
	void setEnd(function_pointer f);

	//virtual void execute();
	virtual void test(EVENT::Input* input);/**< \brief PRIVATE; DO NOT USE. */
	void execute();
	virtual void reset();
};
namespace EVENT{
	struct Container{public:
		std::vector<Event*> events;/**< \brief a list of events that the container manages. */
		void poll();/**< \brief updates the events in the container. */
		/** \brief Adds an event to the container
		 * \param event Event*; The event to add to the container.
		 */
		void addEvent(Event* event);
		/** \brief Removes all occurences of the event from the container
		 * \param event Event*; The event to remove.
		 */
		void removeEvent(Event* event);
		void execute();/**< \brief execute all events accordingly. */
	};

	struct Keyboard : public Event {public:
		virtual void test(Input* input);

		SDL_Keycode keycode;
		SDL_Scancode scancode;
		bool is_scan;
		bool repeat;

		Keyboard(SDL_Keycode key, bool repeat = false);
		Keyboard(SDL_Scancode key, bool repeat = false);
		virtual ~Keyboard();
	};
	struct Quit : public Event {public:
		virtual void test(Input* input);

		Quit();
		virtual ~Quit();
	};
	struct MouseArea : public Event {public:
		virtual void test(Input* input);

		int x1;
		int y1;
		int x2;
		int y2;
		bool inside;

		MouseArea(int x1, int y1, int x2, int y2);
		virtual ~MouseArea();
	};
	struct MouseButton : public Event {public:
		virtual void test(Input* input);

		int button;
		bool doubleclick;

		MouseButton(int button, bool doubleclick = false);
		virtual ~MouseButton();
	};
	struct MouseWheel : public Event {public:
		virtual void test(Input* input);
		virtual void reset();

		MouseWheel();
		virtual ~MouseWheel();
	};
	struct Window : public Event {public:
		virtual void test(Input* input);

		int type;
		int data1;
		int data2;
		bool use_data;
		unsigned int ID;

		Window(int event, SDL_Window* window = NULL);
		Window(int event, int data1, int data2, SDL_Window* window = NULL);
		virtual ~Window();
	};
};};
