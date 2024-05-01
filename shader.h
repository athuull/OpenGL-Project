#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
	unsigned int ID; // Program ID

	// constructor reads and builds the shader

	Shader(const char* vertexPath, const char* fragmentPath) {
		std::string vertexCode;  //  to store the vertex shader code
		std::string fragmentCode; // to store the fragment shader code 
		std::ifstream vShaderFile; // ifstream object to open vertex shader file
		std::ifstream fShaderFIle; // ifstream object to open fragment shader file
		// ensure ifstream objects can throw exceptions
			vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			fShaderFIle.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			//open File
			vShaderFile.open(vertexPath);
			fShaderFIle.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;  
			vShaderStream << vShaderFile.rdbuf();   // stores the contents of the file into the stream object 
			fShaderStream << fShaderFIle.rdbuf(); 
			vShaderFile.close();
			fShaderFIle.close();

			// convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e) {
			std::cout << "Failure" << std::endl;
		}
		const char* vShaderCode = vertexCode.c_str();  // returns a pointer to the start of the vertex shader code
		const char* fshaderCode = fragmentCode.c_str(); // returns a pointer to the start of the fragment shader code
		// Compiling Shaders
		unsigned int vertex, fragment;
		int success;
		char infoLog[512];
		vertex = glCreateShader(GL_VERTEX_SHADER);
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		//Vertex Shader
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		if (!success) {
			std::cout << infoLog<<std::endl;
		}

		 // Fragment Shader
		glShaderSource(fragment, 1, &fshaderCode, NULL);
		glCompileShader(fragment);
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		if (!success) {
			std::cout << infoLog << std::endl;
		}


		// Shader Program
		 ID = glCreateProgram(); 
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);

		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		if (!success) {
			std::cout << infoLog << std::endl;
		}

	}
	
	// activate the shader
	void use() {
		glUseProgram(ID);
	}

    // TODO : 
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value)const;
};







#endif 