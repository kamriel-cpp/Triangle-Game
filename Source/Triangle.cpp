//Constructors/Destructors
Triangle::Triangle()
{
	this->defaultColor.r = 255;
	this->defaultColor.g = 255;
	this->defaultColor.b = 255;
	this->defaultRadius = 20.f;
	this->defaultOrigin.x = this->defaultRadius;
	this->defaultOrigin.y = this->defaultRadius * 0.75f;
	this->defaultScale.x = 0.75f;
	this->defaultScale.y = 1.f;
	this->defaultPointCount = 3;

	this->shape.setFillColor(this->defaultColor);
	this->shape.setRadius(this->defaultRadius);
	this->shape.setOrigin(this->defaultOrigin);
	this->shape.setScale(this->defaultScale);
	this->shape.setPointCount(this->defaultPointCount);

	for (int i = LEFT; i <= DOWN; i++)
		this->wallCheckers.push_back(sf::RectangleShape());
}

//Functions
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
