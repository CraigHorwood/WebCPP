#include "Assets.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"

Shader* Assets::spriteShader;
Texture* Assets::tilesTexture;
Texture* Assets::entitiesTexture;

void Assets::loadAll() {
	spriteShader = new Shader("assets/shaders/sprite.sdr");
	spriteShader->getUniformLocation("projectionMatrix");
	tilesTexture = new Texture("assets/textures/tiles.png");
	entitiesTexture = new Texture("assets/textures/entities.png");
}

void Assets::deleteAll() {
	delete spriteShader;
	delete tilesTexture;
	delete entitiesTexture;
}