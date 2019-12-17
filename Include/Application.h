#ifndef APPLICATION_H
#define APPLICATION_H
#include <iostream>
#include <ctime>
#include <list>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Include/Dungeon.h>
#include <Include/Camera.h>

class Application
{
private:
	sf::RenderWindow*			window;
	sf::Event					event;
	std::vector<sf::VideoMode>	videoModes;
	sf::ContextSettings			windowSettings;
	bool						fullscreen;
	sf::Clock					dtClock;
	float						dt;

	sf::Font					font;
	sf::Text					tips;
	Dungeon						dungeon;
	Camera						mainCamera;
	Camera						secondaryCamera;

	void initVariables();
	void initWindow();
	void initDungeon();
	void initText();
	void initMainCamera();
	void initSecondaryCamera();
public:
	Application();
	Application(Application&) = delete;
	Application(Application&&) = delete;
	virtual ~Application();

	void endApplication();
	void updateDt();
	void updateEvents();
	void updateInput();
	void update(); 
	void render();
	void run();
};

#include <Source/Application.cpp>
#endif