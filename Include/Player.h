#ifndef PLAYER_H
#define PLAYER_H
#include <Include/Unit.h>

class Player : public Unit
{
public:
 	Player(const sf::Vector2f& position);
 	virtual ~Player();

	void update(std::list<Bullet*>* bullets, const sf::Vector2f& target_position, const float& dt) override;
	void updateAutoShooting(std::list<Bullet*>* bullets) override;
};

#include <Source/Player.cpp>
#endif
