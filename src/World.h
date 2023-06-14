#pragma once
#include "Chunk.h"

class World
{
public:
	World(int sizeX, int sizeZ);
	~World();

	void update();
	void updateAll();

	void resizeWorld(glm::vec2 val) { size = val; };
	void setWorldSeed(uint32_t val) { seed = val; };
	void setNumberOfOctaves(uint32_t val) { octaves = val; };
	void setFrequency(float val) { frequency = val; };

	const glm::vec3 getChunkPos(uint32_t n) const { return chunks[n].getChunkPos(); };

	std::vector<float> getGeometry(uint32_t n) const { return worldGeometry[n]; };
	std::vector<uint32_t> getIndicies(uint32_t n) const { return worldIndicies[n]; };

	uint32_t getBlocksNeeded() { return getWorldSize() * Chunk::getChunksMaxBlocks(); };
	uint32_t getWorldSize() { return size.x * size.y; };
	glm::vec2 getWorldSizeVec() { return size; };

private:
	void init();

	Chunk* chunks;

	//World generation
	siv::PerlinNoise::seed_type seed = 123456u;
	siv::PerlinNoise perlin{ seed };

	int octaves = 8;
	float frequency = 0.01f;

	void regenerateGeometry();
	void regenerateIndicies();

	std::vector<std::vector<float>> worldGeometry;
	std::vector<std::vector<uint32_t>> worldIndicies;

	glm::vec2 size;
};

