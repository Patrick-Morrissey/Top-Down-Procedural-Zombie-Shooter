#include "StatPickup.h"
#include "TextureHolder.h"

StatPickup::StatPickup()
{
	
}


void StatPickup::spawn()
{
	Pickup::spawn();

	// Spawn at a random location	
	// anywhere inside the world walls
	int x = (rand() % m_Arena.width - m_Arena.left) + m_Arena.left;
	int y = (rand() % m_Arena.height - m_Arena.top) + m_Arena.top;

	//int x = (m_Arena.width - m_Arena.left) + m_Arena.left;
	//int y = (m_Arena.height - m_Arena.top) + m_Arena.top;

	//int x = m_Arena.left;
	//int y = m_Arena.top;

	m_SecondsSinceSpawn = 0;


	m_Sprite.setPosition(x, y);

	m_Spawned = true;
	m_SecondsToWait = START_WAIT_TIME;
}


void StatPickup::update(float elapsedTime)
{
	if (m_Spawned)
	{
		m_SecondsSinceSpawn += elapsedTime;
	}
	else
	{
		m_SecondsSinceDeSpawn += elapsedTime;
	}


	// Do we need to hide a pickup?
	if (m_SecondsSinceSpawn > m_SecondsToLive && m_Spawned)
	{
		// Remove the pickup and put it somewhere else
		m_Spawned = false;
		m_SecondsSinceDeSpawn = 0;
	}
}

void StatPickup::upgrade()
{
	// Make them more frequent and last longer
	m_SecondsToLive += (START_SECONDS_TO_LIVE / 10);
	m_SecondsToWait -= (START_WAIT_TIME / 10);
}

void StatPickup::gotIt()
{
	m_Spawned = false;
	m_SecondsSinceDeSpawn = 0;
}
