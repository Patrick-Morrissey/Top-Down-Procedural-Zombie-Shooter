#include "RevolverPickup.h"
#include "TextureHolder.h"

RevolverPickup::RevolverPickup()
{
	m_Value = m_StartingActiveTime;
}

void RevolverPickup::spawn()
{
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/revolver_pickup.png")); // https://itch.io/game-assets/tag-revolver

	
	ActionPickup::spawn();
}

void RevolverPickup::update(float elapsedTime)
{
	ActionPickup::update(elapsedTime);

	// Do we need to spawn a pickup - this part of update is here so this class's version of spawn is called and not statpickup's versio
	if (m_SecondsSinceDeSpawn > m_SecondsToWait && !m_Spawned)
	{
		// spawn the pickup and reset the timer
		spawn();
	}
}

void RevolverPickup::upgrade()
{
	m_Value += m_StartingActiveTime;
	// calling a base class function from a derived class function
	ActionPickup::upgrade();
}