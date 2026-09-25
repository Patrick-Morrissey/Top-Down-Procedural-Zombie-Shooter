#pragma once
#include <SFML/Graphics.hpp>
#include "Pickup.h"

using namespace sf;

class StatPickup : public Pickup
{
protected:
	const int START_WAIT_TIME = 10;

	float m_SecondsSinceDeSpawn;
	float m_SecondsToWait;

	// Public prototypes go here
public:

	StatPickup();

	// Prepare a new pickup

	virtual void spawn();

	// Let the pickup update itself each frame
	virtual void update(float elapsedTime);

	// Get the goodness from the pickup
	void gotIt() override;

	// Upgrade the value of each pickup
	virtual void upgrade();
};

