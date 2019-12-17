#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <stack>
#include <map>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <Include/HitboxComponent.h>
#include <Include/MovementComponent.h>
#include <Include/AnimationComponent.h>

class Entity
{
private:
	//Initialization
	void					initVariables();
protected:
	//Variables
	sf::Sprite				sprite;
	HitboxComponent*		hitboxComponent;
	MovementComponent*		movementComponent;
	AnimationComponent*		animationComponent;
public:
	//Constructors/Destructors
							Entity();
	virtual					~Entity();
	//Component functions
	void					createHitboxComponent(sf::Sprite& sprite,
								float offset_x, float offset_y,
								float width, float height);
	void					createMovementComponent(const float maxVelocity,
								const float accelererion, const float deceleration);
	void					createAnimationComponent(sf::Texture& texture_sheet);
	//Functions
	void					setTexture(sf::Texture& texture);
	virtual void			setPosition(const float x, const float y);
	virtual void			move(const float dir_x, const float dir_y, const float& dt);
	virtual void			update(const float& dt);
	virtual void			render(sf::RenderTarget* target = NULL);
};

#include <Source/Entity.cpp>
#endif
