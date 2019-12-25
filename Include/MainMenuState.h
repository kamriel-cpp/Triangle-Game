#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H
#include <Include/State.h>
#include <Include/Button.h>

class MainMenuState : public State
{
private:
	sf::RectangleShape				background;
	sf::Font						font;
	std::map<std::string, Button*>	buttons;

	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initButtons();
public:
	MainMenuState(sf::RenderWindow* window, std::map<std::string,
				  int>* supportedKeys, std::stack<State*>* states);
	virtual ~MainMenuState();

	void endState();
	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget* target = NULL);
	void render(sf::RenderTarget* target = NULL);
};

#include <Source/MainMenuState.cpp>
#endif
