#pragma once
#ifndef CAMERA_H
#define CAMERA_H

class Camera
{
private:
	sf::RenderWindow* window;
	sf::View view;
	float dt;
public:
	Camera();
	~Camera();

	sf::View& getView();

	void setWindow(sf::RenderWindow* window);
	void setSize(const sf::Vector2f& size);
	void setCenter(const sf::Vector2f& center);
	void setViewport(const sf::FloatRect& viewport);
	
	void move(unsigned int direction);
	void zoom(unsigned int direction);
	void zoom(float factor);

	void update(const float& dt);
	void updateView();
};

#include <Source/Camera.cpp>
#endif
