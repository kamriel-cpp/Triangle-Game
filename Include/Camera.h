#ifndef CAMERA_H
#define CAMERA_H

class Camera
{
private:
	sf::RenderWindow* window;
	sf::View view;
public:
	Camera();
	virtual ~Camera();

	const sf::View& getView() const;

	void setWindow(sf::RenderWindow* window);
	void setSize(const sf::Vector2f& size);
	void setCenter(const sf::Vector2f& center);
	void setViewport(const sf::FloatRect& viewport);
	
	void move(float offsetX, float offsetY, const float& dt);
	void move(const sf::Vector2f offset, const float& dt);
	void zoom(const float factor);
};

#include <Source/Camera.cpp>
#endif
