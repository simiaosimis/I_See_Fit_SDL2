#pragma once

#include <string>

namespace sdl2engine {

class Music;
class SoundEffect;

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
		AudioHandler() = default;

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
		* @brief Plays music from path.
		*
		* @note Will warn if there is no music loaded.
		*
		* @param path : The path to the desired music.
		*/
		void PlayMusic(const std::string& path);

		/**
		* @brief Plays music from path.
		*
		* @note Will warn if there is no music loaded.
		*
		* @param path : The path to the desired music.
		* @param times : Times to loop the song (1+).
		*/
		void PlayMusic(const std::string& path, const int times);

		/**
		* @brief Stops playing the current music.
		*/
		void StopMusic();

		static constexpr int k_infinite_loop = -1;
		static constexpr int k_all_channels = -1;
		static constexpr int k_any_channel = -1;
};

} // namespace sdl2engine
