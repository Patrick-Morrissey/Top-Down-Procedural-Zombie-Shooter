#include "ZombieArena.h"
#include "Zombie.h"
#include "Bloater.h"
#include "Chaser.h"
#include "Crawler.h"
#include "InfectedCrow.h"
#include <vector>


using namespace std;

vector<Zombie*> createHorde(int numZombies, int tileSize, IntRect arena, String**& m_GridTileType, int& m_WorldHeight)
{
	vector<Zombie*> vpZombies;
	Vector2f spawnPosition;

	int maxY = arena.height - 50;
	int minY = arena.top + 50;
	int maxX = arena.width - 50;
	int minX = arena.left + 50;
	int side;

	for (int i = 0; i < numZombies; i++)
	{

		// Which side should the zombie spawn
		//srand((int)time(0) * i * 2);

		float x, y;
		bool notInWallOrSurroundedByWalls = false;
		int j = 0;
		// keeps generating x and y coordinates until a position is found that is not in a wall
		// Stops zombies from spawning in walls
		while (!notInWallOrSurroundedByWalls)
		{
			side = (rand() % 4);

			switch (side)
			{
			case 0:
				// left
				x = minX;
				y = (rand() % maxY) + minY;
				break;

			case 1:
				// right
				x = maxX - 1; // stops the x position being in a border wall
				y = (rand() % maxY) + minY;
				break;

			case 2:
				// top
				x = (rand() % maxX) + minX;
				y = minY;
				break;

			case 3:
				// bottom
				x = (rand() % maxX) + minX;
				y = maxY - 1; // stops the y position being in a border wall
				break;
			}
			
			spawnPosition.x = x;
			spawnPosition.y = y;

			// Checks if the generated x and y coordinates are not in a wall and if spawn has less than or equal to 4 walls around it including the 3 border walls
			if (getGridTileType(spawnPosition, m_GridTileType, m_WorldHeight) != "wall" && countWallsAroundTile(spawnPosition, m_GridTileType, m_WorldHeight) <= 4) // && countWallsAroundTile(spawnPosition, m_GridTileType) <= 4
			{
				notInWallOrSurroundedByWalls = true;
			}
			else
			{
				notInWallOrSurroundedByWalls = false;
			}
		}
		

		// Bloater, crawler, runner, or crow
		int type = (rand() % 4);
		//type = 3;
		Zombie* zombie = nullptr;

		// Spawn the new zombie into the array
		switch (type)
		{
			// adds a bloater
			case 0:
				zombie = new Bloater();
				break;
			// adds a chaser
			case 1:
				zombie = new Chaser();
				break;
			// adds a crawler
			case 2:
				zombie = new Crawler();
				break;
				// adds a crawler
			case 3:
				zombie = new InfectedCrow();
				break;
		}
		zombie->spawn(x, y, i, tileSize, m_GridTileType, m_WorldHeight);
		vpZombies.push_back(zombie);
		

	}
	return vpZombies;
}