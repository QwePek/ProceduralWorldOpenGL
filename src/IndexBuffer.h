#pragma once
class IndexBuffer
{
public:
	IndexBuffer(const unsigned int* data, const unsigned int count);
	~IndexBuffer();

	void bind() const;
	void unbind() const;

	inline unsigned int getCount() const { return indiciesCount; };

private:
	unsigned int rendererID;
	unsigned int indiciesCount;
};

