///Constructors/Destructors
Actor::Actor()
{
	this->defaultColor.r = 255;
	this->defaultColor.g = 255;
	this->defaultColor.b = 255;
	this->defaultRadius = 20.f;
	this->defaultOrigin = sf::Vector2f(this->defaultRadius, this->defaultRadius);
	this->defaultScale = sf::Vector2f(1.f, 1.f);
	this->defaultPointCount = 30;
	this->defaultMaxVelocity = 100.f;

	this->setFillColor(this->defaultColor);
	this->setRadius(this->defaultRadius);
	this->setOrigin(this->defaultOrigin);
	this->setScale(this->defaultScale);
	this->setPointCount(this->defaultPointCount);

	this->movementComponent = nullptr;
	this->attributeComponent = nullptr;
	this->attackComponent = nullptr;
}

Actor::~Actor()
{
	this->movementComponent = nullptr;
	this->attributeComponent = nullptr;
	this->attackComponent = nullptr;
	delete this->movementComponent;
	delete this->attributeComponent;
	delete this->attackComponent;
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

void Actor::createAttackComponent(const bool can_shoot, const bool can_pick, const bool can_dash,
	const float& shooting_cooldown, const float& picking_cooldown, const float& dashing_cooldown, float damage)
{
	this->attackComponent = new AttackComponent(can_shoot, can_pick, can_dash, shooting_cooldown, picking_cooldown, dashing_cooldown, damage);
}


void Actor::loseHP(const int hp)
{
	if (this->attributeComponent)
		this->attributeComponent->loseHP(hp);
}

void Actor::gainHP(const int hp)
{
	if (this->attributeComponent)
		this->attributeComponent->gainHP(hp);
}

void Actor::loseEXP(const int exp)
{
	if (this->attributeComponent)
		this->attributeComponent->loseEXP(exp);
}

void Actor::gainEXP(const int exp)
{
	if (this->attributeComponent)
		this->attributeComponent->gainEXP(exp);
}

const bool Actor::isDead() const
{
	if (this->attributeComponent)
		return this->attributeComponent->isDead();

	return false;
}


void Actor::move(float dir_x, float dir_y, const float& dt)
{
	if (this->movementComponent)
		this->movementComponent->move(dir_x, dir_y, dt);
}

void Actor::setMaxVelocity(float max_velocity)
{
	if (this->movementComponent)
		this->movementComponent->setMaxVelocity(max_velocity);
}

void Actor::resetMaxVelocity()
{
	if (this->movementComponent)
		this->movementComponent->setMaxVelocity(this->defaultMaxVelocity);
}

void Actor::stopVelocityX()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocityX();
}

void Actor::stopVelocityY()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocityY();
}


void Actor::shoot(std::list<Bullet*>* bullets)
{
	if (this->attackComponent)
	{
		sf::Vector2f position;
		position.x = this->getRadius() / 2.f * sin(this->getRotation() * 3.14159265358979323846f / 180.f);
		position.y = this->getRadius() / 2.f * -cos(this->getRotation() * 3.14159265358979323846f / 180.f);
		this->attackComponent->shoot(bullets, this->getPosition() + position, this->getRotation());
	}
}

void Actor::pick()
{
	if (this->attackComponent)
		this->attackComponent->pick();
}

void Actor::dash()
{
	if (this->attackComponent)
		this->attackComponent->dash();
}


void Actor::explode(std::list<Effect*>* effects)
{
	effects->push_back(new Explosion(
		this->getPosition(), 1.f,
		this->defaultColor, 4,
		this->getRadius() / 3.f, this->getRadius() / 2.f,
		3, 4,
		2, 25.f));
	effects->push_back(new Explosion(
		this->getPosition(), 1.f,
		this->defaultColor, 6,
		this->getRadius() / 3.f, this->getRadius() / 2.f,
		3, 4,
		3, 50.f));
	effects->push_back(new Explosion(
		this->getPosition(), 1.f,
		this->defaultColor, 8,
		this->getRadius() / 4.f, this->getRadius() / 3.f,
		3, 4,
		4, 75.f));
	effects->push_back(new Explosion(
		this->getPosition(), 1.f,
		this->defaultColor, 10,
		this->getRadius() / 4.f, this->getRadius() / 3.f,
		3, 4,
		5, 100.f));
}

void Actor::blink(std::list<Effect*>* effects)
{
	effects->push_back(new Blink(this, this->defaultColor, 20.f, 0.25f));
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
