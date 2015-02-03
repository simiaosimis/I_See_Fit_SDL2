#pragma once

#include <SDL2/SDL_mixer.h>
#include <string>

namespace sdl2engine {

class SoundEffect {

	public:
		/**
		* @brief The constructor.
		*
		* @param path : The path to the sound effect file.
		*/
		explicit SoundEffect(const std::string& path);

		/**
		* @brief The destructor.
		*/
		~SoundEffect();

		// Not copyable and not moveable.
		SoundEffect(const SoundEffect&) = delete;
		SoundEffect& operator=(const SoundEffect&) = delete;
		SoundEffect(SoundEffect&&) = delete;
		SoundEffect& operator=(SoundEffect&&) = delete;

		/**
		* @return A pointer to the raw Mix_Chunk object.
		*/
		Mix_Chunk* MixChunk() const;

		/**
		* @return The path given to the constructor.
		*/
		std::string Path() const;

		/**
		* @return The channel being played in. Returns -1 on undefined channel.
		*/
		int Channel() const;

		/**
		* @brief Sets the channel being played in.
		*/
		void SetChannel(const int channel);

	private:
		int m_channel; /**< The channel on which its being played. */
		Mix_Chunk* const m_mix_chunk; /**< Sound effect data. */
		const std::string m_path; /**< Path to the sound effect file. */
};

} // namespace sdl2engine
