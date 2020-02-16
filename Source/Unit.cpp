///Constructors/Destructors
Unit::Unit()
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

Unit::~Unit()
{
	delete this->shootComponent;
	delete this->attributeComponent;
	delete this->movementComponent;

	this->shootComponent = nullptr;
	this->attributeComponent = nullptr;
	this->movementComponent = nullptr;
}

///Functions
const bool Unit::completelyIntersects(const sf::FloatRect bounds) const
{
	int counter = 0;
	for (size_t i = DIR_LEFT; i <= DIR_DOWN; i++)
		if (this->collisionCheckers[i].getGlobalBounds().intersects(bounds))
			counter++;

	if (counter >= 4)
		return true;

	return false;
}

const unsigned char Unit::getSideOfCollision(const sf::FloatRect bounds) const
{
	for (size_t i = DIR_LEFT; i <= DIR_DOWN; i++)
		if (this->collisionCheckers[i].getGlobalBounds().intersects(bounds))
			return (unsigned char)i;
	return 0;
}


void Unit::createMovementComponent(const float max_velocity, const float acceleration, const float deceleration)
{
	this->movementComponent = new MovementComponent(this, max_velocity, acceleration, deceleration);
}

void Unit::createAttributeComponent(const unsigned level)
{
	this->attributeComponent = new AttributeComponent(level);
}

void Unit::createShootComponent()
{
	this->shootComponent = new ShootComponent();
}


void Unit::resetHP()
{
	this->attributeComponent->resetHP();
}

void Unit::loseHP(const int hp)
{
	this->attributeComponent->loseHP(hp);
}

void Unit::gainHP(const int hp)
{
	this->attributeComponent->gainHP(hp);
}

void Unit::loseEXP(const int exp)
{
	this->attributeComponent->loseEXP(exp);
}

void Unit::gainEXP(const int exp)
{
	this->attributeComponent->gainEXP(exp);
}

const bool Unit::isDead() const
{
	return this->attributeComponent->isDead();
}


const bool Unit::wasChangedLVL() const
{
	return this->attributeComponent->wasChangedLVL;
}

const bool Unit::wasChangedEXP() const
{
	return this->attributeComponent->wasChangedEXP;
}

const bool Unit::wasChangedAPS() const
{
	return this->attributeComponent->wasChangedAPS;
}

const bool Unit::wasChangedHP() const
{
	return this->attributeComponent->wasChangedHP;
}


const int Unit::getAttribute(const unsigned int attribute_tag) const
{
	switch (attribute_tag)
	{
	case UAT_MHP:
		return this->attributeComponent->mhp;
		break;
	case UAT_SPS:
		return this->attributeComponent->sps;
		break;
	case UAT_SPR:
		return this->attributeComponent->spr;
		break;
	case UAT_DMG:
		return this->attributeComponent->dmg;
		break;
	case UAT_BPS:
		return this->attributeComponent->bps;
		break;
	case UAT_BSP:
		return this->attributeComponent->bsp;
		break;
	case UAT_BRD:
		return this->attributeComponent->brd;
		break;
	default:
		std::cerr << "ERROR::UNIT::COULD_NOT_FOUND_ATTRIBUTE_TAG::" << std::to_string(attribute_tag) << std::endl;
		throw;
	}
}

const int Unit::getLVL() const
{
	return this->attributeComponent->lvl;
}

const int Unit::getEXP() const
{
	return this->attributeComponent->exp;
}

const long Unit::getEXPNext() const
{
	return this->attributeComponent->expNext;
}

const int Unit::getAPS() const
{
	return this->attributeComponent->aps;
}

const int Unit::getHP() const
{
	return this->attributeComponent->hp;
}

const float Unit::getReloadPercent() const
{
	return this->shootComponent->reloadPercent;
}

const bool Unit::manualDistributeAPS(const int& choise)
{
	return this->attributeComponent->manualDistributeAPS(choise);
	return false;
}

void Unit::lvlUp()
{
	this->attributeComponent->gainEXP(this->attributeComponent->expNext);
}

void Unit::debugStatsPrint()
{
	this->attributeComponent->debugPrint();
}


void Unit::move(float dir_x, float dir_y, const float& dt)
{
	this->movementComponent->move(dir_x, dir_y, dt);
}

void Unit::setMaxVelocity(float max_velocity)
{
	this->movementComponent->setMaxVelocity(max_velocity);
}

void Unit::resetMaxVelocity()
{
	this->movementComponent->setMaxVelocity(200.f);
}

void Unit::stopVelocityX()
{
	this->movementComponent->stopVelocityX();
}

void Unit::stopVelocityY()
{
	this->movementComponent->stopVelocityY();
}


void Unit::shoot(std::list<Bullet*>* bullets)
{
	if (!this->shootComponent)
	{
		std::cerr << "ERROR::UNIT::DETECTED_USING_UNINITIALIZED_SHOOTCOMPONENT" << std::endl;
		throw;
	}

	sf::Vector2f position;
	position.x = this->getRadius() / 2.f * sin(this->getRotation() * 3.14159265358979323846f / 180.f);
	position.y = this->getRadius() / 2.f * -cos(this->getRotation() * 3.14159265358979323846f / 180.f);

	this->shootComponent->shoot(bullets,
		this, this->baseFillColor,
		this->getPosition() + position, this->getRotation(),
		this->attributeComponent->spr, this->attributeComponent->dmg,
		this->attributeComponent->bps,
		this->attributeComponent->bsp, this->attributeComponent->brd);
}


void Unit::explode(std::list<Effect*>* effects)
{
	effects->push_back(new Explosion(
		this->getPosition(), 1.f,
		this->baseFillColor, 20,
		this->getRadius() / 4.f, this->getRadius() / 2.f,
		3, 4,
		2, 4,
		25.f, 100.f));
}

void Unit::blink(std::list<Effect*>* effects)
{
	effects->push_back(new Blink(this, this->baseFillColor, 0.25f));
}


void Unit::updateAutoShooting(std::list<Bullet*>* bullets)
{
	this->shoot(bullets);
}

void Unit::updateTrackingLook(const sf::Vector2f& target_position)
{
	this->setRotation(
		atan2(target_position.y - this->getPosition().y, target_position.x - this->getPosition().x)
		* (180.f / 3.14159265358979323846f) + 90.f);
}

void Unit::updateTrackingMove(const sf::Vector2f& target_position, const float& dt)
{
	this->move(
		target_position.x - this->getPosition().x > 1.f ? 1 : target_position.x - this->getPosition().x < -1.f ? -1 : 0,
		target_position.y - this->getPosition().y > 1.f ? 1 : target_position.y - this->getPosition().y < -1.f ? -1 : 0,
		dt);
}

void Unit::updateComponents(const float& dt)
{
	this->movementComponent->update(dt);
	this->shootComponent->update(dt, this->attributeComponent->sps);
}

void Unit::updateCollisionCheckers()
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

void Unit::renderCollisionCheckers(sf::RenderTarget* target)
{
	for (int i = DIR_LEFT; i <= DIR_DOWN; i++)
		target->draw(this->collisionCheckers[i]);
}
