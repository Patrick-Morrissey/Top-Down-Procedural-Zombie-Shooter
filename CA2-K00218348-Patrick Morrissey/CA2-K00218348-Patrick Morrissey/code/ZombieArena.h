#pragma once
#include "Zombie.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <cstdlib>

using namespace sf;
using namespace std;

// in CreateBackground.cpp
int createBackground(VertexArray& rVA, IntRect arena, String**& m_GridTileType, int& m_WorldWidth, int& m_WorldHeight);
void smooth(int width, int height, String**& m_GridTileType, int numRepeats);
int countWalls(int width, int height, String**& m_GridTileType);

// in CreateHorde.cpp
vector<Zombie*> createHorde(int numZombies, int tileSize, IntRect arena, String**& m_GridTileType, int& m_WorldHeight);

// in GridTileMapFunctions.cpp
Vector2i getGridTileMapCoords(Vector2f position);
String getGridTileType(Vector2f position, String**& m_GridTileType, int& m_WorldWidth);
vector<String> getSurroundingGridTileTypesIn8Directions(Vector2f previousPosition, String**& m_GridTileType, int& m_WorldWidth);
bool getMovementDirDiagonalAdjacentTileTypesWalls(Vector2f position, Vector2f previousPosition, String**& m_GridTileType, int& m_WorldWidth);
bool isEnteringNewTile(Vector2f position, Vector2f previousPosition);
int countWallsAroundTile(Vector2f position, String**& m_GridTileType, int& m_WorldWidth);
bool isPositionOutofGridBounds(Vector2f position, int& m_WorldWidth);