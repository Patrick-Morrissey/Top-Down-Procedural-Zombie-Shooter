#include "GameManager.h"
#include <iostream>
using namespace std;

GameManager::GameManager()
{

}

void GameManager::init()
{
	// set the seed for the random number generator
	srand((int)time(0) * 10);

	// Create an instance of the Player class
	pPlayer = new Player();
	
	// Start with the GAME_OVER state
	m_State = State::GAME_OVER;

	// Get the screen resolution and create an SFML window
	m_Resolution.x = VideoMode::getDesktopMode().width;
	m_Resolution.y = VideoMode::getDesktopMode().height;

	// source of RenderWindow methods info - https://www.sfml-dev.org/documentation/2.4.2-fr/classsf_1_1RenderWindow.php
	m_Window.create(VideoMode(m_Resolution.x, m_Resolution.y),
		"Zombie Arena", Style::Fullscreen);

	// Create a an SFML View for the main action - source for how to use a setter for a view - https://www.sfml-dev.org/tutorials/3.0/graphics/view/
	m_MainView = View(sf::FloatRect(0, 0, m_Resolution.x, m_Resolution.y));

	// Load the texture for our background vertex array
	m_TextureBackground = TextureHolder::GetTexture(
		"graphics/background_sheet.png");

	// Set the ammo and firerate stats
	m_BulletsSpare = 30;
	m_BulletsInClip = 15;
	m_ClipSize = 15;
	m_FireRate = 1;

	// About the game
	m_Score = 0;
	m_HiScore = 0;
	m_StartingArenaWidth = 750;
	m_StartingArenaHeight = 750;

	// Hide the mouse pointer and replace it with crosshair
	m_Window.setMouseCursorVisible(true); // 
	m_TextureCrosshair = TextureHolder::GetTexture("graphics/crosshair.png");
	m_SpriteCrosshair.setTexture(m_TextureCrosshair);
	m_SpriteCrosshair.setOrigin(25, 25);

	// Create a couple of pickups
	pHealthPickup = new HealthPickup();
	pAmmoPickup = new AmmoPickup();
	pNukePickup = new NukePickup();
	pRevolverPickup = new RevolverPickup();
	

	// For the home/game over screen
	m_TextureGameOver = TextureHolder::GetTexture("graphics/background.png");
	m_SpriteGameOver.setTexture(m_TextureGameOver);
	m_SpriteGameOver.setPosition(0, 0);

	// Create a view for the HUD
	hudView = View(sf::FloatRect(0, 0, m_Resolution.x, m_Resolution.y));

	// Create a sprite for the ammo icon
	m_TextureAmmoIcon = TextureHolder::GetTexture("graphics/ammo_icon.png");
	m_SpriteAmmoIcon.setTexture(m_TextureAmmoIcon);
	m_SpriteAmmoIcon.setPosition(20, 980);

	// Create a sprite for the ammo icon
	m_TextureRevolverIcon = TextureHolder::GetTexture("graphics/revolver_pickup_icon.png");
	m_SpriteRevolverIcon.setTexture(m_TextureRevolverIcon);
	m_SpriteRevolverIcon.setPosition(850, 980);

	// Load the font
	m_Font.loadFromFile("fonts/zombiecontrol.ttf");

	// Paused
	m_PausedText.setFont(m_Font);
	m_PausedText.setCharacterSize(155);
	m_PausedText.setFillColor(Color::White);
	m_PausedText.setPosition(400, 400);
	m_PausedText.setString("Press Enter \nto continue");

	// Game Over
	m_GameOverText.setFont(m_Font);
	m_GameOverText.setCharacterSize(125);
	m_GameOverText.setFillColor(Color::White);
	m_GameOverText.setPosition(250, 850);
	m_GameOverText.setString("Press Enter to play");

	// Levelling up
	m_LevelUpText.setFont(m_Font);
	m_LevelUpText.setCharacterSize(80);
	m_LevelUpText.setFillColor(Color::White);
	m_LevelUpText.setPosition(150, 250);
	m_LevelUpStream <<
		"Choose your Upgrade!" <<
		"\n1- Increased rate of fire" <<
		"\n2- Increased clip size(next reload)" <<
		"\n3- Increased max health" <<
		"\n4- Increased run speed" <<
		"\n5- More and better health pickups" <<
		"\n6- More and better ammo pickups" <<
		"\n7- Increased wall piercing revolver duration";
	m_LevelUpText.setString(m_LevelUpStream.str());

	// Ammo
	m_AmmoText.setFont(m_Font);
	m_AmmoText.setCharacterSize(55);
	m_AmmoText.setFillColor(Color::White);
	m_AmmoText.setPosition(200, 980);

	// Score
	m_ScoreText.setFont(m_Font);
	m_ScoreText.setCharacterSize(55);
	m_ScoreText.setFillColor(Color::White);
	m_ScoreText.setPosition(20, 0);

	// Load the high score from a text file/
	std::ifstream inputFile("gamedata/scores.txt");
	if (inputFile.is_open())
	{
		inputFile >> m_HiScore;
		inputFile.close();
	}

	// Hi Score
	m_HiScoreText.setFont(m_Font);
	m_HiScoreText.setCharacterSize(55);
	m_HiScoreText.setFillColor(Color::White);
	m_HiScoreText.setPosition(1400, 0);
	m_S << "Hi Score:" << m_HiScore;
	m_HiScoreText.setString(m_S.str());

	// Zombies remaining
	m_ZombiesRemainingText.setFont(m_Font);
	m_ZombiesRemainingText.setCharacterSize(55);
	m_ZombiesRemainingText.setFillColor(Color::White);
	m_ZombiesRemainingText.setPosition(1500, 980);
	m_ZombiesRemainingText.setString("Zombies: 100");

	m_WaveNumberText.setFont(m_Font);
	m_WaveNumberText.setCharacterSize(55);
	m_WaveNumberText.setFillColor(Color::White);
	m_WaveNumberText.setPosition(1250, 980);
	m_WaveNumberText.setString("Wave: 0");

	// revolver pickup - wall piercing
	m_RevolverPickupText.setFont(m_Font);
	m_RevolverPickupText.setCharacterSize(55);
	m_RevolverPickupText.setFillColor(Color::White);
	m_RevolverPickupText.setPosition(900, 980);
	m_RevolverPickupText.setString(":");

	// Health bar
	m_HealthBar.setFillColor(Color::Red);
	m_HealthBar.setPosition(450, 980);

	// How often (in frames) should we update the HUD
	m_fpsMeasurementFrameInterval = 1000;


	/***** Sound *****/

	// Prepare the hit sound
	m_HitBuffer.loadFromFile("sound/hit.wav");
	m_Hit.setBuffer(m_HitBuffer);

	// Prepare the splat sound
	m_SplatBuffer.loadFromFile("sound/splat.wav");
	m_Splat.setBuffer(m_SplatBuffer);

	// Prepare the shoot sound
	m_ShootBuffer.loadFromFile("sound/shoot.wav");
	m_Shoot.setBuffer(m_ShootBuffer);

	// Prepare the reload sound
	m_ReloadBuffer.loadFromFile("sound/reload.wav");
	m_Reload.setBuffer(m_ReloadBuffer);

	// Prepare the failed sound
	m_ReloadFailedBuffer.loadFromFile("sound/reload_failed.wav");
	m_ReloadFailed.setBuffer(m_ReloadFailedBuffer);

	// Prepare the powerup sound
	m_PowerupBuffer.loadFromFile("sound/powerup.wav");
	m_Powerup.setBuffer(m_PowerupBuffer);

	// Prepare the pickup sound
	m_PickupBuffer.loadFromFile("sound/pickup.wav");
	m_Pickup.setBuffer(m_PickupBuffer);

	// Prepare the nuke sound
	m_NukeBuffer.loadFromFile("sound/nuke.wav"); // made on the bfxr website - https://www.bfxr.net/
	m_Nuke.setBuffer(m_NukeBuffer);

	// Prepare the nuke sound
	m_RevolverBuffer.loadFromFile("sound/revolver_shoot.wav"); // made on the bfxr website - https://www.bfxr.net/
	m_RevolverShoot.setBuffer(m_RevolverBuffer);

}

