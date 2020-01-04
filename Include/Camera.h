#ifndef CAMERA_H
#define CAMERA_H

class Camera
{
private:
	sf::View view;
public:
	Camera(sf::RenderWindow* window = nullptr);
	virtual ~Camera();

	const sf::View& getView() const;
	const sf::Vector2f& getSize() const;

	void setSize(const sf::Vector2f& size);
	void setCenter(const sf::Vector2f& center);
	void setViewport(const sf::FloatRect& viewport);
	
	void move(float offsetX, float offsetY, const float& dt);
	void move(const sf::Vector2f offset, const float& dt);
	void zoom(const float factor);
};

#include <Source/Camera.cpp>
#endif
