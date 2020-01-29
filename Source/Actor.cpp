///Constructors/Destructors
Actor::Actor()
{
	this->customFillColor.r = 255;
	this->customFillColor.g = 255;
	this->customFillColor.b = 255;
	this->customRadius = 20.f;
	this->customOrigin = sf::Vector2f(this->customRadius, this->customRadius);
	this->customScale = sf::Vector2f(1.f, 1.f);
	this->customPointCount = 30;

	this->setFillColor(this->customFillColor);
	this->setRadius(this->customRadius);
	this->setOrigin(this->customOrigin);
	this->setScale(this->customScale);
	this->setPointCount(this->customPointCount);

	this->movementComponent = nullptr;
	this->attributeComponent = nullptr;
	this->shootComponent = nullptr;
}

Actor::~Actor()
{
	this->movementComponent = nullptr;
	this->attributeComponent = nullptr;
	this->shootComponent = nullptr;
	delete this->movementComponent;
	delete this->attributeComponent;
	delete this->shootComponent;
}

///Functions
const bool Actor::completelyIntersects(const sf::FloatRect bounds) const
{
	int counter = 0;
	for (size_t i = DIR_LEFT; i <= DIR_DOWN; i++)
		if (this->collisionCheckers[i].getGlobalBounds().intersects(bounds))
			counter++;

	if (counter >= 4)
		return true;

	return false;
}

const unsigned char Actor::getSideOfCollision(const sf::FloatRect bounds) const
{
	for (size_t i = DIR_LEFT; i <= DIR_DOWN; i++)
		if (this->collisionCheckers[i].getGlobalBounds().intersects(bounds))
			return (unsigned char)i;
	return 0;
}


void Actor::createMovementComponent(const float max_velocity, const float acceleration, const float deceleration)
{
	this->movementComponent = new MovementComponent(this, max_velocity, acceleration, deceleration);
}

void Actor::createAttributeComponent(const unsigned level)
{
	this->attributeComponent = new AttributeComponent(level);
}

void Actor::createShootComponent()
{
	this->shootComponent = new ShootComponent();
}


void Actor::loseHP(const int hp)
{
	this->attributeComponent->loseHP(hp);
}

void Actor::gainHP(const int hp)
{
	this->attributeComponent->gainHP(hp);
}

void Actor::loseEXP(const int exp)
{
	this->attributeComponent->loseEXP(exp);
}

void Actor::gainEXP(const int exp)
{
	this->attributeComponent->gainEXP(exp);
}

const bool Actor::isDead() const
{
	return this->attributeComponent->isDead();
	return false;
}

const int Actor::getLevel() const
{
	return this->attributeComponent->level;
	return 0;
}

const bool Actor::selectAttributePoints(const int& choise)
{
	return this->attributeComponent->selectAttributePoints(choise);
	return false;
}


void Actor::move(float dir_x, float dir_y, const float& dt)
{
	this->movementComponent->move(dir_x, dir_y, dt);
}

void Actor::setMaxVelocity(float max_velocity)
{
	this->movementComponent->setMaxVelocity(max_velocity);
}

void Actor::resetMaxVelocity()
{
	this->movementComponent->setMaxVelocity(200.f);
}

void Actor::stopVelocityX()
{
	this->movementComponent->stopVelocityX();
}

void Actor::stopVelocityY()
{
	this->movementComponent->stopVelocityY();
}


void Actor::shoot(std::list<Bullet*>* bullets)
{
	if (this->shootComponent)
	{
		sf::Vector2f position;
		position.x = this->getRadius() / 2.f * sin(this->getRotation() * 3.14159265358979323846f / 180.f);
		position.y = this->getRadius() / 2.f * -cos(this->getRotation() * 3.14159265358979323846f / 180.f);

		this->shootComponent->shoot(bullets,
			this->getPosition() + position, this->getRotation(),
			this->attributeComponent->spread, this->attributeComponent->damage,
			this->attributeComponent->bulletsPerShoot,
			this->attributeComponent->bulletSpeed, this->attributeComponent->bulletRadius);
	}
}

void Actor::pick()
{

}

void Actor::dash()
{

}


void Actor::explode(std::list<Effect*>* effects)
{
	effects->push_back(new Explosion(
		this->getPosition(), 1.f,
		this->customFillColor, 4,
		this->getRadius() / 3.f, this->getRadius() / 2.f,
		3, 4,
		2, 25.f));
	effects->push_back(new Explosion(
		this->getPosition(), 1.f,
		this->customFillColor, 6,
		this->getRadius() / 3.f, this->getRadius() / 2.f,
		3, 4,
		3, 50.f));
	effects->push_back(new Explosion(
		this->getPosition(), 1.f,
		this->customFillColor, 8,
		this->getRadius() / 4.f, this->getRadius() / 3.f,
		3, 4,
		4, 75.f));
	effects->push_back(new Explosion(
		this->getPosition(), 1.f,
		this->customFillColor, 10,
		this->getRadius() / 4.f, this->getRadius() / 3.f,
		3, 4,
		5, 100.f));
}

void Actor::blink(std::list<Effect*>* effects)
{
	effects->push_back(new Blink(this, this->customFillColor, 20.f, 0.25f));
}

void Actor::updateCollisionCheckers()
{
	this->collisionCheckers[DIR_LEFT].setSize(sf::Vector2f(2.f, this->getGlobalBounds().height * 0.75f));
	this->collisionCheckers[DIR_RIGHT].setSize(sf::Vector2f(2.f, this->getGlobalBounds().height * 0.75f));
	this->collisionCheckers[DIR_UP].setSize(sf::Vector2f(this->getGlobalBounds().width * 0.75f, 2.f));
	this->collisionCheckers[DIR_DOWN].setSize(sf::Vector2f(this->getGlobalBounds().width * 0.75f, 2.f));

	this->collisionCheckers[DIR_LEFT].setPosition(sf::Vector2f(
				this->getPosition().x - this->getGlobalBounds().width / 2.f,
				this->getPosition().y));
	this->collisionCheckers[DIR_RIGHT].setPosition(sf::Vector2f(
				this->getPosition().x + this->getGlobalBounds().width / 2.f,
				this->getPosition().y));
	this->collisionCheckers[DIR_UP].setPosition(sf::Vector2f(
				this->getPosition().x,
				this->getPosition().y - this->getGlobalBounds().height / 2.f));
	this->collisionCheckers[DIR_DOWN].setPosition(sf::Vector2f(
				this->getPosition().x,
				this->getPosition().y + this->getGlobalBounds().height / 2.f));

	for (int i = DIR_LEFT; i <= DIR_DOWN; i++)
		this->collisionCheckers[i].setOrigin(this->collisionCheckers[i].getSize() / 2.f);
}
