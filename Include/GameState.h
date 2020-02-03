#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <Include/State.h>
#include <Include/Button.h>
#include <Include/MovementComponent.h>
#include <Include/AttributeComponent.h>
#include <Include/ShootComponent.h>
#include <Include/Room.h>
#include <Include/Floor.h>
#include <Include/Player.h>
#include <Include/Enemy.h>
#include <Include/Camera.h>
#include <Include/Minimap.h>
#include <Include/FPSCounter.h>
#include <Include/WaveSpawner.h>
#include <Include/Effect.h>

class GameState : public State
{
private:
	sf::Font				font;
	std::list<sf::Text*>	texts;
	std::map<std::string, Button*>	buttons;
	Floor					floor;
	sf::Text*				floorText;
	Player*					player;
	std::list<Enemy*>		enemies;
	sf::View*				mainView;
	sf::View*				uiView;
	Camera*					mainCamera;
	Minimap*				minimap;
	sf::Clock 				gameClock;
	FPSCounter*				fpscounter;
	WaveSpawner*			waveSpawner;
	std::list<Effect*>		effects;
	std::list<Bullet*>		bullets;

	bool battleState;
	unsigned int battleRoomIndex;
private:
	void initVariables();
	void initKeybinds();
	void initFont();
	void initFloor();
	void initButtons();
	void initPlayer();
	void initEnemies();
	void initViews();
	void initCameras();
	void initMinimap();
	void initFPSCounter();
	void initWaveSpawner();
public:
	GameState(sf::RenderWindow* window, std::map<std::string,
		int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();

	void updateInput(const float& dt) override;
	void updatePlayerInput(const float& dt);
	void updateCollisionsWithWalls(const float& dt);
	void updateCollisionsWithBullets();
	void updateCombat(const float& dt);
	void updateUnits(const float& dt);
	void updateBullets(const float& dt);
	void updateEffects(const float& dt);
	void updateCameras(const float& dt);
	void updateButtons();
	void updateUI(const float& dt);
	void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
};

#include <Source/GameState.cpp>
#endif
