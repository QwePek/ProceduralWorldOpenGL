#include "Chunk.h"
#include <array>
#include <cstdlib>
#include <ctime>

Chunk::Chunk() : blocks{}, position({ 0,0 })
{

}

void Chunk::init(glm::uvec2 pos, siv::PerlinNoise* perlin)
{
	position = { pos.x, pos.y };

	for (int z = 0; z < chunkSize.z; z++)
	{
		for (int y = 0; y < chunkSize.y; y++)
		{
			for (int x = 0; x < chunkSize.x; x++)
			{
				blocks[x][y][z].setTexture(glm::vec2(0, 0));
				blocks[x][y][z].position = glm::vec3(x, y, z);

				const double noise = perlin->octave2D_01(((x + position.x * chunkSize.x) * 0.01), 
					((z + position.y * chunkSize.z) * 0.01), 8);

				uint32_t yHeight = chunkSize.y * noise;

				for (uint32_t h = chunkSize.y - 1; h > yHeight; h--)
					blocks[x][h][z].setTexture({ 2,0 });
			}
		}
	}

	update();
}

void Chunk::update()
{
	generateChunkGeometry();
	generateIndicies();
}

void Chunk::generateChunkGeometry()
{
	geometry.clear();
	for (uint32_t z = 0; z < chunkSize.z; z++)
	{
		for (uint32_t y = 0; y < chunkSize.y; y++)
		{
			for (uint32_t x = 0; x < chunkSize.x; x++)
			{
				auto blockGeometry = blocks[x][y][z].getGeometry();
				if (blockGeometry.empty())
					continue;

				geometry.insert(geometry.end(), blockGeometry.begin(), blockGeometry.end());
			}
		}
	}
}

void Chunk::generateIndicies()
{
	indicies.clear();
	uint32_t offset = 0;

	for (uint32_t z = 0; z < chunkSize.z; z++)
	{
		for (uint32_t y = 0; y < chunkSize.y; y++)
		{
			for (uint32_t x = 0; x < chunkSize.x; x++)
			{
				auto ind = blocks[x][y][z].getIndicies(BLOCK::SIDE::ALL, offset);
				if (ind.empty())
					continue;

				indicies.insert(indicies.end(), ind.begin(), ind.end());
				offset += 24;
			}
		}
	}
}