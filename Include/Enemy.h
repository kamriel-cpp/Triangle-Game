#ifndef ENEMY_H
#define ENEMY_H

class Enemy : public Triangle
{
private:
	void initVariables();
	void initComponents();
public:
 	Enemy(const sf::Vector2f& position, sf::Color color);
 	virtual ~Enemy();

	void move(float dir_x, float dir_y, const float& dt);
	void move(float offsetX, float offsetY);
	void move(const sf::Vector2f& offset);
	void resetVelocityX();
	void resetVelocityY();

	void update(const float& dt, const sf::Vector2f& target_position) override;
	void render(sf::RenderTarget* target = NULL) override;
};

#include <Source/Enemy.cpp>
#endif
