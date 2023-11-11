#ifndef _LEVEL_H
#define _LEVEL_H

#include "../graphics/SpriteRenderer.h"
#include <inttypes.h>

class Level {
public:
	Level();
	~Level();
	void tick();
	void renderSprites(SpriteRenderer&);
	uint8_t getTile(int, int);
private:
	uint8_t tiles[300];
protected:
};

#endif