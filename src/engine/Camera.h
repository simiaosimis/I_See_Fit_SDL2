#pragma once

#include <SDL2/SDL.h>

namespace sdl2engine {

class GameObject;

/**
* The camera class.
* Contains all the relevant implementation relative to the camera.
*/
class Camera {

	public:
		/**
		* The constructor.
		* Initializes all the attributes.
		* @param game_object : The GameObject to centralize the camera on.
		*/
		explicit Camera(GameObject* const game_object);

		/**
		* The destructor.
		*/
		~Camera();

		/**
		* Updates the camera.
		* @see Camera::UpdatePosition
		* Centralizes the player on the screen.
		*/
		void Update();

		/**
		* Changes the entity to centralize upon.
		* @param entity_ : The entity to centralize the camera on.
		*/
		void CentralizeOn(GameObject* const game_object);

		/**
		* @return The camera clip (an SDL_Rect).
		*/
		SDL_Rect& Clip();

		/**
		* @param width,height : Tells the camera what the width and height of the level is.
		* @see Level::update()
		*/
		void SetLevelDimensions(const int width, const int height);

	private:
		/**
		* Updates the cameras position.
		* Based on the players position, change cameras position.
		*/
		void UpdatePosition();

		GameObject* m_game_object; /**< Reference to the entity. */
		int m_level_width; /**< The width of the level. */
		int m_level_height; /**< The height of the level. */
		SDL_Rect m_clip; /**< Clip which will be used to clip the rendering only to the extent of
			the camera. */
};

} // namespace sdl2engine
