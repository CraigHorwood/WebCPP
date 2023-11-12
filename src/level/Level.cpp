#include "Level.h"
#include "../graphics/SpriteRenderer.h"
#include "../Assets.h"
#include <cstring>

Level::Level() {
	memset(tiles, 0, sizeof(tiles));
	xTest = 0.0f;
}

Level::~Level() {
	//
}

void Level::tick() {
	xTest += 0.5f;
}

void Level::renderSprites(SpriteRenderer& renderer) {
	renderer.begin(Assets::spriteShader, Assets::tilesTexture);
	renderer.draw(64.0f + xTest, 64.0f, 16.0f, 0.0f, 16.0f, 16.0f);
	renderer.end();
}

uint8_t Level::getTile(int xt, int yt) {
	if (xt >= 0 && yt >= 0 && xt < 20 && yt < 15) {
		return tiles[xt + yt * 20];
	}
	return 0;
}