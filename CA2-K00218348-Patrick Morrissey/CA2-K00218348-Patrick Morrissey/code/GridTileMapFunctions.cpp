#include "ZombieArena.h"
#include <vector>

using namespace std;

// Returns the grid position that the provided x and y coordinates are found in
Vector2i getGridTileMapCoords(Vector2f position)
{
	Vector2i gridTileMapPosition;
	// Integers round down to the nearest whole number
	int tileX = int(position.x / 50);
	int tileY = int(position.y / 50);

	gridTileMapPosition.x = tileX;
	gridTileMapPosition.y = tileY;

	return gridTileMapPosition;
}

// checks if the position is out of bounds in the grid tile map
bool isPositionOutofGridBounds(Vector2f position, int& m_WorldWidth)
{
	// calls the getGridTileMapPosition() method to convert the x and y coordinates into a grid tile reference
	Vector2i gridPosition = getGridTileMapCoords(position);
	bool gridPositionOutOfBounds = false;

	// checks if the grid position provided is outside the bounds of the world.
	// the world is square so worldWidth is used for both x and y
	if (gridPosition.x < 0 || gridPosition.x >= m_WorldWidth || gridPosition.y < 0 || gridPosition.y >= m_WorldWidth)
	{
		gridPositionOutOfBounds = true;
	}

	return gridPositionOutOfBounds;
}

// Returns the grid type type located at the provided grid location
String getGridTileType(Vector2f position, String**& m_GridTileType, int& m_WorldWidth)
{
	// calls the getGridTileMapPosition() method to convert the x and y coordinates into a grid tile reference
	Vector2i gridPosition = getGridTileMapCoords(position);
	String gridTileType;

	// checks if the grid position provided is outside the bounds of the world. If it is, the type is called "wall"
	// the world is square so worldWidth is used for both x and y
	if (isPositionOutofGridBounds(position, m_WorldWidth))
	{
		gridTileType = "wall";
	}
	else
	{
		gridTileType = m_GridTileType[gridPosition.x][gridPosition.y];
	}

	return gridTileType;
}

// Returns a vector of strings containing the surrounding tile types in 8 directions
// must use the previous position or out of bounds runtime errors will happen
vector<String> getSurroundingGridTileTypesIn8Directions(Vector2f previousPosition, String**& m_GridTileType, int& m_WorldWith)
{
	// the grid cooridnates of the current tile
	Vector2i currentTile = getGridTileMapCoords(previousPosition);
	vector<String> surroundingTileTypes;

	// set all default values to be a wall
	for (int i = 0; i < 8; i++)
	{
		surroundingTileTypes.push_back("wall");
	}

	// top left
	if (currentTile.y == 0 && currentTile.x == 0)
	{
		surroundingTileTypes[3] = m_GridTileType[currentTile.x + 1][currentTile.y + 1]; // se = 3
	}
	// top right - width is the same as height
	else if (currentTile.y == 0 && currentTile.x == m_WorldWith - 1)
	{
		surroundingTileTypes[5] = m_GridTileType[currentTile.x - 1][currentTile.y + 1]; // sw = 5
	}
	// bottom left
	else if (currentTile.y == m_WorldWith - 1 && currentTile.x == 0)
	{
		surroundingTileTypes[1] = m_GridTileType[currentTile.x + 1][currentTile.y - 1]; // ne = 1
	}
	// bottom right
	else if (currentTile.y == m_WorldWith - 1 && currentTile.x == m_WorldWith - 1)
	{
		surroundingTileTypes[7] = m_GridTileType[currentTile.x - 1][currentTile.y - 1]; // nw = 7
	}
	else
	{
		// n = 0, ne = 1, e = 2, se = 3, s = 4, sw = 5, w = 6, nw = 7
		surroundingTileTypes[0] = m_GridTileType[currentTile.x][currentTile.y - 1]; // n = 0
		surroundingTileTypes[1] = m_GridTileType[currentTile.x + 1][currentTile.y - 1]; // ne = 1
		surroundingTileTypes[2] = m_GridTileType[currentTile.x + 1][currentTile.y]; // e = 2
		surroundingTileTypes[3] = m_GridTileType[currentTile.x + 1][currentTile.y + 1]; // se = 3
		surroundingTileTypes[4] = m_GridTileType[currentTile.x][currentTile.y + 1]; // s = 4
		surroundingTileTypes[5] = m_GridTileType[currentTile.x - 1][currentTile.y + 1]; // sw = 5
		surroundingTileTypes[6] = m_GridTileType[currentTile.x - 1][currentTile.y]; // w = 6
		surroundingTileTypes[7] = m_GridTileType[currentTile.x - 1][currentTile.y - 1]; // nw = 7
	}

	return surroundingTileTypes;
}




