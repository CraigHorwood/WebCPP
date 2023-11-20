#include "GameState.h"
#include <iostream>

using namespace std;

GameState::GameState() {
	cout << "Initialising game state" << endl;
	level = new Level();
}

GameState::~GameState() {
	cout << "Destroying game state" << endl;
	delete level;
}

void GameState::tick() {
	level->tick();
}

void GameState::render() {
	level->renderSprites(spriteRenderer);
}