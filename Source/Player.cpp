///Constructors/Destructors
Player::Player(const sf::Vector2f& position)
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
void Player::updateAutoShooting(std::list<Bullet*>* bullets) { }

void Player::update(std::list<Bullet*>* bullets, const sf::Vector2f& target_position, const float& dt)
{
	this->updateComponents(dt);
	this->updateAutoShooting(bullets);
	this->updateTrackingLook(target_position);
	this->updateCollisionCheckers();
}