void GameManager::play()
{
	// Initialise all game variables, prepare text, and load files, and sounds
	init();

	// The main game loop
	while (m_Window.isOpen())
	{
		handleInput();

		/*
		****************
		UPDATE THE FRAME
		****************
		*/
		update();

		// Draw the scene
		draw();

	}// End game loop
}

void GameManager::handleInput()
{
	// Handle events
	Event event;
	while (m_Window.pollEvent(event))
	{
		if (event.type == Event::KeyPressed)
		{
			// Pause a game while playing
			if (event.key.code == Keyboard::Return &&
				m_State == State::PLAYING)
			{
				m_State = State::PAUSED;
			}

			// Restart while paused
			else if (event.key.code == Keyboard::Return &&
				m_State == State::PAUSED)
			{
				m_State = State::PLAYING;
				// Reset the clock so there isn't a frame jump
				m_Clock.restart();
			}

			// Start a new game while in GAME_OVER state
			else if (event.key.code == Keyboard::Return &&
				m_State == State::GAME_OVER)
			{
				m_State = State::LEVELING_UP;
				m_Wave = 0;
				m_Score = 0;

				// resets the revolver at the start of each round
				m_RevolverPickupActive = false;
				m_RevolverPickupTimer = 0;

				// resets the arena size
				m_Arena.width = m_StartingArenaWidth;
				m_Arena.height = m_StartingArenaHeight;

				// Prepare the gun and ammo for next game
				m_CurrentBullet = 0;
				m_BulletsSpare = 30;
				m_BulletsInClip = 10;
				m_ClipSize = 10;
				m_FireRate = 1;


				// Reset the player's stats
				pPlayer->resetPlayerStats();
			}

			if (m_State == State::PLAYING)
			{
				// Reloading
				if (event.key.code == Keyboard::R)
				{
					if (m_BulletsSpare >= m_ClipSize)
					{
						// Plenty of bullets. Reload.
						m_BulletsInClip = m_ClipSize;
						m_BulletsSpare -= m_ClipSize;
						m_Reload.play();
					}
					else if (m_BulletsSpare > 0)
					{
						// Only few bullets left
						m_BulletsInClip = m_BulletsSpare;
						m_BulletsSpare = 0;
						m_Reload.play();
					}
					else
					{
						// More here soon?!
						m_ReloadFailed.play();
					}
				}
			}

		}
	}// End event polling


	 // Handle the player quitting
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		m_Window.close();
	}

	// Handle controls while playing
	if (m_State == State::PLAYING)
	{
		// Handle the pressing and releasing of the WASD keys
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			pPlayer->moveUp();
		}
		else
		{
			pPlayer->stopUp();
		}

		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			pPlayer->moveDown();
		}
		else
		{
			pPlayer->stopDown();
		}

		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			pPlayer->moveLeft();
		}
		else
		{
			pPlayer->stopLeft();
		}

		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			pPlayer->moveRight();
		}
		else
		{
			pPlayer->stopRight();
		}

		// Fire a bullet
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{

			if (m_GameTimeTotal.asMilliseconds()
				- m_LastPressed.asMilliseconds()
					> 1000 / m_FireRate && m_BulletsInClip > 0)
			{
				// if revolver is active, the wall piercing variable in bullets in set to true
				if (m_RevolverPickupActive)
				{
					m_Bullets[m_CurrentBullet].setWallPiercing(true);
				}
				else
				{
					m_Bullets[m_CurrentBullet].setWallPiercing(false);
				}
				// once bullets' stop function is called, wallPiercing is also reset to false

				// Pass the centre of the player and the centre of the crosshair
				// to the shoot function
				m_Bullets[m_CurrentBullet].shoot(
					pPlayer->getCenter().x, pPlayer->getCenter().y,
					m_MouseWorldPosition.x, m_MouseWorldPosition.y);

				m_CurrentBullet++;
				if (m_CurrentBullet > 99)
				{
					m_CurrentBullet = 0;
				}
				m_LastPressed = m_GameTimeTotal;

				// play the revolver shoot sound if revolver is active, otherwise play the normal shoot sound
				if (m_RevolverPickupActive)
				{
					m_RevolverShoot.play();
				}
				else
				{
					m_Shoot.play();
				}
				
				m_BulletsInClip--;
			}

		}// End fire a bullet

	}// End WASD while playing

	// Handle the levelling up state
	if (m_State == State::LEVELING_UP)
	{
		// Handle the player levelling up
		if (event.key.code == Keyboard::Num1)
		{
			// Increase fire rate
			m_FireRate += (rand() % 2) + 1;
			m_State = State::PLAYING;
		}

		if (event.key.code == Keyboard::Num2)
		{
			// Increase clip size
			m_ClipSize += m_ClipSize;
			m_State = State::PLAYING;
		}

		if (event.key.code == Keyboard::Num3)
		{
			// Increase health
			pPlayer->upgradeHealth();
			m_State = State::PLAYING;
		}

		if (event.key.code == Keyboard::Num4)
		{
			// Increase speed
			pPlayer->upgradeSpeed();
			m_State = State::PLAYING;
		}

		if (event.key.code == Keyboard::Num5)
		{
			pHealthPickup->upgrade();
			m_State = State::PLAYING;
		}

		if (event.key.code == Keyboard::Num6)
		{
			pAmmoPickup->upgrade();
			m_State = State::PLAYING;
		}

		// increase the active time of the revolver pickup by 5 seconds and how long the pickup stays on the ground
		if (event.key.code == Keyboard::Num7)
		{
			pRevolverPickup->upgrade();
			m_State = State::PLAYING;
		}

		if (m_State == State::PLAYING)
		{
			// Increase the wave number
			m_Wave++;

			// resets the revolver at the start of each round
			m_RevolverPickupActive = false;
			m_RevolverPickupTimer = 0;
			
			// Prepare the level
			// We will modify the next two lines later
			m_Arena.width = m_StartingArenaWidth * m_Wave;
			m_Arena.height = m_StartingArenaHeight * m_Wave;
			m_Arena.left = 0;
			m_Arena.top = 0;

			int previousWorldWidth = 0;;
			if (m_Wave == 1)
			{
				previousWorldWidth = m_StartingArenaWidth/m_TileSize;
			}
			else
			{
				previousWorldWidth = (m_StartingArenaWidth * (m_Wave-1))/m_TileSize;
			}

			if (m_Wave > 1)
			{
				// Deletes the memory that each pointer within m_GridTileType points to and the grid of pointers itself to prevent memory
				if (m_GridTileType != nullptr)
				{
					for (int i = 0; i < previousWorldWidth; ++i)
					{
						delete[] m_GridTileType[i];
					}
					delete[] m_GridTileType;
					m_GridTileType = nullptr;
				}
			}
			
			m_WorldWidth = m_Arena.width / m_TileSize;
			m_WorldHeight = m_Arena.height / m_TileSize;

			// Pass the vertex array by reference to the createBackground function
			m_TileSize = createBackground(m_Background, m_Arena, m_GridTileType, m_WorldWidth, m_WorldHeight);
			//cout << gridTileType[8][5].toAnsiString();

			// Spawn the player in the middle of the arena
			pPlayer->spawn(m_Arena, m_Resolution, m_TileSize, m_GridTileType, m_WorldWidth);

			// Configure the pick-ups
			pHealthPickup->setArena(m_Arena); // also calls the spawn function
			pAmmoPickup->setArena(m_Arena);
			pNukePickup->setArena(m_Arena);
			pRevolverPickup->setArena(m_Arena);
			pHealthPickup->spawn();
			pAmmoPickup->spawn();
			pNukePickup->spawn();
			pRevolverPickup->spawn();

			// make a list of pickup and add these to it so other pickups can be added to the list later

			// Create a horde of zombies
			m_NumZombies = ((rand() % 6) + 5) * m_Wave;
			//m_NumZombies = 1; // for testing movement and collision detection

			// Delete the previously allocated memory (if it exists) - uses the pZombies iter defined at the top
			// this part could go in a clean method in a game manager
			for (vpZombiesIter = vpZombies.begin(); vpZombiesIter != vpZombies.end(); ++vpZombiesIter)
			{
				delete* vpZombiesIter;
			}
			vpZombies.clear();
			vpZombies = createHorde(m_NumZombies, m_TileSize, m_Arena, m_GridTileType, m_WorldWidth);
			m_NumZombiesAlive = m_NumZombies;

			// Play the powerup sound
			m_Powerup.play();

			// Reset the clock so there isn't a frame jump
			m_Clock.restart();
		}
	}// End levelling up
}

