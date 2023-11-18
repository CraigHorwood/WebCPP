#ifndef _ENTITY_H
#define _ENTITY_H

#include "../graphics/SpriteRenderer.h"
#include "../level/Level.h"
#include <queue>

#define HIT_BOX_EPSILON 0.0078125f

typedef struct HitBox {
	float x, y, w, h;
} HitBox;

typedef struct HitResult {
	uint8_t tile;
	HitBox hitBox;
} HitResult;

enum CollisionPhase {
	x, y
};

class Entity {
public:
	Entity(Level*, HitBox);
	virtual void tick() {}
	virtual void render(SpriteRenderer&) {}
	float x, y, xVel, yVel;
	bool onGround;
	HitBox hitBox;
private:
	void checkTileCollisions(CollisionPhase);
protected:
	void move();
	void hitTile(const HitResult&, CollisionPhase);
	Level* level;
};

#endif