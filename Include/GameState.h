#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <Include/State.h>
#include <Include/Button.h>
#include <Include/MovementComponent.h>
#include <Include/AttributeComponent.h>
#include <Include/Dungeon.h>
#include <Include/Camera.h>
#include <Include/Minimap.h>
#include <Include/Triangle.h>
#include <Include/Player.h>
#include <Include/Enemy.h>

class GameState : public State
{
private:
	Player		player;
	Enemy		enemy;
	Dungeon		dungeon;
	Camera		mainCamera;
	Camera		secondCamera;
	Camera		thirdCamera;
	Minimap		minimap;
	//Button	button;
	sf::Font	font;
	sf::Text	tips;

	void initKeybinds();
	void initPlayer();
	void initEnemies();
	void initDungeon();
	void initCameras();
	void initMinimap();
	void initTexts();
public:
	GameState(sf::RenderWindow* window, std::map<std::string,
		int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();

	void updateInput(const float& dt) override;
	void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
};

#include <Source/GameState.cpp>
#endif
