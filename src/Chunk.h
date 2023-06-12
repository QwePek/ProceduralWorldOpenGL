#pragma once
#include "Block.h"
#include <vector>

class Chunk
{
public:
	Chunk();

	void init(glm::uvec2 pos, siv::PerlinNoise* perlin);

	void update();

	const std::vector<float> getGeometry() const { return geometry; };
	const std::vector<uint32_t> getIndicies() const { return indicies; };
	glm::vec3 getChunkPos() const { return { position.x * chunkSize.x, 0, position.y * chunkSize.z }; };

	static uint32_t getChunksMaxBlocks() { return chunkSize.x * chunkSize.y * chunkSize.z; };
	static constexpr glm::uvec3 chunkSize = glm::uvec3(8, 32, 8);

private:
	void generateChunkGeometry();
	void generateIndicies();

	std::vector<float> geometry;
	std::vector<uint32_t> indicies;

	glm::uvec2 position;

	Block blocks[Chunk::chunkSize.x][Chunk::chunkSize.y][Chunk::chunkSize.z];
};

