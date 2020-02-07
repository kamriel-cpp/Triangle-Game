#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <Include/State.h>
#include <Include/MovementComponent.h>
#include <Include/AttributeComponent.h>
#include <Include/ShootComponent.h>
#include <Include/Room.h>
#include <Include/Floor.h>
#include <Include/Player.h>
#include <Include/Enemy.h>
#include <Include/Camera.h>
#include <Include/UserInterface.h>
#include <Include/WaveSpawner.h>
#include <Include/Effect.h>

class GameState : public State
{
private:
	sf::Font				font;
	Floor					floor;
	sf::Text*				floorText;

	std::list<Unit*>		units;

	Player*					player;
	std::list<Enemy*>		enemies;
	std::list<Effect*>		effects;
	std::list<Bullet*>		bullets;
	sf::Clock 				gameClock;
	WaveSpawner*			waveSpawner;

	sf::View*				mainView;
	sf::View*				uiView;
	Camera*					mainCamera;
	UserInterface*			ui;

	bool battleState;
	unsigned int battleRoomIndex;
private:
	void initVariables();
	void initKeybinds();
	void initFont();
	void initFloor();
	void initPlayer();
	void initEnemies();
	void initViews();
	void initCameras();
	void initUI();
	void initWaveSpawner();
public:
	GameState(sf::RenderWindow* window, std::map<std::string,
		int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();

	void applyDamage(const float& amount, Actor* target, Actor* caster = nullptr);

	void updateInput(const float& dt) override;
	void updatePlayerInput(const float& dt);
	void updateCollisionsWithWalls(const float& dt);
	void updateCollisionsWithBullets();
	void updateCombat(const float& dt);
	void updateUnits(const float& dt);
	void updateBullets(const float& dt);
	void updateEffects(const float& dt);
	void updateCameras(const float& dt);
	void updateUI();
	void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
};

#include <Source/GameState.cpp>
#endif
