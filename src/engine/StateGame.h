#pragma once

#include <vector>
#include "engine/GameObject.h"

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
		* Purpose is to unload whatever was previously loaded.
		*/
		virtual void unload() = 0;

		/**
		* Renders the state.
		* Pure virtual function.
		*/
		virtual void render() = 0;

		/**
		* Adds a GameObject to the gameObjects vector.
		*/
		void addGameObject(GameObject* const gameObject_);

		/**
		* Deletes all the gameObjects inside the gameObjects vector.
		*/
		void cleanGameObjects();

	protected:
		std::vector<GameObject*> gameObjects; /**< List of all the GameObjects in the state. */

};
