#include "stdafx.h"
#include "ShaderProgram.h"
#include <GL/glew.h>
#include <iostream>
#include <string>
#include <fstream>
#include <exception>
#include <assert.h>

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_programID);
}

void ShaderProgram::createProgram()
{
	m_programID = glCreateProgram();
}

void ShaderProgram::loadShader(GLenum shaderType, char* filename)
{
	GLuint shaderID = glCreateShader(shaderType);
	std::ifstream shaderFile(filename);

	std::string shaderCode = "";
	if (shaderFile.is_open())
	{
		while (shaderFile.good())
		{
			std::string line;
			std::getline(shaderFile, line);
			shaderCode += line + '\n';
		}
		shaderFile.close();
	}
	else
	{
		throw new std::exception("Shader not Found");
	}
	const char* cstr_shaderCode = shaderCode.c_str();
	const GLint length = shaderCode.length();
	glShaderSource(shaderID, 1,&cstr_shaderCode,&length);

	glCompileShader(shaderID);

	
	GLint success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar InfoLog[1024];
		glGetShaderInfoLog(shaderID, sizeof(InfoLog), 0, InfoLog);
		std::cout << "Error compiling shader type"<<shaderType<<": '"<<InfoLog<<"'"<<std::endl;
	}
	glAttachShader(m_programID, shaderID);

	glDeleteShader(shaderID);
}

void ShaderProgram::finalize()
{
	glLinkProgram(m_programID);

	GLint success;
	glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLchar InfoLog[1024];
		glGetProgramInfoLog(m_programID, sizeof(InfoLog), 0, InfoLog);
		std::cout << "Error linking program: '"<<InfoLog<<"'"<< std::endl;
	}
	glValidateProgram(m_programID);

	//get the locations of all of the input variables
	m_posLocation = glGetAttribLocation(m_programID, "Position");
	m_uvLocation = glGetAttribLocation(m_programID, "TexCoord");
	m_colLocation = glGetAttribLocation(m_programID, "Color");
	assert(m_colLocation != 0xFFFFFFFF);
	assert(m_posLocation != 0xFFFFFFFF);
	assert(m_uvLocation != 0xFFFFFFFF);
	glVertexAttribPointer(m_posLocation, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), 0);
	glVertexAttribPointer(m_colLocation, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (GLvoid*)(3*sizeof(float)));
	glVertexAttribPointer(m_uvLocation, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (GLvoid*)(6*sizeof(float)));

	m_samplerLocation = glGetUniformLocation(m_programID, "gSampler");
	assert(m_samplerLocation != 0xFFFFFFFF);
}

void ShaderProgram::useProgram()
{
	glUseProgram(m_programID);
}

void ShaderProgram::enableVertexAttribArray()
{
	glEnableVertexAttribArray(m_posLocation);
	glEnableVertexAttribArray(m_uvLocation);
	glEnableVertexAttribArray(m_colLocation);
}

void ShaderProgram::disableVertexAttribArray()
{
	glDisableVertexAttribArray(m_posLocation);
	glDisableVertexAttribArray(m_uvLocation);
	glDisableVertexAttribArray(m_colLocation);
}