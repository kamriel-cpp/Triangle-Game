#ifndef PLAYER_H
#define PLAYER_H
#include <Include/Triangle.h>

class Player : public Triangle
{
private:
	bool stopped;
public:
 	Player(const sf::Vector2f& position);
 	virtual ~Player();

	const bool isStopped() const;

	void stop();
	void unstop();

	void update(const float& dt, const sf::Vector2f& target_position) override;
};

#include <Source/Player.cpp>
#endif
