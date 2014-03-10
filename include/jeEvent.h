#pragma once
#include "JE.h"
struct jeEvent{
	jeEvent();
	virtual ~jeEvent();
	unsigned int type;/**< \brief the event type, e.g. SDL_KEYDOWN. */
	int stype;/**< \brief the event sub-type, e.g. SDL_WINDOWEVENT_CLOSE. */
	int button;/**< \brief the mouse button that was pressed */
	int scancode;/**< \brief scancode value of the key pressed */
	int symbol;/**< \brief symbol value of the key pressed */
	int mod;/**< \brief key modification, i.e. shift */
	bool repeat;/**< \brief whether the event should allow key repeats */
	unsigned int ID;/**< \brief The window ID of the event */
	float x;/**< \brief the x value that the mouse's x should be greater than. Used for MouseAreaEvent. */
	float y;/**< \brief the y value that the mouse's y should be greater than. Used for MouseAreaEvent. Also used with MouseWheelEvent. */
	float x2;/**< \brief the x value that the mouse's x should be less than. Used for MouseAreaEvent. */
	float y2;/**< \brief the y value that the mouse's y should be less than. Used for MouseAreaEvent. */
	//float angle;
	//float range;
	int wheel;/**< \brief the mouse's wheel movement. */
	int pvalue;/**< \brief the previous value of the event */
	int value;/**< \brief the current value of the event */
	bool pressed;/**< \brief true if the event just happened */
	bool released;/**< \brief true if the event just stopped */
	bool down;/**< \brief true if the event is occuring */
	#ifndef JE_NO_EVENT_FUNCTIONS
	function_pointer during;/**< \brief function called every frame that the event is active. */
	function_pointer start;/**< \brief function called when the event starts */
	function_pointer end;/**< \brief function called when the event stops */
	#endif
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
	void execute();/**< \brief PRIVATE; DO NOT USE. */
	void update();/**< \brief PRIVATE; DO NOT USE. */
	void reset();/**< \brief PRIVATE; DO NOT USE. */
};
struct jeEventContainer{
	std::vector<jeEvent*> events;/**< \brief a list of events that the container manages. */
	void poll();/**< \brief updates the events in the container. */
    /** \brief Adds an event to the container
     * \param event jeEvent*; The event to add to the container.
     */
	void addEvent(jeEvent* event);
    /** \brief Removes all occurences of the event from the container
     * \param event jeEvent*; The event to remove.
     */
	void removeEvent(jeEvent* event);
};
/** \brief Creates a new keyboard event from a keycode, e.g. SDLK_xxx
 * \param key SDL_Keycode; The keycode to use
 * \param bool repeat; whether the event should accept repeat commands, i.e. when you hold down the 'o' key and you get 'oooooooo'
 * \return jeEvent*; The Event that was created.
 */
jeEvent* jeNewKeyboardEvent(SDL_Keycode key, bool repeat = false);

/** \brief Creates a new keyboard event from a scancode, e.g. SDL_SCANCODE_xxx
 * \param key SDL_Scancode; The scancode to use
 * \param bool repeat; whether the event should accept repeat commands, i.e. when you hold down the 'o' key and you get 'oooooooo'
 * \return jeEvent*; The Event that was created.
 */
jeEvent* jeNewKeyboardEvent(SDL_Scancode key, bool repeat = false);

/** \brief Creates a new quit event, for when the red X* button is clicked. *Button may not be red(some linux distributions) or an X(Mac). Also applies to Alt+F4.
 * \return jeEvent*; The Event that was created.
 */
jeEvent* jeNewQuitEvent();

/** \brief Creates a new event for when the Mouse is in a certain region.
 * \param x int; the x1 position, mouse must be to the right.
 * \param y int; the y1 position, mouse must be below it.
 * \param x2 int; the x2 position, the mouse must be to the left.
 * \param y2 int; the y2 position, the mouse must be above it.
 * \return jeEvent*; The Event that was created.
 */
jeEvent* jeNewMouseAreaEvent(int x, int y, int x2, int y2);

/** \brief Creates a new Event from a mouse button, e.g. SDL_BUTTON_xxx
 * \param button int; the Button to use.
 * \return jeEvent*; The Event that was created.
 */
jeEvent* jeNewMouseButtonEvent(int button);

/** \brief Creates a new Event from a window event, e.g. SDL_WINDOWEVENT_xxx
 * \param type int; The window event to use.
 * \return jeEvent*; The Event that was created.
 */
jeEvent* jeNewWindowEvent(int type);

/** \brief Creates a new Event for retreiving mouse wheel information.
 * \return jeEvent*; The Event that was created.
 */
jeEvent* jeNewMouseWheelEvent();


/** \brief
 * \param a jeInput*; The first event to compare.
 * \param b jeEvent*; The second event to compare.
 * \param int mode; The mode of the comparison.
 * \return int; The status of the event.
 */
int jeTestEvent(jeInput* a, jeEvent* b, int mode = JE_EVENTCOMPARE_AUTO);
