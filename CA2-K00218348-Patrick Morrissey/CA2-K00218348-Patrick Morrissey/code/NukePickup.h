#pragma once
#include <SFML/Graphics.hpp>
#include "ActionPickup.h"

using namespace sf;

class NukePickup : public ActionPickup
{
protected:
	//Start value for health pickups
	const int NUKE_START_VALUE = 2;

	// Public prototypes go here
public:

	NukePickup();

	// Prepare a new pickup

	void spawn() override;

	// Let the pickup update itself each frame
	void update(float elapsedTime) override;

	// Upgrade the value of each pickup
	void upgrade() override;

};