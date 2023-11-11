#ifndef _TILE_RENDERER_H
#define _TILE_RENDERER_H

#include "GLFW/glfw3.h"
#include "Renderer.h"

class TileRenderer : Renderer {
public:
	TileRenderer();
	~TileRenderer();
	void updateTiles(uint8_t*);
	void renderTiles();
private:
	GLuint vbo;
protected:
};

#endif