bool getMovementDirDiagonalAdjacentTileTypesWalls(Vector2f position, Vector2f previousPosition, String**& m_GridTileType, int& m_WorldWidth)
{
	Vector2f previousPos = previousPosition;
	Vector2f currentPos = position;

	// n = 0, ne = 1, e = 2, se = 3, s = 4, sw = 5, w = 6, nw = 7
	vector<String> surroundingTileTypes = getSurroundingGridTileTypesIn8Directions(previousPos, m_GridTileType, m_WorldWidth);
	bool bothAdjacentTilesAreWalls = false;

	// if zombie is travelling northeast, and the tile to the north and east are walls
	if (previousPos.x < currentPos.x && previousPos.y > currentPos.y)
	{
		if (surroundingTileTypes[0] == "wall" && surroundingTileTypes[2] == "wall")
		{
			bothAdjacentTilesAreWalls = true;
		}
		else
		{
			bothAdjacentTilesAreWalls = false;
		}
	}

	// if zombie is travelling southeast, and the tile to the south and east are walls
	if (previousPos.x < currentPos.x && previousPos.y < currentPos.y)
	{
		if (surroundingTileTypes[4] == "wall" && surroundingTileTypes[2] == "wall")
		{
			bothAdjacentTilesAreWalls = true;
		}
		else
		{
			bothAdjacentTilesAreWalls = false;
		}
	}

	// if zombie is travelling northwest, and the tile to the north and west are walls
	if (previousPos.x > currentPos.x && previousPos.y > currentPos.y)
	{
		if (surroundingTileTypes[0] == "wall" && surroundingTileTypes[6] == "wall")
		{
			bothAdjacentTilesAreWalls = true;
		}
		else
		{
			bothAdjacentTilesAreWalls = false;
		}
	}

	// if zombie is travelling southwest, and the tile to the south and west are walls
	if (previousPos.x > currentPos.x && previousPos.y < currentPos.y)
	{
		if (surroundingTileTypes[4] == "wall" && surroundingTileTypes[6] == "wall")
		{
			bothAdjacentTilesAreWalls = true;
		}
		else
		{
			bothAdjacentTilesAreWalls = false;
		}
	}

	return bothAdjacentTilesAreWalls;
}

bool isEnteringNewTile(Vector2f position, Vector2f previousPosition)
{
	bool isEnteringNewTile = false;
	Vector2f currentPos = position;
	Vector2f previousPos = previousPosition;
	// checks if the gameactor is entering a new grid tile by checking if the current grid tile coordinates are the same the previous coordinates
	if ((int(currentPos.x / 50)) == (int(previousPos.x / 50)) && (int(currentPos.y / 50) == int(previousPos.y / 50)))
	{
		isEnteringNewTile = false;
	}
	else // entering a new tile
	{
		isEnteringNewTile = true;
	}
	return isEnteringNewTile;
}

// counts the number of walls around a gameactor or pickup
int countWallsAroundTile(Vector2f position, String**& m_GridTileType, int& m_WorldWidth)
{
	vector<String> surroundingTileTypes = getSurroundingGridTileTypesIn8Directions(position, m_GridTileType, m_WorldWidth);

	int count = 0;

	for (int i = 0; i < surroundingTileTypes.size(); i++)
	{
		if (surroundingTileTypes[i] == "wall")
		{
			count++;
		}
	}
	return count;
}

