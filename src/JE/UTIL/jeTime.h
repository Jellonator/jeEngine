#pragma once
namespace JE{
namespace TIME{
	extern int time;/**< \brief int time, the time of the current frame. */
	extern int frames;/**< \brief int frames, frame count.  Used to calculate FPS.  Reset when seconds == 1. */
	extern double seconds;/**< \brief float seconds.  Not really useful, just used to calculate FPS once a second. */
	extern int ptime;/**< \brief int ptime, the previous time. */
	extern float dt;/**< \brief float dt, the delta time.  The time between the last frame and the current frame */
	extern double _dt;/**< \brief float dt, the delta time.  The time between the last frame and the current frame */
	extern double limit;/**< \brief float limit, the delta time cap */
	extern double fps;/**< \brief float fps, the frames per second.  Used for benchmarking. */
	extern bool printFPS;/**< \brief if the engine should print the FPS every second. */ 
	void calculate();/**< \brief Calculates time, called automatically by jeUpdate(); */
  /** \brief sets a maximum delta time, so things don't get weird after, say, a loading sequence.
   * \param float limit the maximum the delta time can be
   */
	void setDeltaTimeLimit(double limit = 1.0f/15.0f);
};
}
