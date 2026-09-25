#include "NukePickup.h"
#include "TextureHolder.h"

NukePickup::NukePickup()
{

}

void NukePickup::spawn()
{
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/nuke.png")); // source - https://www.clipartmax.com/middle/m2H7i8H7G6m2N4i8_nuke-by-d0ct0rrr1cht0f3n-weapon/

	// How much is pickup worth
	m_Value = NUKE_START_VALUE;

	ActionPickup::spawn();
}

void NukePickup::update(float elapsedTime)
{
	ActionPickup::update(elapsedTime);

	// Do we need to spawn a pickup - this part of update is here so this class's version of spawn is called and not statpickup's version
	if (m_SecondsSinceDeSpawn > m_SecondsToWait && !m_Spawned)
	{
		// spawn the pickup and reset the timer
		spawn();
	}
}

void NukePickup::upgrade()
{
	m_Value += (NUKE_START_VALUE * .5);

	// calling a base class function from a derived class function
	ActionPickup::upgrade();
}