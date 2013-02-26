#pragma once
#include <GL/glew.h>
class ShaderProgram
{
public:
	void createProgram();
	void loadShader(GLenum shaderType, char* filename);
	void finalize();

	void useProgram();

	void enableVertexAttribArray();

	void disableVertexAttribArray();

	GLuint getProgramID()
	{
		return m_programID;
	}
	GLuint getPosLocation()
	{
		return m_posLocation;
	}
	GLuint getColLocation()
	{
		return m_colLocation;
	}
	GLuint getMVPLocation()
	{
		return m_MVPLocation;
	}
	GLuint getUVLocation()
	{
		return m_uvLocation;
	}
	GLuint getSamplerLocation()
	{
		return m_samplerLocation;
	}

protected:
	GLuint m_programID;
	GLuint m_posLocation;
	GLuint m_uvLocation;
	GLuint m_colLocation;
	GLuint m_MVPLocation;
	GLuint m_samplerLocation;
	GLuint m_VAO;
};

