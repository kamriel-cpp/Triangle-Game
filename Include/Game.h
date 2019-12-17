#pragma once
#ifndef GAME_H
#define GAME_H
#include <Include/Includes.h>
#include <Include/GameState.h>
#include <Include/MainMenuState.h>

class Game
{
private:
	sf::RenderWindow*			window;
	sf::Event					event;
	std::vector<sf::VideoMode>	videoModes;
	sf::ContextSettings			windowSettings;
	bool						fullscreen;
	sf::Clock					dtClock;
	float						dt;
	std::stack<State*>			states;
	std::map<std::string, int>	supportedKeys;

	void initVariables();
	void initWindow();
	void initKeys();
	void initStates();
public:
	Game();
	Game(Game&) = delete;
	Game(Game&&) = delete;
	virtual ~Game();

	void endApplication();
	void updateDt();
	void updateEvents();
	void update(); 
	void render();
	void run();
};

#include <Source/Game.cpp>
#endif