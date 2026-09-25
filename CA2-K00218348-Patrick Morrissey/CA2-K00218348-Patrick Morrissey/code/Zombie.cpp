#include "zombie.h"
#include "TextureHolder.h"
#include "ZombieArena.h"
#include <cstdlib>
#include <ctime>

#include <iostream>

using namespace std;

Zombie::Zombie()
{

}

void Zombie::spawn(float startX, float startY, int seed, int tileSize, String**& m_GridTileType, int& m_WorldWidth)
{
    m_ZombieGridTileType = m_GridTileType;
    m_TileSize = tileSize;
    m_GMCopyWorldWidth = m_WorldWidth;
    m_Alive = true;
    // Modify the speed to make the zombie unique
    // Every zombie is unique. Create a speed modifier
    srand((int)time(0) + (seed * 2));
    // Somewhere between 80 an 100
    float modifier = (rand() % MAX_VARRIANCE) + OFFSET;
    // Express as a fraction of 1
    modifier /= 100; // Now equals between .7 and 1
    m_Speed *= modifier;
    //m_Speed = 1000;
    m_Position.x = startX;
    m_Position.y = startY;


    m_Sprite.setPosition(m_Position);

    // for testing only - remove when ready
    //m_Speed = 0;

}

bool Zombie::hit()
{
    m_Health--;

    if (m_Health < 0)
    {
        // dead
        m_Alive = false;
        m_Sprite.setTexture(TextureHolder::GetTexture(
            "graphics/blood.png"));

        return true;
    }
    // injured but not dead yet
    return false;

}

bool Zombie::isAlive()
{
    return m_Alive;
}

void Zombie::update(float elapsedTime,
    Vector2f playerLocation)
{
    Vector2f previousPos = m_Position;

    float playerX = playerLocation.x;
    float playerY = playerLocation.y;

    // Update the zombie position variables
    if (playerX > m_Position.x)
    {
        m_Position.x = m_Position.x +
            m_Speed * elapsedTime;
    }

    if (playerY > m_Position.y)
    {
        m_Position.y = m_Position.y +
            m_Speed * elapsedTime;
    }

    if (playerX < m_Position.x)
    {
        m_Position.x = m_Position.x -
            m_Speed * elapsedTime;
    }

    if (playerY < m_Position.y)
    {
        m_Position.y = m_Position.y -
            m_Speed * elapsedTime;
    }

    if (getCollidesWithWall())
    {
        // checks if the zombie is entering a new grid tile by checking if the current grid tile coordinates are the same the previous coordinates
        bool enteringNewTile = isEnteringNewTile(m_Position, previousPos);

        // Stops the zombie from going through tidy gaps between diagonal square wall tiles
        bool bothAdjacentTilesAreWalls = false;
        if (enteringNewTile)
        {
            // Checks if both of the adjacent tiles are walls in the direction the zombies is travelling
            bothAdjacentTilesAreWalls = getMovementDirDiagonalAdjacentTileTypesWalls(m_Position, previousPos, m_ZombieGridTileType, m_GMCopyWorldWidth);
        }

        // code for stopping at internal walls and changing direction - occurs if you hit a wall or tiny gap between diagopnal walls
        if (getGridTileType(m_Position, m_ZombieGridTileType, m_GMCopyWorldWidth) == "wall" || bothAdjacentTilesAreWalls)
        {
            // returns the zombie to their position before colliding with a wall so the next calculation will work and zombies won't still walk through walls
            m_Position = previousPos;

            while (m_Position == previousPos)
            {
                // gets a new position for the zombie that won't move them into a wall and is the next shortest distance from the player
                m_Position = getNewPositionIfStuck(elapsedTime, playerLocation, previousPos);
            }
        }
    }
    

    // Move the sprite
    m_Sprite.setPosition(m_Position);

    // Face the sprite in the correct direction
    float angle = (atan2(playerY - m_Position.y,
        playerX - m_Position.x)
        * 180) / 3.141;

    m_Sprite.setRotation(angle);

}

bool Zombie::getCollidesWithWall()
{
    return m_CollidesWithWalls;
}

