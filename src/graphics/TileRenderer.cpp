#include "TileRenderer.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "Shader.h"

using namespace std;

TileRenderer::TileRenderer() : Renderer() {
	cout << "Initialsiing tile renderer" << endl;

	float vertices[24] = {
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 15.0f,
		1.0f, 0.0f, 20.0f, 15.0f,
		1.0f, 0.0f, 20.0f, 15.0f,
		1.0f, 1.0f, 20.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
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
	glVertexAttribPointer(ATTR_POS, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) 0);
	glVertexAttribPointer(ATTR_UV, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) (2 * sizeof(float)));
	// Bind tile shader
	glDrawArrays(GL_TRIANGLES, 0, 6);
}