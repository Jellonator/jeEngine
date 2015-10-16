#pragma once
#include "../UTIL/jeTime.h"
#include "jeImage.h"
#include <vector>
namespace JE{namespace GRAPHICS{
class Frame;
class Anim;
class Spritemap;
class Anim{
	public:
	Anim();
	virtual ~Anim();
	float speed;/**< \brief The speed of the animation */
	void setSpeed(float speed);
	std::vector<int> frames;/**< \brief A list of frames for the animation. */
};
class SpritemapData{
	public:
	std::vector<Frame> frames;/**< \brief A list of frames in the image. */
	std::vector<Anim> anims;/**< \brief A list of animations. */
	SpritemapData();
	virtual ~SpritemapData();
	Frame* getFrame(int anim, int frame);
	Frame* getFrame(int frame);
	Anim* getAnim(int anim);
	/** \brief Adds a new frame to the spritemap.
	 * \param x float, the X position.
	 * \param y float, the Y position.
	 * \param w float, the width.
	 * \param h float, the height.
	 * \param time float, the time in seconds of the frame.
	 * \param -1 int ID, the ID to set the frame to.  Defaults to appending to the back.
	 */
	void newFrame(int x, int y, int w, int h, float time, int ID = -1);
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
	void addFrame(int anim, int frame, int ID = -1);
};

class Frame{
	public:
	Frame();
	virtual ~Frame();
	void set(int x, int y, int w, int h, float length);
	float length;/**< \brief The length of the frame, in seconds. */
	SDL_Rect rect;/**< \brief The clipping rectangle of the frame. */
};

class Spritemap : public Image
{
	public:
		std::shared_ptr<SpritemapData> data;/**<  */
		float time;/**< \brief The time that the frame has been playing. */
		int anim;/**< \brief The current animation. */
		int frame;/**< \brief The current frame of the animation. */
		bool playing;/**< \brief Is the animation playing? */
		bool looping;/**< \brief Is the animation looping? */
		float speed;/**< \brief The speed of the animation. */

		Spritemap();
		Spritemap(std::string file);
		virtual ~Spritemap();
		Frame* getFrame(int anim, int frame);
		Frame* getFrame(int frame);
		Anim* getAnim(int anim);
        /** \brief Update the spritemap.
         * \param JE::dt float dt, the delta time.
         */
		void update(float dt = JE::TIME::dt);
		void drawWhole(float x = 0, float y = 0, float angle = 0, const std::shared_ptr<Entity>& parent = NULL);
        /** \brief Adds a new frame to the spritemap.
         * \param x float, the X position.
         * \param y float, the Y position.
         * \param w float, the width.
         * \param h float, the height.
         * \param time float, the time in seconds of the frame.
         * \param -1 int ID, the ID to set the frame to.  Defaults to appending to the back.
         */
		void newFrame(int x, int y, int w, int h, float time, int ID = -1);
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
		void addFrame(int anim, int frame, int ID = -1);

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
		void drawFrame(int frame, float x = 0, float y = 0, float angle = 0, const std::shared_ptr<Entity>& parent = NULL);
		void drawFrameNoAnim(int frame, float x = 0, float y = 0, float angle = 0, const std::shared_ptr<Entity>& parent = NULL);
        /** \brief Set's the Spritemap's spritemapData.
         * \param data SpritemapData*, the spritemapdata to use.
         */
		void useData(std::shared_ptr<SpritemapData> data);
		void useData(const std::shared_ptr<Spritemap>& spritemap);
		
		int getFrameCount();
		int getAnimFrameCount(int anim);
		
		int getAnimCount();
		
		float getFrameLength(int frame);
		float getAnimFrameLength(int anim, int frame);
		
		SDL_Rect& getFrameRect(int frame);
		SDL_Rect& getAnimFrameRect(int anim, int frame);
	protected:
	private:
};
};};
