#pragma once

#include "SDL_Libs.h"
#include "GameObject.h"

/**
* The camera class.
* Contains all the relevant implementation relative to the camera.
*/
class Camera {

	public:
		/**
		* The constructor.
		* Initializes all the attributes.
		* @param gameObject_ : The GameObject to centralize the camera on.
		*/
		explicit Camera(GameObject* const gameObject_);

		/**
		* The destructor.
		*/
		~Camera();

		/**
		* Updates the camera.
		* @see Camera::updatePosition
		* Centralizes the player on the screen.
		*/
		void update();

		/**
		* Changes the entity to centralize upon.
		* @param entity_ : The entity to centralize the camera on.
		*/
		void centralizeOn(GameObject* const gameObject_);

		/**
		* @return The camera clip (an SDL_Rect).
		*/
		SDL_Rect& getClip();

		/**
		* @param width_,height_ : Tells the camera what the width and height of the level is.
		* @see Level::update()
		*/
		void setLevelWH(const unsigned int width_, const unsigned int height_);

	private:
		/**
		* Updates the cameras position.
		* Based on the players position, change cameras position.
		*/
		void updatePosition();

		GameObject* gameObject; /**< Reference to the entity. */
		unsigned int levelW; /**< The width of the level. */
		unsigned int levelH; /**< The height of the level. */
		SDL_Rect clip; /**< Clip which will be used to clip the rendering only to the extent of
			the camera. */

};