//////////////////   The rest is commeneted out


/***
Made while trying to see if I could find a way to path find through tiles from the current tile to the player tile but I couldn't figure it out 
Most of it got replaced by functions with better working functions
****/

// not needed because of the getSurroundingGridTileTypesIn8Directions() function
/*
// gets the grid tile coordinates of all tiles surroudning a player a position
vector<Vector2i> getSurroundingTileCoords(Vector2f previousPosition, String**& m_GridTileType)
{
	Vector2i currentTile = getGridTileMapPosition(previousPosition);

	vector<Vector2i> surroundingTileCoords;

	// set the default values of all surrounding tiles to coord
	for (int i = 0; i < 8; i++)
	{
		surroundingTileCoords.push_back(currentTile);
	}
	// n = 0
	surroundingTileCoords[0].x = currentTile.x;
	surroundingTileCoords[0].y = currentTile.y - 1;
	// ne = 1
	surroundingTileCoords[1].x = currentTile.x + 1;
	surroundingTileCoords[1].y = currentTile.y - 1;
	// e = 2
	surroundingTileCoords[2].x = currentTile.x + 1;
	surroundingTileCoords[2].y = currentTile.y;
	// se = 3
	surroundingTileCoords[3].x = currentTile.x + 1;
	surroundingTileCoords[3].y = currentTile.y + 1;
	// s = 4
	surroundingTileCoords[4].x = currentTile.x;
	surroundingTileCoords[4].y = currentTile.y + 1;
	// sw = 5
	surroundingTileCoords[5].x = currentTile.x - 1;
	surroundingTileCoords[5].y = currentTile.y + 1;
	// w = 6
	surroundingTileCoords[6].x = currentTile.x - 1;
	surroundingTileCoords[6].y = currentTile.y;
	// nw = 7
	surroundingTileCoords[7].x = currentTile.x - 1;
	surroundingTileCoords[7].y = currentTile.y - 1;

	return surroundingTileCoords;
}
*/

/*
Vector2f getArenaXYCoordsInGridTile(Vector2i gridTileCoords)
{
	Vector2f arenaCoordsInTile;
	float x = gridTileCoords.x * 50;
	float y = gridTileCoords.y * 50;

	arenaCoordsInTile.x = x;
	arenaCoordsInTile.y = y;

	return arenaCoordsInTile;
}
*/


/*
vector<bool> canMoveToSurroundingTiles(Vector2f previousPosition, String**& m_GridTileType, int& m_WorldWith)
{
	// Creates a vector containing the surrounding tile types in 8 directions
	// n = 0, ne = 1, e = 2, se = 3, s = 4, sw = 5, w = 6, nw = 7
	vector<String> surroundingTileTypes = getSurroundingGridTileTypesIn8Directions(previousPosition, m_GridTileType, m_WorldWith);

	vector<bool> canMoveToSurroundingGridTiles;

	// set the default values of all surrounding tiles to false
	for (int i = 0; i < 8; i++)
	{
		canMoveToSurroundingGridTiles.push_back(false);
	}

	// Check if the zombie can move n
	if (surroundingTileTypes[0] != "wall")
	{
		canMoveToSurroundingGridTiles[0] = true;
	}
	// Check if the zombie can move ne - ne and either n or e are not walls
	if (surroundingTileTypes[1] != "wall" && (surroundingTileTypes[0] != "wall" || surroundingTileTypes[2] != "wall"))
	{
		canMoveToSurroundingGridTiles[1] = true;
	}
	// Check if the zombie can move e
	if (surroundingTileTypes[2] != "wall")
	{
		canMoveToSurroundingGridTiles[2] = true;
	}
	// Check if the zombie can move se - sw and either s or e are not walls
	if (surroundingTileTypes[3] != "wall" && (surroundingTileTypes[2] != "wall" || surroundingTileTypes[4] != "wall"))
	{
		canMoveToSurroundingGridTiles[3] = true;
	}
	// Check if the zombie can move s
	if (surroundingTileTypes[4] != "wall")
	{
		canMoveToSurroundingGridTiles[4] = true;
	}
	// Check if the zombie can move sw - sw and either s or w are not walls
	if (surroundingTileTypes[5] != "wall" && (surroundingTileTypes[4] != "wall" || surroundingTileTypes[6] != "wall"))
	{
		canMoveToSurroundingGridTiles[5] = true;
	}
	// Check if the zombie can move w
	if (surroundingTileTypes[6] != "wall")
	{
		canMoveToSurroundingGridTiles[6] = true;
	}
	// Check if the zombie can move nw - nw and either n or w are not walls
	if (surroundingTileTypes[7] != "wall" && (surroundingTileTypes[6] != "wall" || surroundingTileTypes[0] != "wall"))
	{
		canMoveToSurroundingGridTiles[7] = true;
	}

	return canMoveToSurroundingGridTiles;
}
*/

