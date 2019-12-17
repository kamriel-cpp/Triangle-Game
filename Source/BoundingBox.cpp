//Constructors/Destructors
BoundingBox::BoundingBox(sf::RectangleShape& shape)
:	shape(shape)
{
	this->boundingBox.setPosition(0, 0);
	this->boundingBox.setSize(sf::Vector2f(32, 32));
	this->boundingBox.setFillColor(sf::Color::Transparent);
	this->boundingBox.setOutlineThickness(-1.f);
	this->boundingBox.setOutlineColor(sf::Color::Green);
}

BoundingBox::~BoundingBox()
{
	
}

//Functions
const sf::Vector2f & BoundingBox::getPosition() const
{
	return this->boundingBox.getPosition();
}

void BoundingBox::setPosition(const sf::Vector2f& position)
{
	this->boundingBox.setPosition(position);
}

void BoundingBox::setPosition(const float x, const float y)
{
	this->boundingBox.setPosition(x, y);
}

bool BoundingBox::intersects(const sf::FloatRect& frect)
{
	return this->boundingBox.getGlobalBounds().intersects(frect);
}

void BoundingBox::update(const float& dt)
{
	this->boundingBox.setPosition(this->shape.getPosition().x + this->offsetX, this->shape.getPosition().y + this->offsetY);
}

void BoundingBox::render(sf::RenderTarget& target)
{
	target.draw(this->boundingBox);
}