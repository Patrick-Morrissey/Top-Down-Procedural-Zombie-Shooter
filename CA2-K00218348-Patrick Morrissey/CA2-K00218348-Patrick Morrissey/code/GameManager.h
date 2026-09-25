#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <sstream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ZombieArena.h"
#include "Player.h"
#include "TextureHolder.h"
#include "Bullet.h"
#include "Pickup.h"
#include "StatPickup.h"
#include "ActionPickup.h"
#include "HealthPickup.h"
#include "AmmoPickup.h"
#include "NukePickup.h"
#include "RevolverPickup.h"
#include <cstdlib>

using namespace sf;

class GameManager
{
public:
	GameManager();
	void init();
	void handleInput();
	void update();
	void draw();
	void play();


private:

	// Create an instance of the Player class
	Player* pPlayer;


	// Here is the instance of TextureHolder
	TextureHolder m_Holder;

	// The game will always be in one of four states
	enum class State { PAUSED, LEVELING_UP, GAME_OVER, PLAYING };

	State m_State;

	// Get the screen resolution and create an SFML window
	Vector2f m_Resolution;

	RenderWindow m_Window;

	View m_MainView;

	// Here is our clock for timing everything
	Clock m_Clock;
	// How long has the PLAYING state been active
	Time m_GameTimeTotal;

	// Where is the mouse in relation to world coordinates
	Vector2f m_MouseWorldPosition;
	// Where is the mouse in relation to screen coordinates
	Vector2i m_MouseScreenPosition;

	// The boundaries of the arena
	IntRect m_Arena;

	// Create the background
	VertexArray m_Background;

	Texture m_TextureBackground;

	// A 2d array as a pointer to a pointer for holding the type of tile (wall or floor) is located at each grid position
	String** m_GridTileType;

	int m_TileSize = 50;
	int m_WorldWidth = 0;
	int m_WorldHeight = 0;

	// Prepare for a horde of zombies
	int m_NumZombies;
	int m_NumZombiesAlive;
	//Zombie* zombies = NULL; // pointer to an array of zombies
	// vector of pointers to zombies
	vector<Zombie*>vpZombies;
	vector<Zombie*>::iterator vpZombiesIter;

	// 100 bullets should do
	Bullet m_Bullets[100];
	int m_CurrentBullet = 0;
	int m_BulletsSpare;
	int m_BulletsInClip;
	int m_ClipSize;
	float m_FireRate;
	// When was the fire button last pressed?
	Time m_LastPressed;

	// crosshair sprite and texture
	Sprite m_SpriteCrosshair;
	Texture m_TextureCrosshair;

	// Create a couple of pickups
	Pickup* pHealthPickup;
	Pickup* pAmmoPickup;
	Pickup* pNukePickup;
	Pickup* pRevolverPickup;
	//list<Pickup*> lpPickups; // list for adding pickups to

	float m_RevolverPickupTimer = 0.0f;
	bool m_RevolverPickupActive = false;

	// About the game
	int m_Score;
	int m_HiScore;
	float m_StartingArenaWidth;
	float m_StartingArenaHeight;

	// For the home/game over screen
	Sprite m_SpriteGameOver;
	Texture m_TextureGameOver;

	// Create a view for the HUD
	View hudView;

	// Create a sprite for the ammo icon
	Sprite m_SpriteAmmoIcon;
	Texture m_TextureAmmoIcon;

	// Create a sprite for the revolver pickup
	Sprite m_SpriteRevolverIcon;
	Texture m_TextureRevolverIcon;

	Font m_Font;

	// Paused
	Text m_PausedText;

	// Game Over
	Text m_GameOverText;

	// Levelling up
	Text m_LevelUpText;
	std::stringstream m_LevelUpStream;

	// Ammo
	Text m_AmmoText;

	// Score
	Text m_ScoreText;

	// Hi Score
	Text m_HiScoreText;
	std::stringstream m_S;

	// Zombies remaining
	Text m_ZombiesRemainingText;

	// Wave number
	int m_Wave = 0;
	Text m_WaveNumberText;

	Text m_RevolverPickupText;

	// Health bar
	RectangleShape m_HealthBar;

	// When did we last update the HUD?
	int m_FramesSinceLastHUDUpdate = 0;
	// What time was the last update
	Time m_TimeSinceLastUpdate;
	// How often (in frames) should we update the HUD
	int m_fpsMeasurementFrameInterval;

	/***** Sound *****/

	// Prepare the hit sound
	SoundBuffer m_HitBuffer;
	Sound m_Hit;

	// Prepare the splat sound
	SoundBuffer m_SplatBuffer;
	sf::Sound m_Splat;

	// Prepare the shoot sound
	SoundBuffer m_ShootBuffer;
	Sound m_Shoot;

	// Prepare the reload sound
	SoundBuffer m_ReloadBuffer;
	Sound m_Reload;

	// Prepare the failed sound
	SoundBuffer m_ReloadFailedBuffer;
	Sound m_ReloadFailed;

	// Prepare the powerup sound
	SoundBuffer m_PowerupBuffer;
	Sound m_Powerup;

	// Prepare the pickup sound
	SoundBuffer m_PickupBuffer;
	Sound m_Pickup;

	// Prepare the nuke sound
	SoundBuffer m_NukeBuffer;
	Sound m_Nuke;

	// Prepare the revolver shoot sound
	SoundBuffer m_RevolverBuffer;
	Sound m_RevolverShoot;

};
#endif
