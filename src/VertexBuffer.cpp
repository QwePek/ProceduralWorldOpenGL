#include "VertexBuffer.h"
#include "GL/glew.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	rendererID = 0;
	GLCall(glGenBuffers(1, &rendererID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
	
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::VertexBuffer(unsigned int size)
{
	rendererID = 0;
	GLCall(glGenBuffers(1, &rendererID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, rendererID));

	GLCall(glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &rendererID));
}

void VertexBuffer::bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
}

void VertexBuffer::unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexBuffer::updateData(const void* data, unsigned int size)	//TODO: ZROBIC TAK ABY TO GBYLO WYWOLYWALNE TYLKO JAK SIE ZROBI TEN BEZ DEFAULT DATA - Z DYNAMIC DRAW
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, rendererID));

	GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
}