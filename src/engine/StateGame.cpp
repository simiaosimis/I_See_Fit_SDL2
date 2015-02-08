#include "engine/StateGame.h"
#include "engine/GameObject.h"

namespace sdl2engine {

void StateGame::AddGameObject(GameObject* const game_object) {
	m_game_objects.push_back(game_object);
}

} // namespace sdl2engine
