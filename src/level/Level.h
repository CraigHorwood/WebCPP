#ifndef _LEVEL_H
#define _LEVEL_H

#include "../graphics/SpriteRenderer.h"

class Level {
public:
	Level();
	~Level();
	void tick();
	void renderSprites(SpriteRenderer&);
private:
	unsigned char tiles[300];
protected:
};

#endif