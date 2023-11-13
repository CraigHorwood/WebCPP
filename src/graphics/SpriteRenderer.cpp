#include "SpriteRenderer.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "Shader.h"
#include "Texture.h"

#define addVertex(x, y, u, v, r, g, b, a) vertices[offs++] = (x);\
	vertices[offs++] = (y);\
	vertices[offs++] = (u);\
	vertices[offs++] = (v);\
	vertices[offs++] = (r);\
	vertices[offs++] = (g);\
	vertices[offs++] = (b);\
	vertices[offs++] = (a);

using namespace std;

SpriteRenderer::SpriteRenderer() : Renderer() {
	cout << "Initialsing sprite renderer" << endl;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	uint16_t indices[MAX_SPRITES * 6];
	for (uint16_t i = 0; i < MAX_SPRITES; i++) {
		indices[i * 6] = i * 4;
		indices[i * 6 + 1] = i * 4 + 1;
		indices[i * 6 + 2] = i * 4 + 2;
		indices[i * 6 + 3] = i * 4 + 2;
		indices[i * 6 + 4] = i * 4 + 3;
		indices[i * 6 + 5] = i * 4;
	}
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(ATTR_POS);
	glEnableVertexAttribArray(ATTR_UV);
	glEnableVertexAttribArray(ATTR_COL);

	shader = nullptr;
	texture = nullptr;
	spriteCount = 0;

	for (int i = 0; i < 16; i++) {
		projectionMatrix[i] = 0.0f;
	}
	projectionMatrix[0] = 1.0f / 160.0f;
	projectionMatrix[5] = -1.0f / 140.0f;
	projectionMatrix[10] = -1.0f;
	projectionMatrix[12] = -1.0f;
	projectionMatrix[13] = 1.0f;
	projectionMatrix[15] = 1.0f;
}

SpriteRenderer::~SpriteRenderer() {
	cout << "Destroying sprite renderer" << endl;
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

void SpriteRenderer::begin(Shader* shader, Texture* texture) {
	if (this->shader != shader) {
		this->shader = shader;
		if (shader != nullptr) {
			shader->bind();
			shader->setUniformMatrix4f("projectionMatrix", projectionMatrix);
		}
	}
	if (this->texture != texture) {
		this->texture = texture;
		if (texture != nullptr) {
			texture->bind();
		}
	}
	spriteCount = 0;
}

void SpriteRenderer::draw(float x, float y, float uo, float vo, float w, float h) {
	if (spriteCount == MAX_SPRITES) {
		end();
		begin(shader, texture);
	}

	const float u0 = uo / texture->width;
	const float v0 = vo / texture->height;
	const float u1 = (uo + w) / texture->width;
	const float v1 = (vo + h) / texture->height;
	int offs = spriteCount * FLOATS_PER_VERTEX * 4;
	addVertex(x, y, u0, v0, 1.0f, 1.0f, 1.0f, 1.0f);
	addVertex(x, y + h, u0, v1, 1.0f, 1.0f, 1.0f, 1.0f);
	addVertex(x + w, y + h, u1, v1, 1.0f, 1.0f, 1.0f, 1.0f);
	addVertex(x + w, y, u1, v0, 1.0f, 1.0f, 1.0f, 1.0f);
	spriteCount++;
}

void SpriteRenderer::end() {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(ATTR_POS, 2, GL_FLOAT, GL_FALSE, FLOATS_PER_VERTEX * sizeof(float), (void*) 0);
	glVertexAttribPointer(ATTR_UV, 2, GL_FLOAT, GL_FALSE, FLOATS_PER_VERTEX * sizeof(float), (void*) (2 * sizeof(float)));
	glVertexAttribPointer(ATTR_COL, 3, GL_FLOAT, GL_FALSE, FLOATS_PER_VERTEX * sizeof(float), (void*) (4 * sizeof(float)));
	glBufferSubData(GL_ARRAY_BUFFER, 0, spriteCount * FLOATS_PER_VERTEX * sizeof(float) * 4, vertices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glDrawElements(GL_TRIANGLES, spriteCount * 6, GL_UNSIGNED_SHORT, NULL);
}