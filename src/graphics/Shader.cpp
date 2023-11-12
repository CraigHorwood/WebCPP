#include "Shader.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

Shader::Shader(const char* path) {
	string vertexShaderCode = "";
	string fragmentShaderCode = "";
	string* codeReference = nullptr;

	ifstream shaderFile(path);
	if (shaderFile.is_open()) {
		string line;
		while (getline(shaderFile, line)) {
			if (!line.compare("<vertex>")) {
				codeReference = &vertexShaderCode;
				continue;
			} else if (!line.compare("<fragment>")) {
				codeReference = &fragmentShaderCode;
				continue;
			} else if (!line.compare("</vertex>") || !line.compare("</fragment>")) {
				codeReference = nullptr;
			}
			if (codeReference != nullptr) {
				codeReference->append(line);
			}
		}
		shaderFile.close();
	}

	GLuint vertexShader = compileShader(vertexShaderCode.c_str(), GL_VERTEX_SHADER);
	GLuint fragmentShader = compileShader(fragmentShaderCode.c_str(), GL_FRAGMENT_SHADER);
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

void Shader::getUniformLocation(const string name) {
	const GLint uniformLocation = glGetUniformLocation(program, name.c_str());
	uniformLocations.insert(pair<const string, const GLint>(name, uniformLocation));
}

void Shader::setUniformMatrix4f(const string name, float* matrix) {
	glUniformMatrix4fv(uniformLocations[name], 1, GL_FALSE, matrix);
} 