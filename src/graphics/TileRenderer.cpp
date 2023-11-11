#include "TileRenderer.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>

using namespace std;

TileRenderer::TileRenderer() : Renderer() {
	cout << "Initialsiing tile renderer" << endl;

	float vertices[12] = {
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
	};
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

TileRenderer::~TileRenderer() {
	glDeleteBuffers(1, &vbo);
}

void TileRenderer::updateTiles(uint8_t* tiles) {
	// Upload 300 bytes of tile data to the GPU
	// Only to be called on frames when tiles have been changed
}

void TileRenderer::renderTiles() {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// Bind tile shader
	glDrawArrays(GL_TRIANGLES, 0, 6);
}