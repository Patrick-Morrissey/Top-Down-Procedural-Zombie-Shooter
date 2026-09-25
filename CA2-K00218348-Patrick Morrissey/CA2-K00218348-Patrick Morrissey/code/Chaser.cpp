#include "Chaser.h"
#include "TextureHolder.h"

using namespace std;

Chaser::Chaser()
{

}

void Chaser::spawn(float startX, float startY, int seed, int tileSize, String**& m_GridTileType, int& m_WorldWidth)
{
	// Chaser
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/chaser.png"));
	m_Sprite.setOrigin(14, 21);
	m_Speed = CHASER_SPEED;
	m_Health = CHASER_HEALTH;
	m_CollidesWithWalls = true;

	Zombie::spawn(startX, startY, seed, tileSize, m_GridTileType, m_WorldWidth);
}