#ifndef PLAYER_H
#define PLAYER_H

class Player : public Triangle
{
private:
	void initVariables();
	void initComponents();
public:
 	Player(const sf::Vector2f& position);
 	virtual ~Player();

	bool isDashing;

	void update(const float& dt, const sf::Vector2f& target_position) override;
	void render(sf::RenderTarget* target = NULL) override;
};

#include <Source/Player.cpp>
#endif
