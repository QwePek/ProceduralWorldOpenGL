#pragma once
#include "Chunk.h"

class World
{
public:
	World(int sizeX, int sizeZ);

	void update();

	std::vector<float> getGeometry() const { return worldGeometry; };
	std::vector<uint32_t> getIndicies() const { return worldIndicies; };

	uint32_t getBlocksNeeded() { return size.x * size.y * Chunk::getChunksMaxBlocks(); };

private:
	std::vector<Chunk> chunks;

	void regenerateGeometry();
	void regenerateIndicies();

	std::vector<float> worldGeometry;
	std::vector<uint32_t> worldIndicies;

	glm::uvec2 size = glm::uvec2(1.0f, 1.0f);
};

