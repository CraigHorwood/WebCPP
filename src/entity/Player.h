#ifndef _PLAYER_H
#define _PLAYER_H

#include "Entity.h"
#include "../graphics/SpriteRenderer.h"
#include "../level/Level.h"

typedef struct PlayerInput {
	bool left, right, up, down, jump, shoot, change;
} PlayerInput;

class Player : public Entity {
public:
	Player(Level*, float, float);
	void tick(PlayerInput);
	void render(SpriteRenderer&) override;
private:
protected:
};

#endif