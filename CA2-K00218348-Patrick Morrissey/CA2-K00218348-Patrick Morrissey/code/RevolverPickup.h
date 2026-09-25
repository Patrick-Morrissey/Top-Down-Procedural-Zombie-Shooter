#pragma once
#include <SFML/Graphics.hpp>
#include "ActionPickup.h"

using namespace sf;

class RevolverPickup : public ActionPickup
{
protected:

	const int m_StartingActiveTime = 5;

	// Public prototypes go here
public:

	RevolverPickup();

	// Prepare a new pickup

	void spawn() override;

	// Let the pickup update itself each frame
	void update(float elapsedTime) override;

	// Upgrade the value of each pickup
	void upgrade() override;



};
