#pragma once
#include <SFML/Graphics.hpp>
#include "Zombie.h"

using namespace sf;

class Bloater : public Zombie
{
private:
	// How fast is the zombie?
	const float BLOATER_SPEED = 40;

	// How tough is zombie
	const float BLOATER_HEALTH = 5;

	// Public prototypes go here	
public:
	Bloater();

	// Spawn a new zombie
	void spawn(float startX, float startY, int seed, int tileSize, String**& m_GridTileType, int& m_WorldWidth) override;

};