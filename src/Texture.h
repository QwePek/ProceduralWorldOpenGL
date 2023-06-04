#pragma once
#include <iostream>

class Texture
{
public:
	Texture(const std::string& path);
	~Texture();

	void bind(unsigned int slot = 0) const;
	void unbind() const;

	inline int getWidth() const { return width; };
	inline int getHeight() const { return height; };

private:
	unsigned int texID;
	std::string texturePath;

	unsigned char* textureBuffer;
	int width, height, channelsNr;
};