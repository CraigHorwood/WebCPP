#include "Entity.h"

Entity::Entity(Level* level, HitBox hitBox) {
	this->level = level;
	this->hitBox = hitBox;
	x = 0.0f;
	y = 0.0f;
	xVel = 0.0f;
	yVel = 0.0f;
	onGround = false;
}

// Move entity x,y by xVel,yVel and collide with level tiles
void Entity::move() {
	x += xVel;
	checkTileCollisions(CollisionPhase::x);
	onGround = false;
	y += yVel;
	checkTileCollisions(CollisionPhase::y);
}

void Entity::checkTileCollisions(CollisionPhase phase) {
	const float x0 = x + hitBox.x;
	const float y0 = y + hitBox.y;
	const float x1 = x + hitBox.x + hitBox.w - HIT_BOX_EPSILON;
	const float y1 = y + hitBox.y + hitBox.h - HIT_BOX_EPSILON;
	const int xt0 = (int) x0;
	const int yt0 = (int) y0;
	const int xt1 = (int) x1;
	const int yt1 = (int) y1;
	HitResult hit;
	for (int yt = yt0; yt <= yt1; yt++) {
		for (int xt = xt0; xt <= xt1; xt++) {
			const uint8_t t = level->getTile(xt, yt);
			if (t == 1) {
				hit.tile = 1;
				hit.hitBox.x = xt << 4;
				hit.hitBox.y = yt << 4;
				hit.hitBox.w = 16.0f;
				hit.hitBox.h = 16.0f;
				hitTile(hit, phase);
			}
		}
	}
}

// TODO: Pluggable tile collision behaviour
void Entity::hitTile(const HitResult& hit, CollisionPhase phase) {
	switch (hit.tile) {
		case 1: {
			if (phase == CollisionPhase::x) {
				// Standard x axis solid clipping
				if (xVel > 0.0f) {
					x = hit.hitBox.x - hitBox.w;
				} else if (xVel < 0.0f) {
					x = hit.hitBox.x + hit.hitBox.w;
				}
				xVel = 0.0f;
			} else if (phase == CollisionPhase::y) {
				// Standard y axis solid clipping
				if (yVel > 0.0f) {
					y = hit.hitBox.y - hitBox.h;
					onGround = true;
				} else if (yVel < 0.0f) {
					y = hit.hitBox.y + hit.hitBox.h;
				}
				yVel = 0.0f;
			}
			break;
		}
		default:
			break;
	}
}