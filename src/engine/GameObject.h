#pragma once

#include <SDL2/SDL.h>
#include <string>

namespace sdl2engine {

class Sprite;

/**
* Base class for all game objects (gameObjects).
* The entity contains the (x,y) position, width and height, and a sprite.
*/
class GameObject {

	public:
		/**
		* The destructor.
		*/
		virtual ~GameObject() {};

		/**
		* @brief Updates the entity.
		*
		* Pure virtual function. Purpose is to update whatever is necessary, relative to the
		* 	entity.
		*
		* @param dt : Delta time. Time elapsed between one frame and the other.
		*/
		virtual void Update(const double dt) = 0;

		/**
		* Renders the entity.
		* Pure virtual function. Purpose is to copy the entity's texture onto the renderer.
		* @note Usually just calls the render method from the Sprite class.
		* @param camera_x : The x position of the camera.
		* @param camera_y : The y position of the camera.
		*/
		virtual void Render(const double camera_x, const double camera_y) = 0;

		/**
		* @return The x axis position.
		*/
		double X();

		/**
		* @return The y axis position.
		*/
		double Y();

		/**
		* @return The GameObject width.
		*/
		int Width();

		/**
		* @return The GameObject height.
		*/
		int Height();

		/**
		* @return The GameObject::m_animation_clip.
		*/
		SDL_Rect& AnimationClip();

		/**
		* @return The game object's bounding box.
		*/
		SDL_Rect& BoundingBox();

		/**
		* @brief Set the x axis position.
		*/
		void SetX(const double x);

		/**
		* @brief Set the y axis position.
		*/
		void SetY(const double y);

	protected:
		/**
		* The constructor.
		* Initializes all the attributes.
		* @param x : position in x axis.
		* @param y : position in y axis.
		* @param path : path for which sprite to use.
		*/
		GameObject(const double x, const double y, const std::string& path);

		double m_x; /**< The position in the x axis. */
		double m_y; /**< The position in the y axis. */
		Sprite* m_sprite; /**< The Sprite attributed to the entity. */
		int m_width; /**< The entitys width, from its sprite. */
		int m_height; /**< The entitys height, from its sprite. */
		SDL_Rect m_animation_clip; /**< The current clip on the spritesheet, to determine animation. */
		SDL_Rect m_bounding_box;
};

} // namespace sdl2engine
