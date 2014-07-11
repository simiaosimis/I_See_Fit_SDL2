#include "StateGame.h"

StateGame::~StateGame(){
	// Should be called in each state unload.
	cleanEntities();
}

void StateGame::addEntity(GameObject* const gameObject_) {
	this->gameObjects.push_back(gameObject_);
}

void StateGame::cleanEntities() {
	for(auto gameObject : this->gameObjects){
		delete gameObject;
		gameObject = nullptr;
	}

	this->gameObjects.clear();
}
