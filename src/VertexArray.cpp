#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "GL/glew.h"
#include "Renderer.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &rendererID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &rendererID));
}

void VertexArray::bind() const
{
	GLCall(glBindVertexArray(rendererID));
}

void VertexArray::unbind() const
{
	GLCall(glBindVertexArray(0));
}

void VertexArray::addBuffer(const VertexBuffer& buffer, const VertexBufferLayout& layout)
{
	bind();
	buffer.bind();

	const std::vector<VertexBufferElement>& elements = layout.getElements();
	unsigned int offset = 0;

	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const VertexBufferElement& elem = elements[i];

		GLCall(glEnableVertexAttribArray(i));
		glVertexAttribPointer(i, elem.count, elem.type, elem.normalized, 
			layout.getStride(), (const void*)offset);

		offset += elem.count * VertexBufferElement::getSizeOfType(elem.type);
	}
}