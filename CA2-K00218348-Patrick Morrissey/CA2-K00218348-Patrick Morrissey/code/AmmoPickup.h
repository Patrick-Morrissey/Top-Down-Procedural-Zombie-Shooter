#pragma once
#include <SFML/Graphics.hpp>
#include "StatPickup.h"

using namespace sf;

class AmmoPickup : public StatPickup
{
protected:
	//Start value for health pickups
	const int AMMO_START_VALUE = 12;

	// Public prototypes go here
public:

	AmmoPickup();

	// Prepare a new pickup

	void spawn() override;

	// Let the pickup update itself each frame
	void update(float elapsedTime) override;

	// Upgrade the value of each pickup
	void upgrade() override;

};