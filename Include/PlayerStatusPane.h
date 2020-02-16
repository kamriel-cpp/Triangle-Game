#ifndef PLAYERSTATUSPANE
#define PLAYERSTATUSPANE
#include <Include/ProgressBar.h>

class PlayerStatusPane
{
private:
	sf::Font*						font;
	sf::View*&						view;

	Player*							player;

	sf::Text						lvlInfo;
	sf::Text						apsInfo;

	ProgressBar*					hpBar;
	ProgressBar*					reloadBar;
	ProgressBar*					expBar;
private:
	void initTexts();
	void initProgressBars();
public:
	PlayerStatusPane(sf::Font* font, sf::View* view, Player* player);
	virtual ~PlayerStatusPane();

	void update();
	void render(sf::RenderTarget* target = nullptr);
};

#include <Source/PlayerStatusPane.cpp>
#endif
