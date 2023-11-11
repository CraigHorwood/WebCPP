
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Main.h"
#include "Game.h"
#include "Common.h"
#include <iostream>
#ifdef __EMSCRIPTEN__
#include "emscripten.h"
#include "emscripten/html5.h"
#endif

#define GAME_INIT_WINDOW_WIDTH 960
#define GAME_INIT_WINDOW_HEIGHT 840

static Context context;
static Context* g = &context;

static Game game;

using namespace std;

void init(void* unused) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glViewport(0, 0, GAME_INIT_WINDOW_WIDTH, GAME_INIT_WINDOW_HEIGHT);
	game.init();
}

void mainLoop() {
	game.mainLoop();
	glfwSwapBuffers(g->window);
	glfwPollEvents();
	if (glfwWindowShouldClose(g->window)) {
		g->shutdown = true;
	}
#ifdef __EMSCRIPTEN__
	if (g->shutdown) {
		g->shutdown = false;
		shutdown();
		emscripten_cancel_main_loop();
		emscripten_push_main_loop_blocker(init, NULL);
		emscripten_set_main_loop(mainLoop, 0, 1);
	}
#endif
}

void shutdown() {
	game.shutdown();
}

inline void updateKey(int key, bool down) {
	if (key >= 0 && key <= GLFW_KEY_LAST) {
		game.currentKeys[key] = down;
	}
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	switch (action) {
		case GLFW_PRESS:
			updateKey(key, true);
			game.keyDown(key);
			break;
		case GLFW_RELEASE:
			updateKey(key, false);
			game.keyUp(key);
			break;
		default:
			break;
	}	
}

static void mousePosCallback(GLFWwindow* window, double x, double y) {
	game.mouseMoved(x, y);
}

static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		switch (action) {
			case GLFW_PRESS:
				game.mouseDown();
				break;
			case GLFW_RELEASE:
				game.mouseUp();
				break;
			default:
				break;
		}
	}
}

int main(int argc, char* argv[]) {
	if (!glfwInit()) {
		cout << "Failed to initialise GLFW." << endl;
		return 1;
	}

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	g->window = glfwCreateWindow(GAME_INIT_WINDOW_WIDTH, GAME_INIT_WINDOW_HEIGHT, "Diamond Gun", NULL, NULL);
    if (g->window == NULL)
    {
        cout << "Failed to open GLFW window." << endl;
        glfwTerminate();
        return 1;
    }
	glfwSetKeyCallback(g->window, keyCallback);
	glfwSetCursorPosCallback(g->window, mousePosCallback);
	glfwSetMouseButtonCallback(g->window, mouseButtonCallback);
    glfwMakeContextCurrent(g->window);

    if (glewInit() != GLEW_OK)
    {
        cout << "Failed to initialise GLEW." << endl;
        glfwTerminate();
        return 1;
    }

#ifdef __EMSCRIPTEN__
	emscripten_push_main_loop_blocker(init, NULL);
	emscripten_set_main_loop(mainLoop, 0, 1);
#else
	init(NULL);
	while (!g->shutdown) {
		mainLoop();
	}
	shutdown();
#endif

	glfwTerminate();
	return 0;
}