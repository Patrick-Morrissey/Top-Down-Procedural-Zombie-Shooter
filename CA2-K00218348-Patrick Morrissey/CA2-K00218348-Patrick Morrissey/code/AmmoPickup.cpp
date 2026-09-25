#include "AmmoPickup.h"
#include "TextureHolder.h"

AmmoPickup::AmmoPickup()
{

}

void AmmoPickup::spawn()
{
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/ammo_pickup.png"));

	// How much is pickup worth
	m_Value = AMMO_START_VALUE;

	StatPickup::spawn();
}

void AmmoPickup::update(float elapsedTime)
{
	StatPickup::update(elapsedTime);

	// Do we need to spawn a pickup - this part of update is here so this class's version of spawn is called and not statpickup's versio
	if (m_SecondsSinceDeSpawn > m_SecondsToWait && !m_Spawned)
	{
		// spawn the pickup and reset the timer
		spawn();
	}
}

void AmmoPickup::upgrade()
{
	m_Value += (AMMO_START_VALUE * .5);

	// calling a base class function from a derived class function
	StatPickup::upgrade();
}