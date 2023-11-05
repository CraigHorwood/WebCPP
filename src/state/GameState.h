#ifndef _GAME_STATE_H
#define _GAME_STATE_H

#include "State.h"

class GameState : State {
public:
	GameState();
	~GameState();
	void tick() override;
	void render() override;
private:
protected:
};

#endif