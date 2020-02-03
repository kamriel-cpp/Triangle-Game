///Constructors/Destructors
Player::Player(const sf::Vector2f& position) : stopped(false)
{
	this->createAttributeComponent(1);
	this->createMovementComponent(200.f, 15.f, 5.f);
	this->createShootComponent();

	this->baseFillColor = { 50, 250, 250 };

	#ifdef DEBUG_UNITS_VIEW
	this->baseFillColor = { this->baseFillColor.r, this->baseFillColor.g, this->baseFillColor.b, 150 };
	this->setOutlineThickness(-0.5f);
	this->setOutlineColor({ this->baseFillColor.r, this->baseFillColor.g, this->baseFillColor.b, 250 });
	#endif

	this->setFillColor(this->baseFillColor);
	this->setPosition(position);
}

Player::~Player() { }

///Functions
const bool Player::isStopped() const
{
	return this->stopped;
}

void Player::stop()
{
	this->stopped = true;
}

void Player::unstop()
{
	this->stopped = false;
}

void Player::update(const float& dt, const sf::Vector2f& target_position)
{
	///Update some components
	this->attributeComponent->update();
	this->movementComponent->update(dt);
	this->shootComponent->update(dt, this->attributeComponent->reloadTime);

	///Update collisionCheckers
	this->updateCollisionCheckers();

	///Looking to the target
	sf::Vector2f look_dir(target_position - this->getPosition());
	const float angle = atan2(look_dir.y, look_dir.x) * (180.f / 3.14159265358979323846f) + 90.f;
	this->setRotation(angle);
}
