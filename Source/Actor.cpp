///Constructors/Destructors
Actor::Actor()
{
	this->baseFillColor = { 255, 255, 255 };
	this->baseRadius = 20.f;
	this->baseOrigin.x = this->baseRadius;
	this->baseOrigin.y = this->baseRadius * 0.75f;
	this->baseScale.x = 0.75f;
	this->baseScale.y = 1.f;
	this->basePointCount = 3;

	this->setOrigin(this->baseOrigin);
	this->setScale(this->baseScale);
	this->setPointCount(this->basePointCount);

	this->setFillColor(this->baseFillColor);
	this->setRadius(this->baseRadius);
	this->setOrigin(this->baseOrigin);
	this->setScale(this->baseScale);
	this->setPointCount(this->basePointCount);

	this->movementComponent = nullptr;
	this->attributeComponent = nullptr;
	this->shootComponent = nullptr;
}

Actor::~Actor()
{
	delete this->movementComponent;
	delete this->attributeComponent;
	delete this->shootComponent;
	this->movementComponent = nullptr;
	this->attributeComponent = nullptr;
	this->shootComponent = nullptr;
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


void Actor::resetHP()
{
	this->attributeComponent->resetHP();
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
}

const int Actor::getLevel() const
{
	return this->attributeComponent->level;
}

const int Actor::getHP() const
{
	return this->attributeComponent->hp;
}

const int Actor::getHPMax() const
{
	return this->attributeComponent->hpMax;
}

const int Actor::getEXP() const
{
	return this->attributeComponent->exp;
}

const long Actor::getEXPNext() const
{
	return this->attributeComponent->expNext;
}

const float Actor::getReloadTime() const
{
	return this->attributeComponent->reloadTime;
}

const float Actor::getReloadTimer() const
{
	return this->shootComponent->timer;
}

const bool Actor::selectAttributePoints(const int& choise)
{
	return this->attributeComponent->selectAttributePoints(choise);
	return false;
}

void Actor::levelUp()
{
	this->attributeComponent->gainEXP(this->attributeComponent->expNext);
}

void Actor::debugPrint()
{
	this->attributeComponent->debugPrint();
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


void Actor::shoot(Unit* caster, std::list<Bullet*>* bullets)
{
	if (this->shootComponent != nullptr)
	{
		sf::Vector2f position;
		position.x = this->getRadius() / 2.f * sin(this->getRotation() * 3.14159265358979323846f / 180.f);
		position.y = this->getRadius() / 2.f * -cos(this->getRotation() * 3.14159265358979323846f / 180.f);

		this->shootComponent->shoot(caster, bullets,
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
		this->baseFillColor, 20,
		this->getRadius() / 4.f, this->getRadius() / 2.f,
		3, 4,
		2, 4,
		25.f, 100.f));
}

void Actor::blink(std::list<Effect*>* effects)
{
	effects->push_back(new Blink(this, this->baseFillColor, 0.25f));
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

void Actor::renderCollisionCheckers(sf::RenderTarget* target)
{
	for (int i = DIR_LEFT; i <= DIR_DOWN; i++)
		target->draw(this->collisionCheckers[i]);
}
