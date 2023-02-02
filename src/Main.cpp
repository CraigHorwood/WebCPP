#include "Main.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#ifdef __EMSCRIPTEN__
#include "emscripten.h"
#include "emscripten/html5.h"
#endif

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

static Context context;
static Context* g = &context;

using namespace std;

void init(void* unused) {
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	srand(time(NULL));
	rand();
}

void mainLoop() {
	glClearColor((rand() & 255) / 255.0f, (rand() & 255) / 255.0f, (rand() & 255) / 255.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
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
	// Shutdown
}

int main(int argc, char* argv[]) {
	if (!glfwInit()) {
		cout << "Failed to initialise GLFW." << endl;
		return 1;
	}

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	g->window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Web C++", NULL, NULL);
    if (g->window == NULL)
    {
        cout << "Failed to open GLFW window." << endl;
        glfwTerminate();
        return 1;
    }
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
	while (1) {
		mainLoop();
		if (g->shutdown) {
			break;
		}
	}
	shutdown();
#endif

	glfwTerminate();
	return 0;
}