#ifndef ENEMY_H
#define ENEMY_H
#include <Include/Unit.h>

class Enemy : public Unit
{
private:
	std::string type;
public:
 	Enemy(const sf::Vector2f& position, std::string type, const int& level);
 	virtual ~Enemy();

 	const std::string& getType() const;

	void update(std::list<Bullet*>* bullets, const sf::Vector2f& target_position, const float& dt) override;
};

#include <Source/Enemy.cpp>
#endif
