#pragma once
#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <Include/State.h>
#include <Include/Button.h>
#include <Include/Dungeon.h>
#include <Include/Camera.h>

class GameState : public State
{
private:
	Button		button;
	sf::Font 	font;
	sf::Text 	text;
	Dungeon		dungeon;
	Camera		camera;
	
	void initDungeon();
	void initKeybinds();
	void initPlayer();
	void initText();
	void initCamera();
public:
	GameState(sf::RenderWindow* window, std::map<std::string,
			  int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();

	void endStat(); 
	void updateInput(const float& dt) override;
	void update(const float& dt) override; 
	void render(sf::RenderTarget* target = nullptr) override;
};

#include <Source/GameState.cpp>
#endif
