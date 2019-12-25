#ifndef TRIANGLE_H
#define TRIANGLE_H

/*
 * TODO:
 * 
 * Inside the private section:
 * Variables:
 *  - Shape or Texture
 *  - AttackComponent
 *  - MovementComponent
 *  - two slots of the Guns (maybe Gun*)
 *  - Effect* or std::list of Effects
 *  - some class with triangle parameters (hp, maxhp, maybe armor, xp etc.)
 * 
 * Inside the public section:
 * Functions:
 *  - attack --> the Attack function of the AttackComponent instance should be called here
 *  - death	 --> explosion effect and the destruction of the triangle
 *  - spawn	 --> spawn a triangle on the floor with the zoom effect
 *  - hit	 --> the triangle blinks and takes damage
 *  - dash	 --> is a ghostly movement, faster than the default,
 *				 directed to the mouse and damaging all enemies on the way
 */

class Triangle
{
protected:
	sf::CircleShape shape;
public:
 	Triangle();

 	sf::Vector2f getPosition();
 	sf::FloatRect getGlobalBounds();
 	void setPosition(sf::Vector2f position);
 	void setRotation(float angle);
 	void setRadius(float radius);

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target = NULL);
};

#include <Source/Triangle.cpp>
#endif
