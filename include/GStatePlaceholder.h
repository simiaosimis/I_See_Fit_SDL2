#pragma once

#include "StateGame.h"
#include "Sprite.h"

/**
* The state for the initial splash screen.
* Game state that will contain the initial splash images, before the main menu state is called.
*/
class GStatePlaceholder : public StateGame {

	public:
		/**
		* The constructor.
		* Initializes all the attributes.
		*/
		GStatePlaceholder();

		/**
		* The destructor.
		*/
		virtual ~GStatePlaceholder();

		/**
		* Loads the level.
		* From the Splash.lua script, loads all the necessary objects.
		*/
		virtual void load();

		/**
		* Updates the objects within the StateGame.
		* @param dt_ : Delta time. Time elapsed between one frame and the other.
		*/
		virtual void update(const double dt_);

		/**
		* Unloads everything that was loaded.
		* @see GStatePlaceholder::load
		*/
		virtual void unload();

		/**
		* Renders the state.
		* Always renders on 0,0 position.
		* @see Sprite::render
		*/
		virtual void render();

};
