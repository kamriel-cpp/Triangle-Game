#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include <Include/Button.h>
#include <Include/FPSCounter.h>
#include <Include/Minimap.h>
#include <Include/PlayerStatusPane.h>
#include <Include/PlayerAttributesPane.h>

class UserInterface
{
private:
	sf::Font*						font;
	sf::View*&						view;
	sf::RenderWindow*				window;
	sf::Vector2f*					mousePosView;

	Floor*							floor;
	Player*							player;

	Minimap*						minimap;
	FPSCounter*						fpscounter;	
	PlayerStatusPane*				playerStatusPane;
	PlayerAttributesPane*			playerAttributesPane;
private:
	void initButtons();
	void initMinimap();
	void initFPSCounter();
	void initPlayerStatusPane();
	void initPlayerAttributesPane();
public:
	UserInterface(sf::Font* font, sf::View* view,
		sf::RenderWindow* window, sf::Vector2f* mouse_pos_view,
		Floor* floor, Player* player);
	virtual ~UserInterface();

	void rebuildMinimap();

	void update();
	void render(sf::RenderTarget* target = nullptr);
};

#include <Source/UserInterface.cpp>
#endif