void GameManager::update()
{
	if (m_State == State::PLAYING)
	{
		// Update the delta time
		Time dt = m_Clock.restart();
		// Update the total game time
		m_GameTimeTotal += dt;

		//Powerup Timer
		m_RevolverPickupTimer -= dt.asSeconds();
		// Make a decimal fraction of 1 from the delta time
		float dtAsSeconds = dt.asSeconds();

		// Where is the mouse pointer
		m_MouseScreenPosition = Mouse::getPosition();

		// Convert mouse position to world coordinates of mainView
		m_MouseWorldPosition = m_Window.mapPixelToCoords(
			Mouse::getPosition(), m_MainView);

		// Set the crosshair to the mouse world location
		m_SpriteCrosshair.setPosition(m_MouseWorldPosition);

		// Update the player
		pPlayer->update(dtAsSeconds, Mouse::getPosition());

		// Make a note of the players new position
		Vector2f playerPosition(pPlayer->getCenter());

		// Make the view centre around the player				
		m_MainView.setCenter(pPlayer->getCenter());


		// Loop through each Zombie and update them
		for (vpZombiesIter = vpZombies.begin(); vpZombiesIter != vpZombies.end(); ++vpZombiesIter)
		{
			if ((*vpZombiesIter)->isAlive())
			{
				(*vpZombiesIter)->update(dt.asSeconds(), playerPosition);
			}
		}

		// Update any bullets that are in-flight
		for (int i = 0; i < 100; i++)
		{
			if (m_Bullets[i].isInFlight())
			{
				m_Bullets[i].update(dtAsSeconds, m_GridTileType, m_WorldWidth);
			}
		}

		// Update the pickups
		pHealthPickup->update(dtAsSeconds);
		pAmmoPickup->update(dtAsSeconds);
		pNukePickup->update(dtAsSeconds);
		pRevolverPickup->update(dtAsSeconds);

		// Collision detection
		// Have any zombies been shot?
		for (int i = 0; i < 100; i++)
		{
			for (vpZombiesIter = vpZombies.begin(); vpZombiesIter != vpZombies.end(); ++vpZombiesIter)
			{
				/*
				// while one hit kill revolver is active
				if (m_RevolverPickupActive && vpZombies[j].isAlive())
				{
					while (vpZombies[j].isAlive())
					{
						vpZombies[j].hit();
					}
					m_NumZombiesAlive--;
					// When all the zombies are dead (again)
					if (m_NumZombiesAlive == 0) {
						m_State = State::LEVELING_UP;
					}
				}
				*/

				if (m_Bullets[i].isInFlight() &&
					(*vpZombiesIter)->isAlive())
				{
					int powerupNum = 0;
					// normal gun
					if (m_Bullets[i].getPosition().intersects
					((*vpZombiesIter)->getPosition()) && !m_RevolverPickupActive)
					{
						// Stop the bullet
						m_Bullets[i].stop();

						// Register the hit and see if it was a kill
						if ((*vpZombiesIter)->hit()) {
							// Not just a hit but a kill too
							m_Score += 10;
							if (m_Score >= m_HiScore)
							{
								m_HiScore = m_Score;
							}

							// add code for random powerup drop here

							// percentage chance to spawn the nuke 
							powerupNum = (rand() % 100) + 1;
							if (powerupNum >= 80)
							{
								pNukePickup->setPosition((*vpZombiesIter)->getCenter().x, (*vpZombiesIter)->getCenter().y);
							}

							if (powerupNum <= 30)
							{
								pRevolverPickup->setPosition((*vpZombiesIter)->getCenter().x, (*vpZombiesIter)->getCenter().y);
							}

							m_NumZombiesAlive--;

							// When all the zombies are dead (again)
							if (m_NumZombiesAlive == 0) {
								m_State = State::LEVELING_UP;
							}
						}

						// Make a splat sound
						m_Splat.play();

					}

					// if the revolver is active
					if (m_Bullets[i].getPosition().intersects
					((*vpZombiesIter)->getPosition()) && m_RevolverPickupActive)
					{
						// Stop the bullet
						m_Bullets[i].stop();

						while((*vpZombiesIter)->isAlive())
						{
							(*vpZombiesIter)->hit();
						}
						
						m_Score += 10;
						if (m_Score >= m_HiScore)
						{
							m_HiScore = m_Score;
						}

						// percentage chance to spawn the nuke 
						powerupNum = (rand() % 100) + 1;
						if (powerupNum >= 80) // 20%
						{
							pNukePickup->setPosition((*vpZombiesIter)->getCenter().x, (*vpZombiesIter)->getCenter().y);
						}

						if (powerupNum <= 30) // 30%
						{
							pRevolverPickup->setPosition((*vpZombiesIter)->getCenter().x, (*vpZombiesIter)->getCenter().y);
						}

						m_NumZombiesAlive--;

						// When all the zombies are dead (again)
						if (m_NumZombiesAlive == 0) {
							m_State = State::LEVELING_UP;
						}
						
						// Make a splat sound
						m_Splat.play();

					}
				}

			}
		}// End zombie being shot


		// Have any zombies touched the player			
		for (vpZombiesIter = vpZombies.begin(); vpZombiesIter != vpZombies.end(); ++vpZombiesIter)
		{
			if (pPlayer->getPosition().intersects
			((*vpZombiesIter)->getPosition()) && (*vpZombiesIter)->isAlive())
			{

				if (pPlayer->hit(m_GameTimeTotal))
				{
					// More here later
					m_Hit.play();
				}

				if (pPlayer->getHealth() <= 0)
				{
					m_State = State::GAME_OVER;

					std::ofstream outputFile("gamedata/scores.txt");
					outputFile << m_HiScore;
					outputFile.close();

				}
			}
		}// End player touched

		// Has the player touched health pickup
		if (pPlayer->getPosition().intersects
		(pHealthPickup->getPosition()) && pHealthPickup->isSpawned())
		{
			pPlayer->increaseHealthLevel(pHealthPickup->getValue());
			pHealthPickup->gotIt();
			// Play a sound
			m_Pickup.play();

		}

		// Has the player touched ammo pickup
		if (pPlayer->getPosition().intersects
		(pAmmoPickup->getPosition()) && pAmmoPickup->isSpawned())
		{
			m_BulletsSpare += pAmmoPickup->getValue();
			pAmmoPickup->gotIt();
			// Play a sound
			m_Reload.play();

		}


		// Has the player touched a nuke powerup
		/******************* make a game engine ******************/
		if (pPlayer->getPosition().intersects
		(pNukePickup->getPosition()) && pNukePickup->isSpawned())
		{
			//nukeActive = true;
			//zombiesToKill = nukePickup->getValue();
			pNukePickup->gotIt();
			// Play a sound
			m_Nuke.play();

			//for (int i = 0; i < numZombies; i++)
			for (vpZombiesIter = vpZombies.begin(); vpZombiesIter != vpZombies.end(); ++vpZombiesIter)
			{
				// ensures the nuke only targets zombies that are still alive
				if ((*vpZombiesIter)->isAlive()) // if the zombie is alive
				{
					while ((*vpZombiesIter)->isAlive())
					{
						(*vpZombiesIter)->hit();
					}
					m_NumZombiesAlive--;
				}
				// When all the zombies are dead (again)
				if (m_NumZombiesAlive == 0) {
					m_State = State::LEVELING_UP;
				}
			}
		}


		// has the player hit the revolver pickup
		if (pPlayer->getPosition().intersects
		(pRevolverPickup->getPosition()) && pRevolverPickup->isSpawned())
		{
			pRevolverPickup->gotIt();
			m_RevolverPickupTimer = pRevolverPickup->getValue();
			m_RevolverPickupActive = true;
			/*
			// makes all bullets go through walls
			for (int i = 0; i < 100; i++)
			{
				m_Bullets[i].setWallPiercing(true);
			}
			*/
			m_Pickup.play();
		}

		if (m_RevolverPickupTimer <= 0)
		{
			m_RevolverPickupActive = false;
			/*
			// makes all bullets stop going through walls
			for (int i = 0; i < 100; i++)
			{
				m_Bullets[i].setWallPiercing(false);
			}
			*/
		}



		// size up the health bar
		m_HealthBar.setSize(Vector2f(pPlayer->getHealth() * 3, 70));

		// Increment the amount of time since the last HUD update
		m_TimeSinceLastUpdate += dt;
		// Increment the number of frames since the last HUD calculation
		m_FramesSinceLastHUDUpdate++;
		// Calculate FPS every fpsMeasurementFrameInterval frames
		if (m_FramesSinceLastHUDUpdate > m_fpsMeasurementFrameInterval)
		{

			// Update game HUD text
			std::stringstream ssAmmo;
			std::stringstream ssScore;
			std::stringstream ssHiScore;
			std::stringstream ssWave;
			std::stringstream ssZombiesAlive;
			std::stringstream ssRevolverActive;

			// Update the ammo text
			ssAmmo << m_BulletsInClip << "/" << m_BulletsSpare;
			m_AmmoText.setString(ssAmmo.str());

			// Update the score text
			ssScore << "Score:" << m_Score;
			m_ScoreText.setString(ssScore.str());

			// Update the high score text
			ssHiScore << "Hi Score:" << m_HiScore;
			m_HiScoreText.setString(ssHiScore.str());

			// Update the wave
			ssWave << "Wave:" << m_Wave;
			m_WaveNumberText.setString(ssWave.str());

			// Update the high score text
			ssZombiesAlive << "Zombies:" << m_NumZombiesAlive;
			m_ZombiesRemainingText.setString(ssZombiesAlive.str());

			// Update the revolver active icon and text
			ssRevolverActive << "Revolver: " << int(m_RevolverPickupTimer + 1.0f);
			m_RevolverPickupText.setString(ssRevolverActive.str());

			m_FramesSinceLastHUDUpdate = 0;
			m_TimeSinceLastUpdate = Time::Zero;
		}// End HUD update

	}// End updating the scene
}

