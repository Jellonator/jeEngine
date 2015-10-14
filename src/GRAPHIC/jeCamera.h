#pragma once
#include "../jePoint.h"
#include "../jeMain.h"
#include <SDL2/SDL_image.h>
namespace JE{namespace GRAPHICS{
class Camera : public Point
{
	public:
		SDL_Rect clip;
		bool use_clip;
		float sx, sy; 
		float offX;
		float offY;
		SDL_Point size;
		bool use_size;

		Camera();
		virtual ~Camera();
        /** \brief Sets the camera scaling.
         * \param x float, ammount to scale viewport width.
         * \param y float, ammount to scale height.
         */
		void setScale(float x, float y=-1);
        /** \brief multiplies the current camera's scale.
         * \param x float, ammount to scale viewport width.
         * \param y float, ammount to scale viewport height.
         */
		void pushScale(float x, float y=-1);
        /** \brief Sets the clipping rectangle, which is where the viewport is drawn.
         * \param x float, The x position of the clipping rectangle.
         * \param y float, The y position of the clipping rectangle.
         * \param w float, The width of the clipping rectangle.
         * \param h float, The height of the clipping rectangle.
         */
		void setClip(float x, float y, float w, float h);
        /** \brief Set the offset of the viewport.
         * \param x float, The x position of the viewport.
         * \param y float, The y position of the viewport.
         */
		void setPosition(float x, float y);
        /** \brief Set the size of the viewport.
         * \param w float, The width of the viewport.
         * \param h float, The height of the viewport.
         */
		void setSize(float w, float h);
		void disableSize();/**< \brief Resets scaling to 1x1. */
		void disableClip();/**< \brief Disables viewport clipping. */
		void enableClip();
		void reset();/**< \brief Resets the entire camera to defaults. */
        /** \brief Creates a letterboxed camera.
         * \param w float, width of the viewport.
         * \param h float, height of the viewport
         * \param float x, Horizontal offset of camera, from 0-1(0.5 being middle)
         * \param float y, Verticle offset of camera, from 0-1(0.5 being middle)
         */
		void letterbox(float width, float height, float zoom = 0, float x = 0.5, float y = 0.5, bool doCrop = true);
        /** \brief Sets the viewport clipping to have a border of (x),(y) pixels.
         * \param w float, The width of the border.
         * \param h float, The height of the border(defaults to X)
         */
		void border(float x, float y = -1);
        /** \brief Get the width/height of the viewport
         * \param w float*, The width of the viewport.
         * \param h float*, The height of the viewport.
         */
		void getRatio(float* x, float* y, bool ignoreClip = false);

		float getLeft();
		float getRight();
		float getTop();
		float getBottom();

		float getPositionX(float pos, float left_bound, float right_bound);
		float getPositionY(float pos, float top_bound, float bottom_bound);

		void setScaleZoom(float x, float y = -1);
		void centerTo(float x, float y);

		float getWidth();
		float getHeight();

		void startClip();
		void endClip();
		void getTransforms(float* x = NULL, float* y = NULL, float* width = NULL, float* height = NULL, float* originx = NULL, float* originy = NULL);
		//void moveTo(float x, float y, float step = JE::dt);
		//void moveToShake(float x, float y, float range, float intensity, float step = JE::dt);
		void getPoint(float* x, float* y);
		
		void push(SDL_Renderer* renderer = renderer);
		void pop(SDL_Renderer* renderer = renderer);
		
		void getMousePosition(float* x, float* y);
	protected:
	private:
};
void tempDisableCameras();
void tempEnableCameras();
};};
