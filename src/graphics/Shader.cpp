#include "Shader.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>

using namespace std;

Shader::Shader(const char* path) {
	// TODO: File I/O
	GLuint vertexShader = compileShader("vertex shader code", GL_VERTEX_SHADER);
	GLuint fragmentShader = compileShader("fragment shader code", GL_FRAGMENT_SHADER);
	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glBindAttribLocation(program, ATTR_POS, "position");
	glBindAttribLocation(program, ATTR_UV, "texCoords");
	glBindAttribLocation(program, ATTR_COL, "colour");
	glLinkProgram(program);
	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
	if (isLinked != GL_TRUE) {
		GLint len = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
		if (len) {
			char* log = new char[len];
			GLint result;
			glGetProgramInfoLog(program, len, &result, log);
			cout << log << endl;
			delete[] log;
			glDeleteProgram(program);
			program = 0;
		}
	}
	if (vertexShader) {
		glDeleteShader(vertexShader);
	}
	if (fragmentShader) {
		glDeleteShader(fragmentShader);
	}
}

Shader::~Shader() {
	if (program) {
		glDeleteProgram(program);
	}
}

GLuint Shader::compileShader(const char* source, GLenum type) {
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	GLint isCompiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled != GL_TRUE) {
		GLint len = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
		if (len) {
			char* log = new char[len];
			GLint result;
			glGetShaderInfoLog(shader, len, &result, log);
			cout << log << endl;
			delete[] log;
			glDeleteShader(shader);
			return 0;
		}
	}
	return shader;
}

void Shader::bind() {
	glUseProgram(program);
}