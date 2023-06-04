#include "Renderer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGl error] (" << error << "): " << function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}

void Renderer::clear()
{
	glClearColor(0.494f, 0.654f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::draw(const Shader& shader) const
{
	shader.bind();

	//GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}