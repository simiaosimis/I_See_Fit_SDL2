#pragma once

namespace sdl2engine {

/**
* @brief Handles the different SDL events.
*/
class EventHandler {

	public:
		/**
		* @brief The constructor.
		*/
		EventHandler();

		/**
		* @brief Main event handling method.
		*/
		void PollEvents();

		/**
		* @return EventHandler::m_quit_flagged
		*/
		bool QuitFlagged();

	private:
		bool m_quit_flagged; /**< If the quit signal was recieved or not. */
};

} // namespace sdl2engine
