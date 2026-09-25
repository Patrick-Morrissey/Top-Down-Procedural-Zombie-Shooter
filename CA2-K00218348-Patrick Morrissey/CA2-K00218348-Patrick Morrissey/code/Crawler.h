#pragma once
#include <SFML/Graphics.hpp>
#include "Zombie.h"

using namespace sf;

class Crawler : public Zombie
{
private:
	// How fast is the zombie?
	const float CRAWLER_SPEED = 20;

	// How tough is the zombie
	const float CRAWLER_HEALTH = 3;

	// Public prototypes go here	
public:
	Crawler();

	// Spawn a new zombie
	void spawn(float startX, float startY, int seed, int tileSize, String**& m_GridTileType, int& m_WorldWidth) override;

};