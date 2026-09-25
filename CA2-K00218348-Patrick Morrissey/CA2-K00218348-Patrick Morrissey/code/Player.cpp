#include "player.h"
#include "TextureHolder.h"

#include <iostream>
#include <vector>

using namespace std;

Player::Player()
{
	m_Speed = START_SPEED;
	m_Health = START_HEALTH;
	m_MaxHealth = START_HEALTH;

	// Associate a texture with the sprite
	// !!Watch this space!!
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/player.png"));

	// Set the origin of the sprite to the centre, 
	// for smooth rotation
	m_Sprite.setOrigin(20, 20);
}

void Player::resetPlayerStats()
{
	m_Speed = START_SPEED;
	m_Health = START_HEALTH;
	m_MaxHealth = START_HEALTH;
}

void Player::spawn(IntRect arena, Vector2f resolution, int tileSize, String**& m_GridTileType, int& m_WorldWidth)
{
	m_PlayerGridTileType = m_GridTileType;
	// Remember how big the tiles are in this arena
	m_TileSize = tileSize;
	m_GMCopyWorldWidth = m_WorldWidth;

	// Place the player in the middle of the arena
	m_Position.x = arena.width / 2;
	m_Position.y = arena.height / 2;

	// checks if the spawn position set is a wall and finds a new position if it is
	if (getGridTileType(m_Position, m_PlayerGridTileType, m_GMCopyWorldWidth) == "wall")
	{
		float newX, newY;
		Vector2i gridTileCoordinates;

		vector<String> surroundTileTypes = getSurroundingGridTileTypesIn8Directions(m_Position, m_PlayerGridTileType, m_GMCopyWorldWidth); // n = 0, ne = 1, e = 2, se = 3, s = 4, sw = 5, w = 6, nw = 7
		bool newSpawnFound = false;
		while (!newSpawnFound)
		{
			// If north isn't a wall, change spawn to there
			if (surroundTileTypes[0] != "wall")
			{
				m_Position.y -= m_TileSize;
				newSpawnFound = true;
			}
			// If ne isn't a wall, change spawn to there
			else if (surroundTileTypes[1] != "wall")
			{
				m_Position.x += m_TileSize;
				m_Position.y -= m_TileSize;
				newSpawnFound = true;
			}
			// If e isn't a wall, change spawn to there
			else if (surroundTileTypes[2] != "wall")
			{
				m_Position.x += m_TileSize;
				newSpawnFound = true;
			}
			// If se isn't a wall, change spawn to there
			else if (surroundTileTypes[3] != "wall")
			{
				m_Position.x += m_TileSize;
				m_Position.y += m_TileSize;
				newSpawnFound = true;
			}
			// If s isn't a wall, change spawn to there
			else if (surroundTileTypes[4] != "wall")
			{
				m_Position.y += m_TileSize;
				newSpawnFound = true;
			}
			// If sw isn't a wall, change spawn to there
			else if (surroundTileTypes[5] != "wall")
			{
				m_Position.x -= m_TileSize;
				m_Position.y += m_TileSize;
				newSpawnFound = true;
			}
			// If w isn't a wall, change spawn to there
			else if (surroundTileTypes[6] != "wall")
			{
				m_Position.x -= m_TileSize;
				newSpawnFound = true;
			}
			// If nw isn't a wall, change spawn to there
			else if (surroundTileTypes[7] != "wall")
			{
				m_Position.x -= m_TileSize;
				m_Position.y -= m_TileSize;
				newSpawnFound = true;
			}
			// If all four tiles beside the current tile are walls, change m_Position to one of the 4 tiles and check its surrounding tiles for a non-wall tile to spawn at
			else
			{
				newSpawnFound = false;
			}
			
			// If a new free spawn position has not been found, move randomly to one of the 4 tiles beside the current one and repeat the search process again
			if (!newSpawnFound)
			{
				int side = rand() % 4;

				switch (side)
				{
				case 0:
					m_Position.y -= m_TileSize;
					break;
				case 1:
					m_Position.y += m_TileSize;
					break;
				case 2:
					m_Position.x += m_TileSize;
					break;
				case 3:
					m_Position.x -= m_TileSize;
					break;
				}
			}
		}
	} // end of check to see if the spawn position set is a wall and finding a new position if it is

	

	// Copy the details of the arena to the player's m_Arena
	m_Arena.left = arena.left;
	m_Arena.width = arena.width;
	m_Arena.top = arena.top;
	m_Arena.height = arena.height;

	
	// Strore the resolution for future use
	m_Resolution.x = resolution.x;
	m_Resolution.y = resolution.y;

}


