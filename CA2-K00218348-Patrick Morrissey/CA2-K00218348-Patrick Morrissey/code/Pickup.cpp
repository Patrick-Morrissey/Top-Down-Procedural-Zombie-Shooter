#include "Pickup.h"
#include "TextureHolder.h"

Pickup::Pickup()
{
	
	
}

void Pickup::setArena(IntRect arena)
{
	// Copy the details of the arena to the pickup's m_Arena
	m_Arena.left = arena.left + 50;
	m_Arena.width = arena.width - 50;
	m_Arena.top = arena.top + 50;
	m_Arena.height = arena.height - 50;

	//spawn();
}


void Pickup::spawn()
{
	m_Sprite.setOrigin(25, 25);

	m_SecondsToLive = START_SECONDS_TO_LIVE;
}

void Pickup::setPosition(float x, float y)
{
	m_Sprite.setPosition(x, y);
	m_Spawned = true;
	m_SecondsSinceSpawn = 0;
}


FloatRect Pickup::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Sprite Pickup::getSprite()
{
	return m_Sprite;
}

bool Pickup::isSpawned()
{
	return m_Spawned;
}

int Pickup::getValue()
{
	return m_Value;
}