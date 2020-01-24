#ifndef PLAYER_H
#define PLAYER_H

class Player : public Triangle
{
private:
	void initComponents();
	bool dashing;
	bool stopped;
public:
 	Player(const sf::Vector2f& position);
 	virtual ~Player();

	const bool isDashing() const;
	const bool isStopped() const;

	void setStop();
	void setContinue();

	void update(const float& dt, const sf::Vector2f& target_position) override;
};

#include <Source/Player.cpp>
#endif
