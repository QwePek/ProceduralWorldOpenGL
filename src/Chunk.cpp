#include "Chunk.h"
#include <array>
#include <cstdlib>
#include <ctime>

Chunk::Chunk() : blocks{}
{
	for (int z = 0; z < chunkSize.z; z++)
	{
		for (int x = 0; x < chunkSize.x; x++)
		{
			int yHeight = 1;
			blocks[x][yHeight][z].setTexture(glm::vec2(0, 0));
			blocks[x][yHeight][z].position = glm::vec3(x, yHeight, z);
			//float yHeight = rand() % chunkSize.y;
			//for (int y = yHeight; y >= 0; y--)
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
	for (uint32_t z = 0; z < chunkSize.z; z++)
	{
		for (uint32_t y = 0; y < chunkSize.y; y++)
		{
			for (uint32_t x = 0; x < chunkSize.x; x++)
			{
				auto ind = blocks[x][y][z].getIndicies();
				if (ind.empty())
					continue;

				indicies.insert(indicies.end(), ind.begin(), ind.end());
			}
		}
	}
}