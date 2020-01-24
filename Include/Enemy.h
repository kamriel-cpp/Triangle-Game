#ifndef ENEMY_H
#define ENEMY_H

class Enemy : public Triangle
{
private:
	std::string type;

	void initComponents();
public:
 	Enemy(const sf::Vector2f& position, std::string type);
 	virtual ~Enemy();

 	const std::string& getType() const;

	void update(const float& dt, const sf::Vector2f& target_position) override;
};

#include <Source/Enemy.cpp>
#endif
