#pragma once
#include <SFML/Graphics.hpp>
#include "GameActor.h"


using namespace sf;

class Zombie : public GameActor
{
protected:

	// Make each zombie vary its speed slightly
	const int MAX_VARRIANCE = 30;
	const int OFFSET = 101 - MAX_VARRIANCE;


	// Is it still alive?
	bool m_Alive;

	// Does the zombie collide with walls
	bool m_CollidesWithWalls;

	// A pointer to the shared 2d array grid tile map for the game to be used by zombie
	String** m_ZombieGridTileType;

	// Public prototypes go here	
public:
	Zombie();

	// Handle when a bullet hits a zombie
	bool hit();

	// Find out if the zombie is alive
	bool isAlive();

	// find out if the zombie collides with walls
	bool getCollidesWithWall();

	float getDistanceToPlayer(Vector2f zombiePosition, Vector2f playerLocation);

	Vector2f getNewPositionIfStuck(float elapsedTime, Vector2f playerLocation, Vector2f previousLocation);

	// Spawn a new zombie
	virtual void spawn(float startX, float startY, int seed, int tileSize, String**& m_GridTileType, int& m_WorldWidth);

	// Update the zombie each frame
	virtual void update(float elapsedTime, Vector2f playerLocation);
};


