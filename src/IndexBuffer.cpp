#include "IndexBuffer.h"
#include <GL/glew.h>
#include "Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
{
	ASSERT(sizeof(unsigned int) == sizeof(GLuint)); //To poniewaz na roznych kompach sa rozne rozmiary

	GLCall(glGenBuffers(1, &rendererID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));

	indiciesCount = count;
}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &rendererID));
}

void IndexBuffer::bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID));
}

void IndexBuffer::unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}