#include "stdafx.h"
#include "Renderer.h"
#include <iostream>

Renderer::Renderer(void)
{
}



void Renderer::VInit()
{
	shaderProgram.createProgram();
	shaderProgram.loadShader(GL_VERTEX_SHADER, "VertexShader.glsl");
	shaderProgram.loadShader(GL_FRAGMENT_SHADER, "FragmentShader.glsl");
	shaderProgram.finalize();
	color = glm::vec4(0.5f, 0.5f, 1.0f, 1.0f);
}

void Renderer::VUpdate(int delta)
{
	//TODO: only change this if the transform has actually changed instead of every frame
	if (m_owner)
	{
		glm::mat4 translate, rotatex, rotatey, rotatez, scale;
		glm::translate(translate, m_owner->getPosition());
		glm::rotate(rotatex, m_owner->getRotation().x, glm::vec3(1.0f, 0.0f, 0.0f));
		glm::rotate(rotatey, m_owner->getRotation().y, glm::vec3(0.f, 1.f, 0.f));
		glm::rotate(rotatez, m_owner->getRotation().z, glm::vec3(0.f, 0.f, 1.f));
		glm::scale(scale, m_owner->getScale());

		worldTransform = translate * rotatex * rotatey * rotatez * scale;
	}
}

void Renderer::VDraw()
{
	shaderProgram.useProgram();
	glUniform4f(shaderProgram.getColLocation(), color.r, color.g, color.b, color.a);
	shaderProgram.enableVertexAttribArray();
	
	glDrawArrays(GL_TRIANGLES, 0, 4);
	shaderProgram.disableVertexAttribArray();
}

glm::vec3 Renderer::vertices[] = {
	glm::vec3(1.0f, 1.0f, 0.0f),
	glm::vec3(-1.0f, 1.0f, 0.0f),
	glm::vec3(-1.f, -1.f, 0.f),
	glm::vec3(1.f, -1.f, 0.f) 
};