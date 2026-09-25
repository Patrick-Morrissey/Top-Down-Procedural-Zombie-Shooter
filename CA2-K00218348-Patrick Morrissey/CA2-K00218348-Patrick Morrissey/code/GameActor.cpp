#include "GameActor.h"

GameActor::GameActor()
{
	
}

Vector2f GameActor::getCenter()
{
	return m_Position;
}

Time GameActor::getLastHitTime()
{
	return m_LastHit;
}

FloatRect GameActor::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Sprite GameActor::getSprite()
{
	return m_Sprite;
}

String GameActor::getType()
{
	return m_Type;
}

int GameActor::getHealth()
{
	return m_Health;
}

GameActor::~GameActor()
{

}