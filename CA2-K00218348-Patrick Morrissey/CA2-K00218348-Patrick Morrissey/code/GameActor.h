#pragma once
#include <SFML/Graphics.hpp>


using namespace sf;

class GameActor
{
protected:

	// Where is the gameactor
	Vector2f m_Position;

	// How big is each tile of the arena
	int m_TileSize;

	int m_GMCopyWorldWidth;

	// Of course we will need a sprite
	Sprite m_Sprite;

	String m_Type;

	// How much health has the gameactor got?
	int m_Health;

	// When was the gameactor last hit
	Time m_LastHit;

	// Speed in pixels per second
	float m_Speed;


	// All our public functions will come next
public:

	GameActor();

	// Where is the center of the gameactor
	Vector2f getCenter();

	// How long ago was the gameactor last hit
	Time getLastHitTime();

	// Where is the gameactor
	FloatRect getPosition();

	// Send a copy of the sprite to main
	Sprite getSprite();

	// Get the type of gameactor
	String getType();

	// How much health has the gameactor currently got?
	int getHealth();

	virtual ~GameActor(); // virtual destructor for game actor so the dervived class will call the base class destructor and then its own
};
