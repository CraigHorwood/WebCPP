#include "Level.h"
#include "../graphics/SpriteRenderer.h"
#include <cstring>

Level::Level() {
	memset(tiles, 0, sizeof(tiles));
}

Level::~Level() {
	//
}

void Level::tick() {
	//
}

void Level::renderSprites(SpriteRenderer& renderer) {
	//
}

uint8_t Level::getTile(int xt, int yt) {
	if (xt >= 0 && yt >= 0 && xt < 20 && yt < 15) {
		return tiles[xt + yt * 20];
	}
	return 0;
}