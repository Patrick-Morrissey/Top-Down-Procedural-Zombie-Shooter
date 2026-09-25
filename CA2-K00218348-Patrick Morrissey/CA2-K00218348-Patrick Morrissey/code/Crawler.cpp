#include "Crawler.h"
#include "TextureHolder.h"

using namespace std;

Crawler::Crawler()
{

}

void Crawler::spawn(float startX, float startY, int seed, int tileSize, String**& m_GridTileType, int& m_WorldWidth)
{
	// Crawler
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/crawler.png"));
	m_Sprite.setOrigin(25, 17);
	m_Speed = CRAWLER_SPEED;
	m_Health = CRAWLER_HEALTH;
	m_CollidesWithWalls = true;

	Zombie::spawn(startX, startY, seed, tileSize, m_GridTileType, m_WorldWidth);
}