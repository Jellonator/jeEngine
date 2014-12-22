#pragma once
#include "JE.h"
#include "jeData.h"
namespace JE{namespace GRAPHICS{
class Frame;
class Anim;
class Spritemap;

class SpritemapData : public Data{
	public:
	std::vector<Frame*> frames;/**< \brief A list of frames in the image. */
	std::vector<Anim*> anims;/**< \brief A list of animations. */
	SpritemapData(void* owner = NULL);
	virtual ~SpritemapData();
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
};

class Frame{
	public:
	Frame();
	virtual ~Frame();
	float length;/**< \brief The length of the frame, in seconds. */
	SDL_Rect* rect;/**< \brief The clipping rectangle of the frame. */
};

class Anim{
	public:
	float speed;/**< \brief The speed of the animation */
	std::vector<unsigned int> frames;/**< \brief A list of frames for the animation. */
};

class Spritemap : public Image
{
	public:
		SpritemapData* data;/**<  */
		float time;/**< \brief The time that the frame has been playing. */
		int anim;/**< \brief The current animation. */
		int frame;/**< \brief The current frame of the animation. */
		bool playing;/**< \brief Is the animation playing? */
		bool looping;/**< \brief Is the animation looping? */
		float speed;/**< \brief The speed of the animation. */

		Spritemap();
		Spritemap(std::string file);
		virtual ~Spritemap();

        /** \brief Update the spritemap.
         * \param JE::dt float dt, the delta time.
         */
		void update(float dt = JE::TIME::dt);
		void drawWhole(float x = 0, float y = 0, Camera* camera = NULL, Entity* parent = NULL);
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
		void setFrameNoAnim(int frame = -1);
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
		void pause();/**< \brief pause the animation. */
		void resume();/**< \brief resume the animation. */
		void reset();/**< \brief reset the animation. */
		void drawFrame(int frame, float x = 0, float y = 0, Camera* camera = NULL, Entity* parent = NULL);
		void drawFrameNoAnim(int frame, float x = 0, float y = 0, Camera* camera = NULL, Entity* parent = NULL);
        /** \brief Set's the Spritemap's spritemapData.
         * \param data SpritemapData*, the spritemapdata to use.
         */
		void useData(SpritemapData* data);
	protected:
	private:
};
};};
