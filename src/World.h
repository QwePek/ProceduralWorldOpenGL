#pragma once
#include "Chunk.h"

class World
{
public:
	World(int sizeX, int sizeZ);
	~World();

	void update();

	const glm::vec3 getChunkPos(uint32_t n) const { return chunks[n].getChunkPos(); };

	std::vector<float> getGeometry(uint32_t n) const { return worldGeometry[n]; };
	std::vector<uint32_t> getIndicies(uint32_t n) const { return worldIndicies[n]; };

	uint32_t getBlocksNeeded() { return getWorldSize() * Chunk::getChunksMaxBlocks(); };
	uint32_t getWorldSize() { return size.x * size.y; };

private:
	Chunk* chunks;

	siv::PerlinNoise::seed_type seed = 123456u;
	siv::PerlinNoise perlin{ seed };

	void regenerateGeometry();
	void regenerateIndicies();

	std::vector<std::vector<float>> worldGeometry;
	std::vector<std::vector<uint32_t>> worldIndicies;

	glm::uvec2 size;
};

