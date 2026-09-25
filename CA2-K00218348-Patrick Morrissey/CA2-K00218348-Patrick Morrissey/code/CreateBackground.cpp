#include <SFML/Graphics.hpp>
#include "ZombieArena.h"

#include <iostream>

using namespace std;

int createBackground(VertexArray& rVA, IntRect arena, String**& m_GridTileType, int& m_WorldWidth, int& m_WorldHeight)
{
	// Anything we do to rVA we are actually doing to background (in the main function)

	// How big is each tile/texture
	const int TILE_SIZE = 50;
	const int TILE_TYPES = 3;
	const int VERTS_IN_QUAD = 4;

	int worldWidth = arena.width / TILE_SIZE;
	int worldHeight = arena.height / TILE_SIZE;

	// updates the world width and height (grid tile) member variables in game manager
	m_WorldWidth = worldWidth;
	m_WorldHeight = worldHeight;

	// What type of primitive are we using?
	rVA.setPrimitiveType(Quads);

	// Set the size of the vertex array
	rVA.resize(worldWidth * worldHeight * VERTS_IN_QUAD);

	// Start at the beginning of the vertex array
	int currentVertex = 0;

	// Prepare the 2d array to hold the type values of the tiles
	m_GridTileType = new String* [worldWidth];
	for (int i = 0; i < worldWidth; ++i)
	{
		// Add a new array into each array element
		m_GridTileType[i] = new String[worldHeight];
	}

	// sets default values
	for (int x = 0; x < worldWidth; x++)
	{
		for (int y = 0; y < worldHeight; y++)
		{
			m_GridTileType[x][y] = "other";
		}
	}

	// sets the probability of walls spawning - between 1 and 30%
	int percentageWallCoverage = (rand() % 30) + 1;
	//percentageWallCoverage = 25;
	// Cellular automata random tile generation - based on algorithms for games game dev lab code
	// Starts at 1 x and 1 y because the world border will later be set as a wall
	for (int x = 1; x < worldWidth; x++) 
	{
		for (int y = 1; y < worldHeight; y++) 
		{
			// generates a random number 1 and 100. Sets the tile to wall if the value is less than or equal to 20
			if ((rand() % 100) + 1 <= percentageWallCoverage)
			{
				m_GridTileType[x][y] = "wall";
			}
		}
	}

	//smooth(worldWidth, worldHeight, m_GridTileType,8); // smoothing seemed to just increase the chance of generating inaccessible areas so I don't use it

	for (int w = 0; w < worldWidth; w++)
	{
		for (int h = 0; h < worldHeight; h++)
		{
			// Position each vertex in the current quad
			rVA[currentVertex + 0].position = Vector2f(w * TILE_SIZE, h * TILE_SIZE);
			rVA[currentVertex + 1].position = Vector2f((w * TILE_SIZE) + TILE_SIZE, h * TILE_SIZE);
			rVA[currentVertex + 2].position = Vector2f((w * TILE_SIZE) + TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE);
			rVA[currentVertex + 3].position = Vector2f((w * TILE_SIZE), (h * TILE_SIZE) + TILE_SIZE);

			// Define the position in the Texture to draw for current quad
			// Either mud, stone, grass or wall
			if (h == 0 || h == worldHeight - 1 || w == 0 || w == worldWidth - 1)
			{
				m_GridTileType[w][h] = "wall";
			}
			/*
			// set the tile beside the border wall to not be a wall
			if (h == 1 || h == worldHeight - 2 || w == 1 || w == worldWidth - 2)
			{
				m_GridTileType[w][h] = "floor";
			}
			*/
			if(m_GridTileType[w][h] == "wall")
			{
				// Use the wall texture
				rVA[currentVertex + 0].texCoords = Vector2f(0, 0 + TILE_TYPES * TILE_SIZE);
				rVA[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, 0 + TILE_TYPES * TILE_SIZE);
				rVA[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + TILE_TYPES * TILE_SIZE);
				rVA[currentVertex + 3].texCoords = Vector2f(0, TILE_SIZE + TILE_TYPES * TILE_SIZE);

				//gridTileType[w][h] = "wall";
				
			}
			else
			{
				// Use a random floor texture
				//srand((int)time(0) + h * w - h);
				int mOrG = (rand() % TILE_TYPES);
				int verticalOffset = mOrG * TILE_SIZE;

				rVA[currentVertex + 0].texCoords = Vector2f(0, 0 + verticalOffset);
				rVA[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, 0 + verticalOffset);
				rVA[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
				rVA[currentVertex + 3].texCoords = Vector2f(0, TILE_SIZE + verticalOffset);

				m_GridTileType[w][h] = "other";

			}

			// Position ready for the next for vertices
			currentVertex = currentVertex + VERTS_IN_QUAD;
		}
	}
	
	return TILE_SIZE;
}

// counts the number of walls surrounding the tile position in a 3x3 area around it - based on algorithms for games game dev lab code
int countWalls(int width, int height, String**& m_GridTileType) // x y
{
	int count = 0;
	for (int dx = -1; dx <= 1; dx++) 
	{
		for (int dy = -1; dy <= 1; dy++) 
		{
			int nx = width + dx;
			int ny = height + dy;
			if (nx >= 0 && nx < width && ny >= 0 && ny < height && m_GridTileType[nx][ny] == "wall") 
			{
				count++;
			}
		}
	}
	return count;
}

// smoothes edges - based on algorithms for games game dev lab code
void smooth(int width, int height, String**& m_GridTileType, int numRepeats)
{
	int worldWidth = width;
	int worldHeight = height;
	for (int i = 0; i < numRepeats; i++)
	{
		for (int x = 1; x < worldWidth-1; x++) {
			for (int y = 1; y < worldHeight-1; y++) {
				// generates a random number 0 and 4. Sets the tile to be a wall if the value is 0
				int numWalls = countWalls(width, height, m_GridTileType);
				if (numWalls > 4)
				{
					m_GridTileType[x][y] = "wall";
				}
			}
		}
	}
	
}
