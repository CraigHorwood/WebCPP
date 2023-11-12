#ifndef _SHADER_H
#define _SHADER_H
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <map>
#include <string>

#define ATTR_POS 0
#define ATTR_UV 1
#define ATTR_COL 2

class Shader {
public:
	Shader() {}
	Shader(const char*);
	~Shader();
	void bind();
	void getUniformLocation(const std::string);
	void setUniformMatrix4f(const std::string, float*);
private:
	GLuint compileShader(const char*, GLenum);
	GLint program;
	std::map<const std::string, const GLint> uniformLocations;
protected:
};

#endif