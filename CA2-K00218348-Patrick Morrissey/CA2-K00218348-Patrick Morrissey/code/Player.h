#pragma once
#include <SFML/Graphics.hpp>
#include "GameActor.h"
#include "ZombieArena.h"

using namespace sf;

class Player : public GameActor
{
private:
	const float START_SPEED = 200;
	const float START_HEALTH = 100;

	// And a texture
	// !!Watch this space!!
	// May not be needed - remove
	Texture m_Texture;

	// What is the screen resolution
	Vector2f m_Resolution;

	// What size is the current arena
	IntRect m_Arena;

	// A pointer to the shared 2d array grid tile map for the game to be used by the player
	String** m_PlayerGridTileType;

	

	// Which directions is the player currently moving in
	bool m_UpPressed;
	bool m_DownPressed;
	bool m_LeftPressed;
	bool m_RightPressed;

	// What is the maximum health the player can have
	int m_MaxHealth;

	// All our public functions will come next
public:

	Player();

	// Call this at the end of every game
	void resetPlayerStats();

	void spawn(IntRect arena, Vector2f resolution, int tileSize, String**& m_GridTileType, int& m_WorldWidth);

	// Handle the player getting hit by a zombie
	bool hit(Time timeHit);

	// Which angle is the player facing
	float getRotation();

	// The next four functions move the player
	void moveLeft();

	void moveRight();

	void moveUp();

	void moveDown();

	// Stop the player moving in a specific direction
	void stopLeft();

	void stopRight();

	void stopUp();

	void stopDown();

	// We will call this function once every frame
	void update(float elapsedTime, Vector2i mousePosition);

	// Give player a speed boost
	void upgradeSpeed();

	// Give the player some health
	void upgradeHealth();

	// Increase the maximum amount of health the player can have
	void increaseHealthLevel(int amount);


};
