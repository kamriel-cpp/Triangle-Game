//Constructors/Destructors
Triangle::Triangle()
{
	this->shape.setRadius(20.f);
	this->shape.setPointCount(3);
	this->shape.setOrigin(sf::Vector2f(
		this->shape.getRadius(),
		this->shape.getRadius()));
	this->shape.setOutlineColor(sf::Color::White);
	this->shape.setScale(sf::Vector2f(0.75f, 1.f));
}

//Functions
sf::Vector2f Triangle::getPosition()
{
	return this->shape.getPosition();
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
	//updating some variables
}

void Triangle::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
