#ifndef _ASSETS_H
#define _ASSETS_H

#include "graphics/Shader.h"
#include "graphics/Texture.h"

namespace Assets {
	extern Shader* spriteShader;
	extern Texture* tilesTexture;

	void loadAll();
	void deleteAll();
}

#endif