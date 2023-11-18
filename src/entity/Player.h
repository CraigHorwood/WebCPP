#ifndef _PLAYER_H
#define _PLAYER_H

#include "Entity.h"
#include "../graphics/SpriteRenderer.h"
#include "../level/Level.h"

class Player : public Entity {
public:
	Player(Level*, float, float);
	void tick(bool, bool, bool, bool, bool, bool, bool);
	void render(SpriteRenderer&) override;
private:
protected:
};

#endif