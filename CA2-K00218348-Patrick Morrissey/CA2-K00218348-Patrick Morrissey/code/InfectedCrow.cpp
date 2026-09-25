#include "InfectedCrow.h"
#include "TextureHolder.h"

using namespace std;

InfectedCrow::InfectedCrow()
{

}

void InfectedCrow::spawn(float startX, float startY, int seed, int tileSize, String**& m_GridTileType, int& m_WorldWidth)
{
	// InfectedCrow
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/infectedCrow.png")); // source - https://www.pngegg.com/en/png-bsptb
	m_Sprite.setOrigin(10, 20);
	m_Speed = INFECTEDCROW_SPEED;
	m_Health = INFECTEDCROW_HEALTH;
    m_CollidesWithWalls = false;

	Zombie::spawn(startX, startY, seed, tileSize, m_GridTileType, m_WorldWidth);
}