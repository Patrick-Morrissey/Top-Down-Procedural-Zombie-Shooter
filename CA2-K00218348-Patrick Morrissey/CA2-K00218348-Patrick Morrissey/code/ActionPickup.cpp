#include "ActionPickup.h"
#include "TextureHolder.h"

ActionPickup::ActionPickup()
{

}


void ActionPickup::spawn()
{
	Pickup::spawn();
	m_Spawned = false;
	m_SecondsToWait = START_WAIT_TIME;
}


void ActionPickup::update(float elapsedTime)
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

void ActionPickup::setSpawned(bool spawned)
{
	m_Spawned = spawned;
}

void ActionPickup::upgrade()
{
	// Make them more frequent and last longer
	m_SecondsToLive += (START_SECONDS_TO_LIVE / 10);
	m_SecondsToWait -= (START_WAIT_TIME / 10);
}

void ActionPickup::gotIt()
{
	m_Spawned = false;
	m_SecondsSinceDeSpawn = 0;
}
