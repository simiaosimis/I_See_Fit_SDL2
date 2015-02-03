#pragma once

#include <string>

namespace sdl2engine {

static constexpr int k_infinite_loop = -1; /**< Represents infinite looping of an audio. */

/**
* @brief Distinguishes between the two types of audio.
*/
enum class AudioType {
	Music,
	SoundEffect
};

/**
* @brief Static class that handles all the audio in the game.
*
* AudioMusic or AudioHandler<AudioType::Music>
* AudioSfx or AudioHandler<AudioType::SoundEffect>
*
* @todo Add support for multiple music. Example: you pause the game, the game music pauses, and
* 	the pause menu plays a different music. When you unpause, it resumes the game music.
*/
template <AudioType type>
class AudioHandler final {

	public:
		/**
		* @brief Plays an audio a given amount of times.
		*
		* @param path : The path to the desired audio.
		* @param times : The amount of times to loop the sound effect. Use k_infinite_loop for
		*	infinite looping.
		*/
		static void Play(const std::string& path, const int times);

		/**
		* @brief Sets the volume for the audio.
		*
		* @param percent : The volume percentage (0-100).
		*/
		static void SetVolume(const int percent);

		/**
		* @brief Pauses audio.
		*/
		static void Pause();

		/**
		* @brief Resumes audio.
		*/
		static void Resume();

		/**
		* @brief Stops playing the current audio.
		*/
		static void Stop();

		/**
		* @brief Gradually fades audio out.
		*
		* The audio will be stopped after completely fading out.
		*
		* @param seconds : The amount in seconds over which the audio will fade out.
		*/
		static void FadeOut(const double seconds);

		/**
		* @return True if the audio has faded away.
		*
		* @todo Figure out a way to indicate that sound effects channels have been faded out.
		*/
		static bool FadedOut();
};

using AudioSfx = AudioHandler<AudioType::SoundEffect>;
using AudioMusic = AudioHandler<AudioType::Music>;

} // namespace sdl2engine
