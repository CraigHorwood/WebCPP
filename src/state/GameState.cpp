#include "GameState.h"
#include <iostream>

using namespace std;

GameState::GameState() {
	cout << "Initialising game state" << endl;
}

GameState::~GameState() {
	cout << "Destroying game state" << endl;
}

void GameState::tick() {
	level.tick();
}

void GameState::render() {
	level.renderSprites(spriteRenderer);
}