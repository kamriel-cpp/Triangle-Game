#ifndef ENEMY_H
#define ENEMY_H
#include <Include/Actor.h>

class Enemy : public Actor
{
private:
	std::string type;
public:
 	Enemy(const sf::Vector2f& position, std::string type, const int& level);
 	virtual ~Enemy();

 	const std::string& getType() const;

	void updateAutoShooting(Unit* caster, std::list<Bullet*>* bullets);
	void update(const float& dt, const sf::Vector2f& target_position) override;
};

#include <Source/Enemy.cpp>
#endif