// caused zombies to get stuck
/*
bool canMoveIntoGridTile(Vector2f position, Vector2f previousPosition, String**& m_GridTileType)
{
	Vector2f previousPos = previousPosition;
	Vector2f currentPos = position;
	Vector2i previousGridTilePos = getGridTileMapPosition(previousPos, m_GridTileType);
	Vector2i currentGridTilePos = getGridTileMapPosition(currentPos, m_GridTileType);

	vector<Vector2i> surroundingTileCoords = getSurroundingTileCoords(previousPosition, m_GridTileType);

	// n = 0, ne = 1, e = 2, se = 3, s = 4, sw = 5, w = 6, nw = 7
	vector<bool> canMoveToSurroundingGridTiles = canMoveToSurroundingTiles(previousPos, m_GridTileType); // must be previous position (last position before entering a wall)
	bool canMoveIntoTile = false;

	// if gameactor is travelling north
	if (currentGridTilePos == surroundingTileCoords[0])
	{
		if (canMoveToSurroundingGridTiles[0])
		{
			canMoveIntoTile = true;
		}
		else
		{
			canMoveIntoTile = false;
		}
	}

	// if gameactor is travelling northeast
	if (currentGridTilePos == surroundingTileCoords[1])
	{
		if (canMoveToSurroundingGridTiles[1])
		{
			canMoveIntoTile = true;
		}
		else
		{
			canMoveIntoTile = false;
		}
	}

	// if gameactor is travelling east
	if (currentGridTilePos == surroundingTileCoords[2])
	{
		if (canMoveToSurroundingGridTiles[2])
		{
			canMoveIntoTile = true;
		}
		else
		{
			canMoveIntoTile = false;
		}
	}

	// if gameactor is travelling southeast
	if (currentGridTilePos == surroundingTileCoords[3])
	{
		if (canMoveToSurroundingGridTiles[3])
		{
			canMoveIntoTile = true;
		}
		else
		{
			canMoveIntoTile = false;
		}
	}

	// if gameactor is travelling south
	if (currentGridTilePos == surroundingTileCoords[4])
	{
		if (canMoveToSurroundingGridTiles[4])
		{
			canMoveIntoTile = true;
		}
		else
		{
			canMoveIntoTile = false;
		}
	}

	// if gameactor is travelling southwest
	if (currentGridTilePos == surroundingTileCoords[5])
	{
		if (canMoveToSurroundingGridTiles[5])
		{
			canMoveIntoTile = true;
		}
		else
		{
			canMoveIntoTile = false;
		}
	}

	// if gameactor is travelling west
	if (currentGridTilePos == surroundingTileCoords[6])
	{
		if (canMoveToSurroundingGridTiles[6])
		{
			canMoveIntoTile = true;
		}
		else
		{
			canMoveIntoTile = false;
		}
	}

	// if gameactor is travelling northwest
	if (currentGridTilePos == surroundingTileCoords[7])
	{
		if (canMoveToSurroundingGridTiles[7])
		{
			canMoveIntoTile = true;
		}
		else
		{
			canMoveIntoTile = false;
		}
	}

	return canMoveIntoTile;
}
*/