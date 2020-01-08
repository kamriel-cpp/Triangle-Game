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
	this->defaultMaxVelocity = 100.f;
	this->collision = false;

	this->shape.setFillColor(this->defaultColor);
	this->shape.setRadius(this->defaultRadius);
	this->shape.setOrigin(this->defaultOrigin);
	this->shape.setScale(this->defaultScale);
	this->shape.setPointCount(this->defaultPointCount);

	this->movementComponent = nullptr;
	this->attributeComponent = nullptr;
}

Triangle::~Triangle()
{
	this->movementComponent = nullptr;
	this->attributeComponent = nullptr;
	delete this->movementComponent;
	delete this->attributeComponent;
}

//Functions
void Triangle::createMovementComponent(const float max_velocity, const float acceleration, const float deceleration)
{
	this->movementComponent = new MovementComponent(&this->shape, max_velocity, acceleration, deceleration);
}

void Triangle::createAttributeComponent(const unsigned level)
{
	this->attributeComponent = new AttributeComponent(level);
}

void Triangle::loseHP(const int hp)
{
	if (this->attributeComponent)
		this->attributeComponent->loseHP(hp);
}

void Triangle::gainHP(const int hp)
{
	if (this->attributeComponent)
		this->attributeComponent->gainHP(hp);
}

void Triangle::loseEXP(const int exp)
{
	if (this->attributeComponent)
		this->attributeComponent->loseEXP(exp);
}

void Triangle::gainEXP(const int exp)
{
	if (this->attributeComponent)
		this->attributeComponent->gainEXP(exp);
}

void Triangle::move(float dir_x, float dir_y, const float& dt)
{
	if (this->movementComponent)
		this->movementComponent->move(dir_x, dir_y, dt);
}

void Triangle::move(float offsetX, float offsetY)
{
	this->shape.move(offsetX, offsetY);
}

void Triangle::move(const sf::Vector2f& offset)
{
	this->shape.move(offset.x, offset.y);
}

void Triangle::setMaxVelocity(float max_velocity)
{
	if (this->movementComponent)
		this->movementComponent->setMaxVelocity(max_velocity);
}

void Triangle::resetMaxVelocity()
{
	if (this->movementComponent)
		this->movementComponent->setMaxVelocity(this->defaultMaxVelocity);
}

void Triangle::resetVelocityX()
{
	if (this->movementComponent)
		this->movementComponent->resetVelocityX();
}

void Triangle::resetVelocityY()
{
	if (this->movementComponent)
		this->movementComponent->resetVelocityY();
}

const bool Triangle::intersects(const sf::FloatRect bounds) const
{
	if (this->shape.getGlobalBounds().intersects(bounds))
	{
		return true;
	}
	else
	{
		for (size_t i = LEFT; i <= DOWN; i++)
			if (this->collisionCheckers[i].getGlobalBounds().intersects(bounds))
				return true;
	}
	return false;
}

const unsigned char Triangle::getSideOfCollision(const sf::FloatRect bounds) const
{
	for (size_t i = LEFT; i <= DOWN; i++)
		if (this->collisionCheckers[i].getGlobalBounds().intersects(bounds))
			return (unsigned char)i;
	return 0;
}
