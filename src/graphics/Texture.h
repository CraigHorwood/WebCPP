#ifndef _TEXTURE_H
#define _TEXTURE_H
#include "GLFW/glfw3.h"

class Texture {
public:
	Texture(const char*);
	~Texture();
	unsigned int width, height;
private:
	GLuint texture;
protected:
};

#endif