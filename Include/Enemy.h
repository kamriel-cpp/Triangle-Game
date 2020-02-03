#ifndef ENEMY_H
#define ENEMY_H
#include <Include/Triangle.h>

class Enemy : public Triangle
{
private:
	std::string type;
public:
 	Enemy(const sf::Vector2f& position, std::string type, const int& level);
 	virtual ~Enemy();

 	const std::string& getType() const;

	void updateAutoShooting(Actor* caster, std::list<Bullet*>* bullets);
	void update(const float& dt, const sf::Vector2f& target_position) override;
};

#include <Source/Enemy.cpp>
#endif
