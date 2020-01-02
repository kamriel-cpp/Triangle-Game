#ifndef PLAYER_H
#define PLAYER_H

class Player : public Triangle
{
private:
	MovementComponent* movementComponent;
	AttributeComponent* attributeComponent;
	
	void initVariables();
	void initWallCheckers();
	void initMovementComponent();
	void initAttributeComponent();
public:
 	Player(const sf::Vector2f& position);
 	virtual ~Player();

 	//Until I completely complete the work on the player’s movement system, it will be here
 	bool intersectsWall;
	std::list<sf::RectangleShape> wallCheckers;

	void loseHP(const int hp);
	void gainHP(const int hp);
	void loseEXP(const int exp);
	void gainEXP(const int exp);

	void move(float dir_x, float dir_y, const float& dt);
	void move(float offsetX, float offsetY);
	void move(const sf::Vector2f& offset);
	void resetVelocityX();
	void resetVelocityY();

	void update(const float& dt) override;
	void render(sf::RenderTarget* target = NULL) override;
};

#include <Source/Player.cpp>
#endif
