#pragma once

#include <SDL2/SDL_mixer.h>
#include <string>
#include <vector>
#include "audio/Music.h"
#include "audio/SoundEffect.h"

/**
* Class that handles all the audio in the game.
*
* @todo Figure out the best way to design music logic apart from SFX logic.
* @todo Add support for multiple music. Example: you pause the game, the game music pauses, and
* 	the pause menu plays a different music. When you unpause, it resumes the game music.
* @todo Unecessary pointers?
*/
class AudioHandler {

	public:
		/**
		* @brief The constructor.
		*/
		AudioHandler();

		/**
		* @brief The destructor.
		*/
		~AudioHandler();

		/**
		* @brief Sets new music for given path, infinitely looping.
		*
		* Stops the music, sets it to the new one, and plays it as an infinite loop.
		*
		* @param path : The path to the desired music.
		*/
		void ChangeMusic(const std::string& path);

		/**
		* @brief Sets new music for given path.
		*
		* Stops the music, sets it to the new one, and plays it for the determined amount of
		* loops.
		*
		* @param path : The path to the desired music.
		* @param times : The amount of times to loop the music.
		*/
		void ChangeMusic(const std::string& path, const int times);

		/**
		* @brief Plays a sound effect once.
		*
		* @param path : The path to the desired sound effect.
		*/
		void PlaySoundEffect(const std::string& path);

		/**
		* @brief Plays a sound effect a given amount of times.
		*
		* Should only be used if you either want to play the effect 2+ times or infinitely, in
		* which case you should pass k_infinite_loop.
		*
		* @param path : The path to the desired sound effect.
		* @param times : The amount of times to loop the sound effect.
		*/
		void PlaySoundEffect(const std::string& path, const int times);

		/**
		* @brief Sets the volume for the music.
		*
		* @param percent : The volume percentage (0-100).
		*/
		void SetMusicVolume(const int percent);

		/**
		* @brief Sets the volume for the sound effects.
		*
		* @param percent : The volume percentage (0-100).
		*/
		void SetEffectsVolume(const int percent);

		/**
		* @brief Pauses the music.
		*/
		void PauseMusic();

		/**
		* @brief Pauses all sound effects.
		*/
		void PauseEffects();

		/**
		* @brief Resumes the music.
		*/
		void ResumeMusic();

		/**
		* @brief Resumes all sound effects.
		*/
		void ResumeEffects();

	private:
		/**
		* @brief Plays the current music as an infinite loop.
		*
		* @note Will warn if there is no music loaded.
		*/
		void PlayMusic();

		/**
		* @brief Plays the current music.
		*
		* @note Will warn if there is no music loaded.
		*
		* @param times : Times to loop the song (1+).
		*/
		void PlayMusic(const int times);

		/**
		* @brief Stops playing the current music.
		*/
		void StopMusic();

		/**
		* @brief Sets the current music.
		*
		* If one already exists, frees it first.
		*
		* @param path : The path to the desired music.
		*/
		void SetMusic(const std::string& path);

		/**
		* @brief Removes any sound effects from a given channel.
		*
		* @param channel : The channel to remove all sound effects from.
		*/
		void ClearChannel(const int channel);

		/**
		* @brief Callback that gets called everytime a channel is done playing.
		*
		* @note Calls AudioHandler::ClearChannel.
		*/
		static void ChannelDone(const int channel);

		static constexpr int k_infinite_loop = -1;
		static constexpr int k_all_channels = -1;
		static constexpr int k_any_channel = -1;

		Music* m_current_music; /**< The current music that is playing. */
		std::vector<SoundEffect*> m_effects; /**< The current effects that are playing. */
};
