#pragma once

#include "engine/StateGame.h"
#include "graphics/Sprite.h"
#include "engine/Animation.h"

/**
* The state used for testing the engine.
* For now is just a placeholder, might have different states to test different things later.
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
		* Loads the state.
		* 
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
		*
		*/
		virtual void render();

	private:
		Sprite* image;
		Animation* animation;
		SDL_Rect animationClip;

};
