#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <Include/State.h>
#include <Include/Button.h>
#include <Include/MovementComponent.h>
#include <Include/AttributeComponent.h>
#include <Include/Room.h>
#include <Include/Floor.h>
#include <Include/Triangle.h>
#include <Include/Player.h>
#include <Include/Enemy.h>
#include <Include/Camera.h>
#include <Include/Cinemachine.h>
#include <Include/Minimap.h>
#include <Include/FPSCounter.h>
#include <Include/WaveSpawner.h>

class GameState : public State
{
private:
	sf::Font				font;
	std::list<sf::Text*>	texts;
	Floor					floor;
	sf::Text*				floorText;
	Player*					player;
	std::list<Enemy*>		enemies;
	Camera*					mainCamera;
	Camera*					uiCamera;
	Cinemachine*			cinemachine;
	Minimap*				minimap;
	sf::Clock 				gameClock;
	FPSCounter*				fpscounter;
	WaveSpawner*			waveSpawner;

	bool wasPressedLeft;
	bool wasPressedRight;

	void initKeybinds();
	void initTexts();
	void initFloor();
	void initPlayer();
	void initEnemies();
	void initCameras();
	void initCinemachine();
	void initMinimap();
	void initFPSCounter();
	void initWaveSpawner();
public:
	GameState(sf::RenderWindow* window, std::map<std::string,
		int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();

	void updateInput(const float& dt) override;
	void updatePlayerInput(const float& dt);
	void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
};

#include <Source/GameState.cpp>
#endif
