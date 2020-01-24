#ifndef STATE_H
#define STATE_H

class State
{
protected:
	std::stack<State*>* states;
	sf::RenderWindow* window;

	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	bool quit;
	bool wasPressedLeft;
	bool wasPressedRight;
	bool wasPressedMiddle;

	std::map<std::string, sf::Texture> textures;

	virtual void initKeybinds() = 0;
public:
	State(sf::RenderWindow* window, std::map<std::string,
		  int>* supportedKeys, std::stack<State*>* states);
	virtual ~State();

	const bool& getQuit() const;
	void endState(); 

	virtual void updateMousePositions(const sf::View* view = NULL);
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0; 
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

#include <Source/State.cpp>
#endif
