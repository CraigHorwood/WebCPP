#ifndef _ENTITY_H
#define _ENTITY_H

#include "../graphics/SpriteRenderer.h"
#include "../level/Level.h"

typedef struct HitBox {
	float xo, yo, w, h;
} HitBox;

typedef struct HitResult {
	uint8_t tile;
	float x, y, w, h;
} HitResult;

class Entity {
public:
	Entity(Level*, HitBox);
	virtual void tick() {}
	virtual void render(SpriteRenderer&) {}
	float x, y, xVel, yVel;
	bool onGround;
	HitBox hitBox;
private:
	HitResult hitTile();
protected:
	void move();
	Level* level;
};

#endif