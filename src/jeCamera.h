#pragma once
#include "JE.h"
namespace JE{namespace GRAPHICS{
class Camera : public Point
{
	public:
		SDL_Rect* clip;
		float sx, sy;
		float offX;
		float offY;
		SDL_Point* size;

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
		void reset();/**< \brief Resets the entire camera to defaults. */
        /** \brief Creates a letterboxed camera.
         * \param w float, width of the viewport.
         * \param h float, height of the viewport
         * \param float x, Horizontal offset of camera, from 0-1(0.5 being middle)
         * \param float y, Verticle offset of camera, from 0-1(0.5 being middle)
         */
		void letterbox(float width, float height, float x = 0.5, float y = 0.5);
		/** \brief Creates a letterboxed camera.
         * \param w float, width of the viewport.
         * \param h float, height of the viewport
         * \param float x, Horizontal offset of camera, from 0-1(0.5 being middle)
         * \param float y, Verticle offset of camera, from 0-1(0.5 being middle)
         */
		void zoom(float width, float height, float x = 0.5, float y = 0.5);
        /** \brief Sets the viewport clipping to have a border of (x),(y) pixels.
         * \param w float, The width of the border.
         * \param h float, The height of the border(defaults to X)
         */
		void border(float x, float y = -1);
        /** \brief Get the width/height of the viewport
         * \param w float*, The width of the viewport.
         * \param h float*, The height of the viewport.
         */
		void getRatio(float* x, float* y);

		//void moveTo(float x, float y, float step = JE::dt);
		//void moveToShake(float x, float y, float range, float intensity, float step = JE::dt);
	protected:
	private:
};
};};
