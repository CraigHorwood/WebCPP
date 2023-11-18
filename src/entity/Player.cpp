#include "Player.h"
#include "../graphics/SpriteRenderer.h"
#include "../level/Level.h"

Player::Player(Level* level, float x, float y) : Entity(level, { 0.0f, 0.0f, 16.0f, 24.0f }) {
	this->x = x;
	this->y = y;
}

void Player::tick(bool left, bool right, bool up, bool down, bool jump, bool shoot, bool change) {
	xVel = 0.0f;
	if (left) {
		xVel = -2.0f;
	} else if (right) {
		xVel = 2.0f;
	}
	if (jump && onGround) {
		yVel = -8.0f;
	}
	move();
	yVel += 0.25f;
}

void Player::render(SpriteRenderer& spriteRenderer) {
	//
}