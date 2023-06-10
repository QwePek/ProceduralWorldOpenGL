#include "World.h"

World::World(int sizeX, int sizeZ)
{
	size = { sizeX, sizeZ };

	for (int x = 0; x < sizeX; x++)
	{
		for (int z = 0; z < sizeZ; z++)
		{
			chunks.push_back(Chunk());
		}
	}

	update();
}

void World::update()
{
	regenerateGeometry();
	regenerateIndicies();
}

void World::regenerateGeometry()
{
	worldGeometry = chunks[0].getGeometry();

	std::cout << "1: " << worldGeometry.size() << std::endl;
}

void World::regenerateIndicies()
{
	worldIndicies = chunks[0].getIndicies();

	std::cout << "2: " << worldIndicies.size() << std::endl;
}