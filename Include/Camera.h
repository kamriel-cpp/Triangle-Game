#ifndef CAMERA_H
#define CAMERA_H

class Camera
{
private:
	sf::View* view;
	sf::Shape* target;
	sf::RenderWindow* window;
public:
	Camera(sf::View* view = nullptr, sf::Shape* target = nullptr, sf::RenderWindow* window = nullptr);
	virtual ~Camera();

	float smoothing;

	void update(const float& dt);
};

#include <Source/Camera.cpp>
#endif
