#include "engine/StateGame.h"

StateGame::~StateGame() {

}

void StateGame::unload() {
	cleanGameObjects();
}

void StateGame::addGameObject(GameObject* const gameObject_) {
	this->gameObjects.push_back(gameObject_);
}

void StateGame::cleanGameObjects() {
	for(auto gameObject : this->gameObjects) {
		delete gameObject;
		gameObject = nullptr;
	}

	this->gameObjects.clear();
}
