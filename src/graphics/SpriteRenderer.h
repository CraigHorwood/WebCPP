#ifndef _SPRITE_RENDERER_H
#define _SPRITE_RENDERER_H

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"

#define MAX_SPRITES 1024
#define FLOATS_PER_VERTEX 8

class SpriteRenderer : public Renderer {
public:
	SpriteRenderer();
	~SpriteRenderer();
	void begin(Shader*, Texture*);
	void draw(float, float, float, float, float, float);
	void end();
private:
	Shader* shader;
	Texture* texture;
	GLuint vbo, ibo;
	float vertices[MAX_SPRITES * FLOATS_PER_VERTEX];
	int spriteCount;
protected:
};

#endif