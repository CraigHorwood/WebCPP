#include "Entity.h"

#define HIT_BOX_EPSILON 0.0078125f

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
	HitResult hit;
	x += xVel;
	hit = hitTile();
	if (hit.tile) {
		// Standard x axis solid clipping
		if (xVel > 0.0f) {
			x = hit.x - hitBox.w;
		} else if (xVel < 0.0f) {
			x = hit.x + hit.w;
		}
		xVel = 0.0f;
	}
	onGround = false;
	y += yVel;
	hit = hitTile();
	if (hit.tile) {
		// Standard y axis solid clipping
		if (yVel > 0.0f) {
			y = hit.y - hitBox.h;
			onGround = true;
		} else if (yVel < 0.0f) {
			y = hit.y + hit.h;
		}
		yVel = 0.0f;
	}
}

HitResult Entity::hitTile() {
	const float x0 = x + hitBox.xo;
	const float y0 = y + hitBox.yo;
	const float x1 = x + hitBox.xo + hitBox.w - HIT_BOX_EPSILON;
	const float y1 = y + hitBox.yo + hitBox.h - HIT_BOX_EPSILON;
	const int xt0 = (int) x0;
	const int yt0 = (int) y0;
	const int xt1 = (int) x1;
	const int yt1 = (int) y1;
	HitResult hit;
	hit.tile = 0;
	for (int yt = yt0; yt <= yt1; yt++) {
		for (int xt = xt0; xt <= xt1; xt++) {
			const uint8_t t = level->getTile(xt, yt);
			if (t == 1) {
				hit.tile = 1;
				hit.x = xt << 4;
				hit.y = yt << 4;
				hit.w = 16.0f;
				hit.h = 16.0f;
				return hit;
			}
		}
	}
	return hit;
}