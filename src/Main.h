#ifndef _MAIN_H
#define _MAIN_H
#include "GLFW/glfw3.h"

typedef struct Context {
	bool shutdown;
	GLFWwindow* window;
} Context;

void init(void* unused);
void mainLoop();
void shutdown();

#endif