// Calculate the distance to the player using the distance formula
float Zombie::getDistanceToPlayer(Vector2f zombiePosition, Vector2f playerLocation)
{
    float distX = playerLocation.x - zombiePosition.x;
    float distY = playerLocation.y - zombiePosition.y;

    float distanceToPlayer = sqrtf((distX * distX) + (distY * distY));

    return distanceToPlayer;
}

Vector2f Zombie::getNewPositionIfStuck(float elapsedTime, Vector2f playerLocation, Vector2f previousLocation)
{
    Vector2f newPosition = m_Position;
    float speedModifier = 2;
    // speeds up the zombie while they are sliding against walls
    m_Speed = m_Speed * speedModifier;
    // up = 0, up and left = 1, up and right = 2, down = 3, down and left = 4, down and right = 5, left = 6, right = 7
    Vector2f newPositionOptions[8];
    // Calculates the x and y coordinates if the zombie goes up
    newPositionOptions[0].x = m_Position.x;
    newPositionOptions[0].y = m_Position.y - m_Speed * elapsedTime;
    // Calculates the x and y coordinates if the zombie goes up and left
    newPositionOptions[1].x = m_Position.x - m_Speed * elapsedTime;
    newPositionOptions[1].y = m_Position.y - m_Speed * elapsedTime;
    // Calculates the x and y coordinates if the zombie goes up and left
    newPositionOptions[2].x = m_Position.x + m_Speed * elapsedTime;
    newPositionOptions[2].y = m_Position.y - m_Speed * elapsedTime;
    // Calculates the x and y coordinates if the zombie goes down
    newPositionOptions[3].x = m_Position.x;
    newPositionOptions[3].y = m_Position.y + m_Speed * elapsedTime;
    // Calculates the x and y coordinates if the zombie goes down and left
    newPositionOptions[4].x = m_Position.x - m_Speed * elapsedTime;
    newPositionOptions[4].y = m_Position.y + m_Speed * elapsedTime;
    // Calculates the x and y coordinates if the zombie goes down and right
    newPositionOptions[5].x = m_Position.x + m_Speed * elapsedTime;
    newPositionOptions[5].y = m_Position.y + m_Speed * elapsedTime;
    // Calculates the x and y coordinates if the zombie goes left
    newPositionOptions[6].x = m_Position.x - m_Speed * elapsedTime;
    newPositionOptions[6].y = m_Position.y;
    // Calculates the x and y coordinates if the zombie goes right
    newPositionOptions[7].x = m_Position.x + m_Speed * elapsedTime;
    newPositionOptions[7].y = m_Position.y;

    // resets the zombie speed back to its normal value
    m_Speed = m_Speed / speedModifier;

    //float smallestDistance = 0;
    float smallestDistance = FLT_MAX; // setting the max value of variables - https://www.geeksforgeeks.org/cpp/stdnumeric_limitsmax-and-stdnumeric_limitsmin-in-c/
    // Zombies can't spawn in walls so at least one direction has to be a floor
    // loops through the array to find the movement direction that won't put the zombie in a wall and gets them closest to the player
    for (int i = 0; i < 8; i++)
    {
        float distanceToPlayer = getDistanceToPlayer(newPositionOptions[i], playerLocation);

        // Sets the smallest distance to the first element of the nextPositionOptions array's distance from the player
        if (smallestDistance == 0.0)
        {
            smallestDistance = distanceToPlayer;
        }

        // If the distance from the newPositionOptions element isn't located in a wall and isn't the previous location
        if (getGridTileType(newPositionOptions[i], m_ZombieGridTileType, m_GMCopyWorldWidth) != "wall" && newPositionOptions[i] != previousLocation)
        {
            newPosition = newPositionOptions[i];

            // If the distance from that position is less than or equal to the smallestDistance value, that value is set as the newPosition to move to
            if (distanceToPlayer < smallestDistance)
            {
                smallestDistance = distanceToPlayer;
                newPosition = newPositionOptions[i];
            }
        }
    }
    return newPosition;
}