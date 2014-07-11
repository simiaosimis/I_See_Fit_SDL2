#pragma once

#include "GameObject.h"
#include <vector>

/**
* Parent class for other game states.
*/
class StateGame {

	public:
		/**
		* The destructor.
		*/
		virtual ~StateGame();

		/**
		* Loads necessary objects.
		* Pure virtual function. Purpose is to load all things relevant to the state.
		*/
		virtual void load() = 0;

		/**
		* Update all gameObjects.
		* Pure virtual function. Purpose is to update all the gameObjects in the vector.
		* @param dt_ : Delta time. Time elapsed between one frame and the other.
		*/
		virtual void update(const double dt_) = 0;

		/**
		* Unloads necessary objects.
		* Pure virtual function. Purpose is to unload whatever was previously loaded.
		*/
		virtual void unload() = 0;

		/**
		* Renders the level.
		* Always render on 0,0 position.
		* @see Sprite::render()
		*/
		virtual void render() = 0;

		/**
		* Adds an entity to the vector.
		*/
		void addEntity(GameObject* const entity);

		/**
		* Deletes all the gameObjects inside the vector.
		*/
		void cleanEntities();

	protected:
		std::vector<GameObject*> gameObjects; /**< List of all the gameObjects in the state. */

};
