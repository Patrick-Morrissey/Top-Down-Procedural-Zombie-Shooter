#include <sstream>
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ZombieArena.h"
#include "GameManager.h"
#include "GameActor.h"
#include "Player.h"
#include "TextureHolder.h"
#include "Bullet.h"
#include "Pickup.h"
#include "StatPickup.h"
#include "ActionPickup.h"
#include "HealthPickup.h"
#include "AmmoPickup.h"
#include "NukePickup.h"
#include <cstdlib>
#include <list>

using namespace sf;

using namespace std;

int main()
{
	GameManager game;

	game.play();

	return 0;
}