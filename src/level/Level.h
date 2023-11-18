#ifndef _LEVEL_H
#define _LEVEL_H

#include "../graphics/SpriteRenderer.h"
#include <inttypes.h>
#include <vector>
#include <set>

class Entity;
typedef struct HitBox HitBox;
class Player;

class Level {
public:
	Level();
	~Level();
	void addEntity(Entity*);
	void tick();
	void renderSprites(SpriteRenderer&);
	uint8_t getTile(int, int);
	std::set<Entity*>& getEntities(const HitBox&);
private:
	Player* player;
	uint8_t tiles[300];
	std::vector<Entity*> entityMap[300];
	std::vector<Entity*> entities;
	std::set<Entity*> hitEntities;
	float xTest;
protected:
};

#endif