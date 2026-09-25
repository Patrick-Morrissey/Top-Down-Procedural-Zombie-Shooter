#include "Bloater.h"
#include "TextureHolder.h"

using namespace std;

Bloater::Bloater()
{

}

void Bloater::spawn(float startX, float startY, int seed, int tileSize, String**& m_GridTileType, int& m_WorldWidth)
{
	// Bloater
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/bloater.png"));
	m_Sprite.setOrigin(30, 30);
	m_Speed = BLOATER_SPEED;
	m_Health = BLOATER_HEALTH;
	m_CollidesWithWalls = true;

	Zombie::spawn(startX, startY, seed, tileSize, m_GridTileType, m_WorldWidth);
}