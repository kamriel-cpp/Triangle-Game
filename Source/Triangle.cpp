//Constructors/Destructors
Triangle::Triangle()
{
	this->shape.setRadius(20.f);
	this->shape.setPointCount(3);
	this->shape.setOrigin(sf::Vector2f(
		this->shape.getRadius(),
		this->shape.getRadius() * 0.75f));
	this->shape.setOutlineColor(sf::Color::White);
	this->shape.setScale(sf::Vector2f(0.75f, 1.f));

	for (int i = LEFT; i <= DOWN; i++)
		this->wallCheckers.push_back(sf::RectangleShape());
}

//Functions
sf::Vector2f Triangle::getPosition()
{
	return this->shape.getPosition();
}

sf::FloatRect Triangle::getGlobalBounds()
{
	return this->shape.getGlobalBounds();
}

void Triangle::setPosition(sf::Vector2f position)
{
	this->shape.setPosition(position);
}

void Triangle::setRotation(float angle)
{
	this->shape.setRotation(angle);
}

void Triangle::setRadius(float radius)
{
	this->shape.setRadius(radius);
}

void Triangle::update(const float& dt)
{
	char counter = 0;
	for (auto& wallChecker : this->wallCheckers)
	{
		if (counter == LEFT || counter == RIGHT)
			wallChecker.setSize(sf::Vector2f(1.f, this->shape.getGlobalBounds().height));
		else if (counter == UP || counter == DOWN)
			wallChecker.setSize(sf::Vector2f(this->shape.getGlobalBounds().width, 1.f));
		if (counter == LEFT)
			wallChecker.setPosition(sf::Vector2f(
				this->shape.getPosition().x - this->shape.getGlobalBounds().width / 2.f,
				this->shape.getPosition().y));
		if (counter == RIGHT)
			wallChecker.setPosition(sf::Vector2f(
				this->shape.getPosition().x + this->shape.getGlobalBounds().width / 2.f,
				this->shape.getPosition().y));
		if (counter == UP)
			wallChecker.setPosition(sf::Vector2f(
				this->shape.getPosition().x,
				this->shape.getPosition().y - this->shape.getGlobalBounds().height / 2.f));
		if (counter == DOWN)
			wallChecker.setPosition(sf::Vector2f(
				this->shape.getPosition().x,
				this->shape.getPosition().y + this->shape.getGlobalBounds().height / 2.f));
		wallChecker.setOrigin(wallChecker.getSize() / 2.f);
		counter++;
	}
}

void Triangle::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
