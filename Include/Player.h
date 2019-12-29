#ifndef PLAYER_H
#define PLAYER_H

class Player : public Triangle
{
private:
	MovementComponent movementComponent;
	
	sf::Vector2i* mousePosition;
	sf::Vector2f* mousePosition2;
	sf::Vector2f lookDir;

	void initMovementComponent();
	void initAttributeComponent();
public:
 	Player();
 	virtual ~Player();

 	//Until I completely complete the work on the player’s movement system, it will be here
 	bool intersectsWall;

 	//This is for the future
	AttributeComponent attributeComponent;

 	void setMousePosition(sf::Vector2i* mousePosition);
 	void setMousePosition2(sf::Vector2f* mousePosition);
	void move(const float dir_x, const float dir_y, const float& dt);
	void move(const float offsetX, const float offsetY);
	void resetVelocity();

	void update(const float& dt) override;
	void render(sf::RenderTarget* target = NULL) override;
};

#include <Source/Player.cpp>
#endif
