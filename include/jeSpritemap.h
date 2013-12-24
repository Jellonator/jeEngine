#pragma once
#include "JE.h"

class jeFrame{
	public:
	jeFrame();
	virtual ~jeFrame();
	float length;/**< The length of the frame, in seconds. */
	SDL_Rect* rect;/**< The clipping rectangle of the frame. */
};

class jeAnim{
	public:
	float speed;/**< The speed of the animation */
	std::vector<unsigned int> frames;/**< A list of frames for the animation. */
};

class jeSpritemap : public jeImage
{
	public:
		std::vector<jeFrame*> frames;/**< A list of frames in the image. */
		std::vector<jeAnim*> anims;/**< A list of animations. */

		jeSpritemap();
		virtual ~jeSpritemap();

        /** \brief Update the spritemap.
         * \param JE::dt float dt, the delta time.
         */
		void update(float dt = JE::dt);

        /** \brief Adds a new frame to the spritemap.
         * \param x float, the X position.
         * \param y float, the Y position.
         * \param w float, the width.
         * \param h float, the height.
         * \param time float, the time in seconds of the frame.
         * \param -1 int ID, the ID to set the frame to.  Defaults to appending to the back.
         */
		void newFrame(float x, float y, float w, float h, float time, int ID = -1);
        /** \brief Adds a new animation to the spritemap.
         * \param -1 int ID, the ID to set the anim to.  Defaults to appending to the back.
         * \param 1 float speed, the speed of the animation.
         */
		void newAnim(int ID = -1, float speed = 1);
        /** \brief Adds a frame to an animation.
         * \param anim int, the animation to add the frame to.
         * \param frame int, the frame to add.
         * \param -1 int pos, the position to set the frame to.
         */
		void addFrame(int anim, int frame, int pos = -1);

        /** \brief Set the current frame to the desired frame, or leave blank to update the clip rect.
         * \param -1 int frame, the frame to use.
         */
		void setFrame(int frame = -1);
        /** \brief Set the speed of the animation.
         * \param speed float, the speed to use
         * \param anim int, the animation to change the speed of, leave blank for global speed.
         */
		void setSpeed(float speed, int anim = -1);

        /** \brief Play and animation.
         * \param anim int, the animation to play.
         * \param true bool loop, whether it should loop.
         * \param true bool reset, whether it should reset.
         * \param 0 int frame, the frame to start from.
         */
		void play(int anim, bool loop = true, bool reset = true, int frame = 0);
		void pause();/**< pause the animation. */
		void resume();/**< resume the animation. */
		void reset();/**< reset the animation. */

		float time;/**< The time that the frame has been playing. */
		int anim;/**< The current animation. */
		int frame;/**< The current frame of the animation. */
		bool playing;/**< Is the animation playing? */
		bool looping;/**< Is the animation looping? */
		float speed;/**< The speed of the animation. */
	protected:
	private:
};
