#include "Game.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <cstring>
#include "state/GameState.h"

void Game::init() {
	memset(lastKeys, false, (GLFW_KEY_LAST + 1) * sizeof(bool));
	memset(currentKeys, false, (GLFW_KEY_LAST + 1) * sizeof(bool));
	xMouse = 0;
	yMouse = 0;
	xMouseLast = 0;
	yMouseLast = 0;
	mouseIsDown = false;
	mouseWasDown = false;
	state = new GameState();
}

void Game::mainLoop(double& unprocessedTime) {
	while (unprocessedTime > 0.0) {
		tick();
		unprocessedTime -= 1.0 / 60.0;
	}
	render();
}

void Game::shutdown() {
	delete state;
}

void Game::tick() {
	state->tick();
	memcpy(lastKeys, currentKeys, (GLFW_KEY_LAST + 1) * sizeof(bool));
	xMouseLast = xMouse;
	yMouseLast = yMouse;
	mouseWasDown = mouseIsDown;
}

void Game::render() {
	glClear(GL_COLOR_BUFFER_BIT);
	state->render();
}

void Game::keyDown(int key) {
	if (state) {
		state->keyDown(key);
	}
}

void Game::keyUp(int key) {
	if (state) {
		state->keyUp(key);
	}
}

void Game::mouseDown() {
	mouseIsDown = true;
	if (state) {
		state->mouseDown(xMouse, yMouse);
	}
}

void Game::mouseUp() {
	mouseIsDown = false;
	if (state) {
		state->mouseUp(xMouse, yMouse);
	}
}

void Game::mouseMoved(double x, double y) {
	xMouse = x;
	yMouse = y;
	if (state) {
		state->mouseMoved(xMouse, yMouse, xMouse - xMouseLast, yMouse - yMouseLast);
	}
}