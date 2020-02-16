#ifndef PLAYERATTRIBUTESPANE_H
#define PLAYERATTRIBUTESPANE_H

class PlayerAttributesPane
{
private:
	std::map<std::string, sf::Text*>	statsInfo;
	std::map<std::string, Button*>		buttons;

	sf::Vector2f*						mousePosView;
	Player*								player;
private:
	void initStatsInfo(sf::Font* font, sf::View* view);
	void initButtons(sf::Font* font, sf::View* view);
public:
	PlayerAttributesPane(sf::Font* font, sf::View* view, sf::Vector2f* mouse_pos_view, Player* player);
	virtual ~PlayerAttributesPane();
	
	void updateStatsInfo();
	void updateButtons();
	void update();
	void render(sf::RenderTarget* target = nullptr);
};

#include <Source/PlayerAttributesPane.cpp>
#endif
