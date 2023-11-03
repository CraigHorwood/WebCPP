#ifndef _SHADER_H
#define _SHADER_H
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#define ATTR_POS 0
#define ATTR_UV 1
#define ATTR_COL 2

class Shader {
public:
	Shader(const char*);
	~Shader();
	void bind();
private:
	GLuint compileShader(const char*, GLenum);
	GLint program;
protected:
};

#endif