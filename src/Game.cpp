#include "Game.h"
#include "GLFW/glfw3.h"
#include <cstring>

void Game::init() {
	memset(lastKeys, false, (GLFW_KEY_LAST + 1) * sizeof(bool));
	memset(currentKeys, false, (GLFW_KEY_LAST + 1) * sizeof(bool));
	xMouse = 0;
	yMouse = 0;
	xMouseLast = 0;
	yMouseLast = 0;
	mouseDown = false;
	mouseWasDown = false;
}

void Game::mainLoop() {
	// Tick for length of passed time
	// Render
}

void Game::shutdown() {
	// Delete
}

void Game::tick() {
	// Game update
	memcpy(lastKeys, currentKeys, (GLFW_KEY_LAST + 1) * sizeof(bool));
	xMouseLast = xMouse;
	yMouseLast = yMouse;
	mouseWasDown = mouseDown;
}

void Game::render() {
	glClear(GL_COLOR_BUFFER_BIT);
}