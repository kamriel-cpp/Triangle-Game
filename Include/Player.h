#ifndef PLAYER_H
#define PLAYER_H

class Player : public Triangle
{
private:
	MovementComponent movementComponent;
	
	sf::Vector2i* mousePosition;
	sf::Vector2f* mousePosition2;
	sf::Vector2f lookDir;

	sf::RectangleShape frame;

	void initMovementComponent();
	void initAttributeComponent();
public:
 	Player();
 	~Player();

 	bool insideDungeon;
	unsigned char lastMove;
	AttributeComponent attributeComponent;

 	void setMousePosition(sf::Vector2i* mousePosition);
 	void setMousePosition2(sf::Vector2f* mousePosition);
	void move(const float dir_x, const float dir_y, const float& dt);
	void update(const float& dt) override;
	void render(sf::RenderTarget* target = NULL) override;
};

#include <Source/Player.cpp>
#endif
