#include "World.h"

World::World(int sizeX, int sizeZ)
{
	size = { sizeX, sizeZ };
	chunks = new Chunk[size.x * size.y];
	
	int x = 0, z = 0;
	for (int i = 0; i < size.x * size.y; i++)
	{
		chunks[i].init(glm::uvec2(x, z), &perlin);
		worldGeometry.push_back(std::vector<float>());
		worldIndicies.push_back(std::vector<uint32_t>());

		x++;
		if (x == size.x)
		{
			x = 0;
			z++;
		}
	}

	update();
}

World::~World()
{
	delete[] chunks;
}

void World::update()
{
	regenerateGeometry();
	regenerateIndicies();
}

void World::regenerateGeometry()
{
	for (int i = 0; i < worldGeometry.size(); i++)
		worldGeometry[i].clear();

	for (int i = 0; i < size.x * size.y; i++)
	{
		auto vec = chunks[i].getGeometry();
		
		//std::cout << "I: " << i << std::endl;
		//for (int j = 0; j < vec.size(); j++)
		//{
		//	if (j % 5 == 0)
		//		std::cout << std::endl;

		//	std::cout << vec[j] << ", ";
		//}

		worldGeometry[i].insert(worldGeometry[i].begin(), vec.begin(), vec.end());
	}
}

void World::regenerateIndicies()
{
	for (int i = 0; i < worldIndicies.size(); i++)
		worldIndicies[i].clear();

	for (int i = 0; i < size.x * size.y; i++)
	{
		auto vec = chunks[i].getIndicies();
		worldIndicies[i].insert(worldIndicies[i].begin(), vec.begin(), vec.end());
	}
}