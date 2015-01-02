#pragma once

#include "SDL_Libs.h"
#include "Sprite.h"
#include <string>

/**
* Base class for all game objects (gameObjects).
* The entity contains the (x,y) position, width and height, and a sprite.
*/
class GameObject {

	public:
		/**
		* The destructor.
		*/
		virtual ~GameObject();

		/**
		* Updates the entity.
		* Pure virtual function. Purpose is to update whatever is necessary, relative to the
		* 	entity.
		* @param dt_ : Delta time. Time elapsed between one frame and the other.
		*/
		virtual void update(const double dt_) = 0;

		/**
		* Renders the entity.
		* Pure virtual function. Purpose is to copy the entity's texture onto the renderer.
		* @note Usually just calls the render method from the Sprite class.
		* @param cameraX_ : The x position of the camera.
		* @param cameraY_ : The y position of the camera.
		*/
		virtual void render(const double cameraX_, const double cameraY_) = 0;

		/**
		* @return The GameObject width.
		*/
		unsigned int getWidth();

		/**
		* @return The GameObject height.
		*/
		unsigned int getHeight();

		/**
		* @return The GameObject::animationClip.
		*/
		SDL_Rect& getAnimationClip();

		SDL_Rect& getBoundingBox();

		double x; /**< The position in the x axis. */
		double y; /**< The position in the y axis. */
		bool isRight; /**< The direction in the x axis. */

	protected:
		/**
		* The constructor.
		* Initializes all the attributes.
		* @param x_ : position in x axis.
		* @param y_ : position in y axis.
		* @param sprite_ : which sprite to use.
		*/
		GameObject(const double x_, const double y_, const std::string& path_);

		/**
		* The constructor.
		* Initializes all the attributes.
		* @param x_ : position in x axis.
		* @param y_ : position in y axis.
		*/
		GameObject(const double x_, const double y_);

		Sprite* sprite; /**< The Sprite attributed to the entity. */
		unsigned int width; /**< The entitys width, from its sprite. */
		unsigned int height; /**< The entitys height, from its sprite. */
		SDL_Rect animationClip; /**< The current clip on the spritesheet, to determine animation. */
		SDL_Rect boundingBox;

};
