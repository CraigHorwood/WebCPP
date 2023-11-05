#ifndef _GAME_H
#define _GAME_H

#include "GLFW/glfw3.h"
#include "State.h"

class Game {
public:
	void init();
	void mainLoop();
	void shutdown();
	void keyDown(int);
	void keyUp(int);
	void mouseUp();
	void mouseDown();
	void mouseMoved(double, double);
	bool currentKeys[GLFW_KEY_LAST + 1];
	double xMouse, yMouse;
private:
	void tick();
	void render();
	bool lastKeys[GLFW_KEY_LAST + 1];
	double xMouseLast, yMouseLast;
	bool mouseIsDown, mouseWasDown;
	State* state;
protected:
};

#endif