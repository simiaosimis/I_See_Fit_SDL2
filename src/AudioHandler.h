#pragma once

#ifndef MIX_LOOP
#define MIX_LOOP -1
#endif

#ifndef ALL_CHANNELS
#define ALL_CHANNELS -1
#endif

#include "SDL_Libs.h"
#include "Music.h"
#include "SoundEffect.h"
#include <string>
#include <vector>

/**
* The audio handler.
* Class that handles all the audio in the game.
* @todo Figure out the best way to design music logic apart from SFX logic.
* @todo Add support for multiple music. Example: you pause the game, the game music pauses, and
* 	the pause menu plays a different music. When you unpause, it resumes the game music.
*/
class AudioHandler {

	public:
		/**
		* The constructor.
		*/
		AudioHandler();

		/**
		* The destructor.
		*/
		~AudioHandler();

		/**
		* Changes current music.
		* Stops the music, sets it to the new one, and plays it.
		* @param path_ : The path to the desired music.
		* @param times_ : The amount of times to loop the music. Defaults to infinite looping.
		*/
		void changeMusic(const std::string& path_, const int times_ = MIX_LOOP);

		/**
		* Pushes a new sound effect onto the vector, and plays it.
		* @param path_ : The path to the desired sound effect.
		* @param times_ : The amount of times to loop the sound effect. Defaults to infinite
		* 	looping.
		*/
		void pushSoundEffect(const std::string& path_, const int times_ = 0);

		void pauseMusic();
		void pauseEffects();

		void resumeMusic();
		void resumeEffects();

		/**
		* Sets the volume for the music.
		* If the percent_ is over 100, will be set to 100.
		* @param percent_ : The volume percentage (0-100).
		*/
		void setVolumeMusic(const unsigned int percent_);

		/**
		* Sets the volume for the effects.
		* If the percent_ is over 100, will be set to 100.
		* @param percent_ : The volume percentage (0-100).
		*/
		void setVolumeEffects(const unsigned int percent_);

	private:
		/**
		* Plays the current effect.
		* @note Will warn if there is no effect loaded.
		* @param times_ : Times to loop the song. MIX_LOOP (or -1) for infinite looping.
		*/
		void playEffect(const int times_);

		/**
		* Stops playing the current music.
		*/
		void stopMusic();

		/**
		* Sets the current music.
		* If one already exists, frees it first.
		* @param path_ : The path to the desired music.
		*/
		void setCurrentMusic(const std::string& path_);

		/**
		* Plays the current music.
		* @note Will warn if there is no music loaded.
		* @param times_ : Times to loop the song. MIX_LOOP (or -1) for infinite looping.
		*/
		void playMusic(const int times_);

		void clearChannel(const int channel_);
		static void channelDone(int channel_);

		Music* currentMusic; /**< The current music that is playing. */
		std::vector<SoundEffect*> currentEffects; /**< The current effect that is playing. */

};
