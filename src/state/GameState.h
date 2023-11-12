#ifndef _GAME_STATE_H
#define _GAME_STATE_H

#include "State.h"
#include "../level/Level.h"
#include "../graphics/SpriteRenderer.h"

class GameState : public State {
public:
	GameState();
	~GameState();
	void tick() override;
	void render() override;
private:
	Level level;
	SpriteRenderer spriteRenderer;
protected:
};

#endif