bool Player::hit(Time timeHit)
{
	if (timeHit.asMilliseconds() - m_LastHit.asMilliseconds() > 200)// 2 tenths of second
	{
		m_LastHit = timeHit;
		m_Health -= 10;
		return true;
	}
	else
	{
		return false;
	}

}

float Player::getRotation()
{
	return m_Sprite.getRotation();
}

void Player::moveLeft()
{
	m_LeftPressed = true;
}

void Player::moveRight()
{
	m_RightPressed = true;
}

void Player::moveUp()
{
	m_UpPressed = true;
}

void Player::moveDown()
{
	m_DownPressed = true;
}

void Player::stopLeft()
{
	m_LeftPressed = false;
}

void Player::stopRight()
{
	m_RightPressed = false;
}

void Player::stopUp()
{
	m_UpPressed = false;
}

void Player::stopDown()
{
	m_DownPressed = false;
}

void Player::update(float elapsedTime, Vector2i mousePosition)
{
	Vector2f previousPos = m_Position;

	if (m_UpPressed)
	{
		m_Position.y -= m_Speed * elapsedTime;
	}

	if (m_DownPressed)
	{
		m_Position.y += m_Speed * elapsedTime;
	}

	if (m_RightPressed)
	{
		m_Position.x += m_Speed * elapsedTime;
	}

	if (m_LeftPressed)
	{
		m_Position.x -= m_Speed * elapsedTime;
	}

	m_Sprite.setPosition(m_Position);



	// Keep the player in the arena
	if (m_Position.x > m_Arena.width - m_TileSize)
	{
		m_Position.x = m_Arena.width - m_TileSize;
	}

	if (m_Position.x < m_Arena.left + m_TileSize)
	{
		m_Position.x = m_Arena.left + m_TileSize;
	}

	if (m_Position.y > m_Arena.height - m_TileSize)
	{
		m_Position.y = m_Arena.height - m_TileSize;
	}

	if (m_Position.y < m_Arena.top + m_TileSize)
	{
		m_Position.y = m_Arena.top + m_TileSize;
	}

	// checks if the player is entering a new grid tile by checking if the current grid tile coordinates are the same the previous coordinates
	bool enteringNewTile = isEnteringNewTile(m_Position, previousPos);

	// Stops the player from going through tidy gaps between diagonal square wall tiles
	bool bothAdjacentTilesAreWalls = false;
	if (isEnteringNewTile)
	{
		// Checks if both of the adjacent tiles are walls in the direction the zombies is travelling
		bothAdjacentTilesAreWalls = getMovementDirDiagonalAdjacentTileTypesWalls(m_Position, previousPos, m_PlayerGridTileType, m_GMCopyWorldWidth);
	}

	// code for stopping at internal walls
	if (getGridTileType(m_Position, m_PlayerGridTileType, m_GMCopyWorldWidth) == "wall" || getGridTileType(m_Position, m_PlayerGridTileType, m_GMCopyWorldWidth) != "wall" && bothAdjacentTilesAreWalls)
	{
		// returns the player to their position before entering colliding with the wall
		m_Position = previousPos;
		
	}

	// Calculate the angle the player is facing
	float angle = (atan2(mousePosition.y - m_Resolution.y / 2,
		mousePosition.x - m_Resolution.x / 2)
		* 180) / 3.141;

	m_Sprite.setRotation(angle);
}

void Player::upgradeSpeed()
{
	// 20% speed upgrade
	m_Speed += (START_SPEED * .2);
}

void Player::upgradeHealth()
{
	// 20% max health upgrade
	m_MaxHealth += (START_HEALTH * .2);

}

void Player::increaseHealthLevel(int amount)
{
	m_Health += amount;

	// But not beyond the maximum
	if (m_Health > m_MaxHealth)
	{
		m_Health = m_MaxHealth;
	}
}

