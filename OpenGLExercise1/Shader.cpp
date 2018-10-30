#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Shader::Shader(const char* vertexPath, const char* fragmentPath){
	std::ifstream vertextFile;
	std::ifstream fragmentFile;

	vertextFile.open(vertexPath);
	fragmentFile.open(fragmentPath);

	stringstream vertexSStream, fragmentSStream;

	vertextFile.exceptions(ifstream::failbit | ifstream::badbit);
	fragmentFile.exceptions(ifstream::failbit | ifstream::badbit);

	try{
		if (!vertextFile.is_open() || !fragmentFile.is_open()) {
			throw exception("File Open Error");
		}
		vertexSStream << vertextFile.rdbuf();
		fragmentSStream << fragmentFile.rdbuf();

		vertexString = vertexSStream.str();
		fragmentString = fragmentSStream.str();

		vertexSource = vertexString.c_str();
		fragmentSource = fragmentString.c_str();

		unsigned int vertex, fragment;
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexSource, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentSource, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	catch (const std::exception& ex){
		printf(ex.what());
	}
}

Shader::~Shader(){
}

void Shader::use() {
	glUseProgram(ID);
}

void Shader::checkCompileErrors(unsigned int ID, std::string type) {
	int success;
	char infoLog[512];

	if (type != "PROGRAM") {
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(ID, 512, NULL, infoLog);
			cout << "Shader Compile Error: " << infoLog << endl;
		}
	}
	else {
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			cout << "Program Linking Error: " << infoLog << endl;
		}
	}
}