#pragma once

class VertexBuffer
{
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void bind() const;
	void unbind() const;

private:
	uint32_t rendererID = 0;
};