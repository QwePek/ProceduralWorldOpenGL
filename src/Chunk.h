#pragma once
#include "Block.h"
#include <vector>

class Chunk
{
public:
	Chunk();

	void update();

	const std::vector<float> getGeometry() const { return geometry; };
	const std::vector<uint32_t> getIndicies() const { return indicies; };

	static uint32_t getChunksMaxBlocks() { return chunkSize.x * chunkSize.y * chunkSize.z; };
	static constexpr glm::uvec3 chunkSize = glm::uvec3(1, 1, 1);

private:
	void generateChunkGeometry();
	void generateIndicies();

	std::vector<float> geometry;
	std::vector<uint32_t> indicies;

	Block blocks[1][1][1];


	//Block blocks[16][32][16];
};

