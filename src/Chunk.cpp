#include "Chunk.h"
#include <array>
#include <cstdlib>
#include <ctime>
#include <unordered_map>
#include <set>

Chunk::Chunk() : blocks{}, position({ 0,0 })
{

}

void Chunk::init(glm::uvec2 pos, siv::PerlinNoise* perlin, float frequency, int octaves)
{
	position = { pos.x, pos.y };

	for (int z = 0; z < chunkSize.z; z++)
	{
		for (int y = 0; y < chunkSize.y; y++)
		{
			for (int x = 0; x < chunkSize.x; x++)
			{
				blocks[x][y][z].setTexture(BLOCK::TEXTURE::GRASS);
				blocks[x][y][z].position = glm::vec3(x, y, z);
			}
		}
	}

	calculateChunkTerrain(perlin, frequency, octaves);

	update();
}

void Chunk::update()
{
	generateChunkGeometry();
	//generateIndicies();
}

void Chunk::calculateChunkTerrain(siv::PerlinNoise* perlin, float frequency, int octaves)
{
	double noise = 0;

	// Terrain calculation
	for (int z = 0; z < chunkSize.z; z++)
	{
		for (int x = 0; x < chunkSize.x; x++)
		{
			noise = perlin->octave2D_01(((x + position.x * Chunk::chunkSize.x) * frequency),
				((z + position.y * Chunk::chunkSize.z) * frequency), octaves);

			uint32_t yHeight = chunkSize.y * noise;

			//Air fill
			for (int h = Chunk::chunkSize.y - 1; h > yHeight; h--)
				blocks[x][h][z].setTexture(BLOCK::TEXTURE::AIR);

			if(noise >= 0.5f)
				blocks[x][yHeight][z].setTexture(BLOCK::TEXTURE::GRASS);
			else if(noise >= 0.49f)
				blocks[x][yHeight][z].setTexture(BLOCK::TEXTURE::GRAVEL);
			else if(noise < 0.49f && noise >= 0.4f)
				blocks[x][yHeight][z].setTexture(BLOCK::TEXTURE::GRASS);
			else if(noise >= 0.35f)
				blocks[x][yHeight][z].setTexture(BLOCK::TEXTURE::SAND);
			else
				blocks[x][yHeight][z].setTexture(BLOCK::TEXTURE::WATER);

			//Dirt fill
			for (int h = yHeight - 1; h > yHeight - 5 && h >= 0; h--)
				blocks[x][h][z].setTexture(BLOCK::TEXTURE::DIRT);

			//Stone fill
			for (int h = yHeight - 5; h >= 0; h--)
				blocks[x][h][z].setTexture(BLOCK::TEXTURE::STONE);
		}
	}
}

void Chunk::generateChunkGeometry()
{
	geometry.clear();
	uint32_t offset = 0;

	for (uint32_t z = 0; z < chunkSize.z; z++)
	{
		for (uint32_t y = 0; y < chunkSize.y; y++)
		{
			for (uint32_t x = 0; x < chunkSize.x; x++)
			{
				//if (blocks[x][y][z].getTextureType() == BLOCK::TEXTURE::AIR)
				//	continue;

				createChunkMesh(x, y, z, offset);

				//auto blockGeometry = blocks[x][y][z].getGeometry();
				//if (blockGeometry.empty())
				//	continue;

				//geometry.insert(geometry.end(), blockGeometry.begin(), blockGeometry.end());
			}
		}
	}
}

void Chunk::createChunkMesh(int x, int y, int z, uint32_t &offset)
{
	if (blocks[x][y][z].getTextureType() == BLOCK::TEXTURE::AIR)
		return;

	std::set<BLOCK::SIDE> scianki;

	if ((z == 0) || (z > 0 && blocks[x][y][z - 1].getTextureType() == BLOCK::TEXTURE::AIR)) //róg
		scianki.insert(BLOCK::SIDE::SIDE1);

	if ((z == chunkSize.z - 1) || (z < chunkSize.z - 1 && blocks[x][y][z + 1].getTextureType() == BLOCK::TEXTURE::AIR)) //róg
		scianki.insert(BLOCK::SIDE::SIDE2);

	if ((x == 0) || (x > 0 && blocks[x - 1][y][z].getTextureType() == BLOCK::TEXTURE::AIR)) //róg
		scianki.insert(BLOCK::SIDE::SIDE3);

	if ((x == chunkSize.x - 1) || (x < chunkSize.x - 1 && blocks[x + 1][y][z].getTextureType() == BLOCK::TEXTURE::AIR)) //róg
		scianki.insert(BLOCK::SIDE::SIDE4);

	if ((y == 0) || (y > 0 && blocks[x][y - 1][z].getTextureType() == BLOCK::TEXTURE::AIR))
		scianki.insert(BLOCK::SIDE::BOTTOM);

	if ((y == chunkSize.y - 1) || (y < chunkSize.y - 1 && blocks[x][y + 1][z].getTextureType() == BLOCK::TEXTURE::AIR))
		scianki.insert(BLOCK::SIDE::TOP);

	for (BLOCK::SIDE sciana : scianki)
	{
		auto blockGeometry = blocks[x][y][z].getGeometry(sciana);
		geometry.insert(geometry.end(), blockGeometry.begin(), blockGeometry.end());

		auto blockIndicies = blocks[x][y][z].getIndicies(sciana, offset);
		indicies.insert(indicies.end(), blockIndicies.begin(), blockIndicies.end());

		offset += 4;
	}
}

//void Chunk::generateIndicies()
//{
//	indicies.clear();
//	uint32_t offset = 0;
//
//	for (uint32_t z = 0; z < chunkSize.z; z++)
//	{
//		for (uint32_t y = 0; y < chunkSize.y; y++)
//		{
//			for (uint32_t x = 0; x < chunkSize.x; x++)
//			{
//				auto ind = blocks[x][y][z].getIndicies(BLOCK::SIDE::ALL, offset);
//				if (ind.empty())
//					continue;
//
//				indicies.insert(indicies.end(), ind.begin(), ind.end());
//				offset += 24;
//			}
//		}
//	}
//}