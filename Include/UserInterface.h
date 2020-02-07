#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include <Include/Button.h>
#include <Include/FPSCounter.h>
#include <Include/Minimap.h>
#include <Include/StatusBar.h>

class UserInterface
{
private:
	sf::Font*						font;
	std::list<sf::Text*>			texts;
	std::map<std::string, Button*>	buttons;

	Floor*							floor;
	Player*							player;
	sf::RenderWindow*				window;
	Minimap*						minimap;

	sf::View*&						view;

	FPSCounter*						fpscounter;
	sf::Vector2f*					mousePosView;

	StatusBar*						hpBar;
	StatusBar*						reloadBar;
	StatusBar*						expBar;
private:
	void initButtons();
	void initMinimap();
	void initFPSCounter();
	void initStatusBars();
public:
	UserInterface(sf::Font* font,
		Floor* floor, Player* player, sf::RenderWindow* window,
		sf::View* view,
		sf::Vector2f* mouse_pos_view);
	virtual ~UserInterface();

	void rebuildMinimap();

	void updateButtons();
	void update();
	void render(sf::RenderTarget* target = nullptr);
};

#include <Source/UserInterface.cpp>
#endif
