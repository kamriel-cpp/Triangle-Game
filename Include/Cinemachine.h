#ifndef CINEMACHINE_H
#define CINEMACHINE_H

class Cinemachine
{
private:
	Camera* camera;
	sf::Shape* target;
	sf::RenderWindow* window;
public:
	Cinemachine(Camera* camera = nullptr, sf::Shape* target = nullptr, sf::RenderWindow* window = nullptr);
	virtual ~Cinemachine();

	float smoothing;

	void update(const float& dt);
};

#include <Source/Cinemachine.cpp>
#endif