void GameManager::draw()
{
	if (m_State == State::PLAYING)
	{
		m_Window.clear();

		// set the mainView to be displayed in the window
		// And draw everything related to it
		m_Window.setView(m_MainView);

		// Draw the background
		m_Window.draw(m_Background, &m_TextureBackground);



		// Draw the dead zombies
		for (vpZombiesIter = vpZombies.begin(); vpZombiesIter != vpZombies.end(); ++vpZombiesIter)
		{
			if (!(*vpZombiesIter)->isAlive())
			{
				m_Window.draw((*vpZombiesIter)->getSprite());
			}
		}

		// Draw the walking dead zombies
		for (vpZombiesIter = vpZombies.begin(); vpZombiesIter != vpZombies.end(); ++vpZombiesIter)
		{
			if ((*vpZombiesIter)->isAlive())
			{
				m_Window.draw((*vpZombiesIter)->getSprite());
			}
		}

		for (int i = 0; i < 100; i++)
		{
			if (m_Bullets[i].isInFlight())
			{
				m_Window.draw(m_Bullets[i].getShape());
			}
		}

		// Draw the player
		m_Window.draw(pPlayer->getSprite());

		// Draw the pickups is currently spawned
		if (pAmmoPickup->isSpawned())
		{
			m_Window.draw(pAmmoPickup->getSprite());
		}
		if (pHealthPickup->isSpawned())
		{
			m_Window.draw(pHealthPickup->getSprite());
		}

		if (pNukePickup->isSpawned())
		{
			m_Window.draw(pNukePickup->getSprite());
		}

		if (pRevolverPickup->isSpawned())
		{
			m_Window.draw(pRevolverPickup->getSprite());
		}

		//Draw the crosshair
		m_Window.draw(m_SpriteCrosshair);

		// Switch to the HUD view
		m_Window.setView(hudView);

		// Draw all the HUD elements
		m_Window.draw(m_SpriteAmmoIcon);
		m_Window.draw(m_AmmoText);
		m_Window.draw(m_ScoreText);
		m_Window.draw(m_HiScoreText);
		m_Window.draw(m_HealthBar);
		m_Window.draw(m_WaveNumberText);
		m_Window.draw(m_ZombiesRemainingText);

		if (m_RevolverPickupActive)
		{
			m_Window.draw(m_RevolverPickupText);
			m_Window.draw(m_SpriteRevolverIcon);
		}
	}

	if (m_State == State::LEVELING_UP)
	{
		m_Window.draw(m_SpriteGameOver);
		m_Window.draw(m_LevelUpText);
	}

	if (m_State == State::PAUSED)
	{
		m_Window.draw(m_PausedText);
	}

	if (m_State == State::GAME_OVER)
	{
		m_Window.draw(m_SpriteGameOver);
		m_Window.draw(m_GameOverText);
		m_Window.draw(m_ScoreText);
		m_Window.draw(m_HiScoreText);
	}

	m_Window.display();
}