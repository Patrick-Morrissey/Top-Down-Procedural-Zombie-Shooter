#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Pickup
{
protected:
	// Start value for health pickups
	//const int NUKE_START_VALUE = 2;
	//const int START_WAIT_TIME = 10;
	const int START_SECONDS_TO_LIVE = 5;

	// The sprite that represents this pickup
	Sprite m_Sprite;

	// The arena it exists in
	IntRect m_Arena;

	// How much is this pickup worth?
	int m_Value;

	// Handle spawning and disappearing
	bool m_Spawned;
	float m_SecondsSinceSpawn;
	//float m_SecondsSinceDeSpawn;
	float m_SecondsToLive;
	//float m_SecondsToWait;

	// Public prototypes go here
public:

	Pickup();

	// Prepare a new pickup
	void setArena(IntRect arena);

	virtual void spawn();

	void setPosition(float x, float y);

	// Check the position of a pickup
	FloatRect getPosition();

	// Get the sprite for drawing
	Sprite getSprite();

	// Let the pickup update itself each frame - pure virtual method
	virtual void update(float elapsedTime) = 0;

	// Is this pickup currently spawned?
	bool isSpawned();

	// Get the goodness from the pickup - pure virtual method
	virtual void gotIt() = 0;

	// return the value of the m_Value variable
	int getValue();

	// Upgrade the value of each pickup
	virtual void upgrade() = 0;

};