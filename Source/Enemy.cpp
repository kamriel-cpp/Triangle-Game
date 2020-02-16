///Constructors/Destructors
Enemy::Enemy(const sf::Vector2f& position, std::string type, const int& level) : type(type)
{
	this->createAttributeComponent(level);
	this->createMovementComponent(100.f, 15.f, 5.f);
	this->createShootComponent();

	if (this->type == "Melee")
		this->baseFillColor = { 250, 50, 50 };
	else if (this->type == "Shooter")
		this->baseFillColor = { 250, 250, 50 };

	#ifdef DEBUG_UNITS_VIEW
	this->baseFillColor = { this->baseFillColor.r, this->baseFillColor.g, this->baseFillColor.b, 150 };
	this->setOutlineThickness(-0.5f);
	this->setOutlineColor({ this->baseFillColor.r, this->baseFillColor.g, this->baseFillColor.b, 250 });
	#endif

	this->setPosition(position);
	this->setFillColor(this->baseFillColor);
}

Enemy::~Enemy() { }

///Functions
const std::string& Enemy::getType() const
{
	return this->type;
}

void Enemy::update(std::list<Bullet*>* bullets, const sf::Vector2f& target_position, const float& dt)
{
	this->updateComponents(dt);
	this->updateAutoShooting(bullets);
	this->updateTrackingLook(target_position);
	this->updateTrackingMove(target_position, dt);
	this->updateCollisionCheckers();
}
