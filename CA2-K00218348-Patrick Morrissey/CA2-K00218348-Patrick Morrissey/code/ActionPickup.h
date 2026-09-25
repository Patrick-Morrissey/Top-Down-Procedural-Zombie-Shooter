#pragma once
#include <SFML/Graphics.hpp>
#include "Pickup.h"

using namespace sf;

class ActionPickup : public Pickup
{
protected:
	const int START_WAIT_TIME = 10;

	// How much is this pickup worth?
	//int m_Value;


	float m_SecondsSinceDeSpawn;
	float m_SecondsToWait;

	// Public prototypes go here
public:

	ActionPickup();

	// Prepare a new pickup

	virtual void spawn();

	// Let the pickup update itself each frame
	virtual void update(float elapsedTime);

	// Get the goodness from the pickup
	void gotIt() override;

	void setSpawned(bool spawned);

	// Upgrade the value of each pickup
	virtual void upgrade();
};

