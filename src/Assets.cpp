#include "Assets.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"

Shader* Assets::spriteShader;
Texture* Assets::tilesTexture;

void Assets::loadAll() {
	spriteShader = new Shader("assets/shaders/sprite.sdr");
	spriteShader->getUniformLocation("projectionMatrix");
	tilesTexture = new Texture("assets/textures/tiles.png");
}

void Assets::deleteAll() {
	delete spriteShader;
	delete tilesTexture;
}