#include "Level.h"
#include "../graphics/SpriteRenderer.h"
#include "../entity/Entity.h"
#include "../entity/Player.h"
#include "../Assets.h"
#include <cstring>
#include <set>

using namespace std;

Level::Level() {
	memset(tiles, 0, sizeof(tiles));
	for (int y = 10; y < 15; y++) {
		for (int x = 0; x < 120; x++) {
			tiles[x + y * 20] = 1;
		}
	}
	xTest = 0.0f;
	player = new Player(this, 128.0f, 64.0f);
	addEntity(player);
}

Level::~Level() {
	for (Entity* e : entities) {
		delete e;
	}
}

void Level::addEntity(Entity* e) {
	entities.push_back(e);
}

void Level::tick() {
	xTest += 0.5f;
	player->tick(false, false, false, false, false, false, false);
	for (Entity* e : entities) {
		e->tick();
	}
}

void Level::renderSprites(SpriteRenderer& renderer) {
	renderer.begin(Assets::spriteShader, Assets::tilesTexture);
	renderer.draw(64.0f + xTest, 64.0f, 16.0f, 0.0f, 16.0f, 16.0f);
	renderer.end();
	for (Entity* e : entities) {
		e->render(renderer);
	}
}

uint8_t Level::getTile(int xt, int yt) {
	if (xt >= 0 && yt >= 0 && xt < 20 && yt < 15) {
		return tiles[xt + yt * 20];
	}
	return 0;
}

set<Entity*>& Level::getEntities(const HitBox& hitBox) {
	hitEntities.clear();
	const float x0 = x + hitBox.x;
	const float y0 = y + hitBox.y;
	const float x1 = x + hitBox.x + hitBox.w - HIT_BOX_EPSILON;
	const float y1 = y + hitBox.y + hitBox.h - HIT_BOX_EPSILON;
	const int xt0 = (int) x0;
	const int yt0 = (int) y0;
	const int xt1 = (int) x1;
	const int yt1 = (int) y1;
	for (int yt = yt0; yt <= yt1; yt++) {
		for (int xt = xt0; xt <= xt1; xt++) {
			if (xt >= 0 && yt >= 0 && xt < 20 && yt < 15) {
				vector<Entity*>& cell = entityMap[xt + yt * 20];
				hitEntities.insert(cell.begin(), cell.end());
			}
		}
	}
	return hitEntities;
}