///Constructors/Destructors
Player::Player(const sf::Vector2f& position) : stopped(false)
{
	this->createAttributeComponent(1);
	this->createMovementComponent(200.f, 15.f, 5.f);
	this->createShootComponent();

	this->customFillColor = { 50, 250, 250 };

	this->setFillColor(this->customFillColor);
	this->setPosition(position);
}

Player::~Player() { }

///Functions
const bool Player::isDashing() const
{
	return this->dashing;
}

const bool Player::isStopped() const
{
	return this->stopped;
}

void Player::setStop()
{
	this->stopped = true;
}

void Player::setContinue()
{
	this->stopped = false;
}

void Player::update(const float& dt, const sf::Vector2f& target_position)
{
	///Update some components
	if (this->attributeComponent)
		this->attributeComponent->update();
	if (this->movementComponent)
		this->movementComponent->update(dt);
	if (this->shootComponent)
		this->shootComponent->update(dt, this->attributeComponent->reloadTime);

	///Update collisionCheckers
	this->updateCollisionCheckers();

	if (!this->isDashing())
	{
		///Looking to the target
		sf::Vector2f look_dir(target_position - this->getPosition());
		const float angle = atan2(look_dir.y, look_dir.x) * (180.f / 3.14159265358979323846f) + 90.f;
		this->setRotation(angle);
	}
	else
	{
		///Dashing
	}
}
