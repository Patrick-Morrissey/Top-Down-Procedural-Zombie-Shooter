#pragma once
#include <SFML/Graphics.hpp>
#include "Zombie.h"

using namespace sf;

class InfectedCrow : public Zombie
{
private:
	// How fast is the zombie?
	const float INFECTEDCROW_SPEED = 90;

	// How tough is zombie
	const float INFECTEDCROW_HEALTH = 1;

	// Public prototypes go here	
public:
	InfectedCrow();

	// Spawn a new zombie
	void spawn(float startX, float startY, int seed, int tileSize, String**& m_GridTileType, int& m_WorldWidth) override;

};
