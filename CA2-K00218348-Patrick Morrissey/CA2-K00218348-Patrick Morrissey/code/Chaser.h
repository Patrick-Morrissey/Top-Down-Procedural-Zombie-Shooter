#pragma once
#include <SFML/Graphics.hpp>
#include "Zombie.h"

using namespace sf;

class Chaser : public Zombie
{
private:
	// How fast is the zombie?
	const float CHASER_SPEED = 80;

	// How tough is the zombie
	const float CHASER_HEALTH = 1;

	// Public prototypes go here	
public:
	Chaser();

	// Spawn a new zombie
	void spawn(float startX, float startY, int seed, int tileSize, String**& m_GridTileType, int& m_WorldWidth) override;

};