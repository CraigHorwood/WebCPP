#ifndef _GAME_H
#define _GAME_H

class Game {
public:
	void init();
	void mainLoop();
	void shutdown();
	bool currentKeys[GLFW_KEY_LAST + 1];
	double xMouse, yMouse;
	bool mouseDown;
private:
	void tick();
	void render();
	bool lastKeys[GLFW_KEY_LAST + 1];
	double xMouseLast, yMouseLast;
	bool mouseWasDown;
protected:
};

#endif