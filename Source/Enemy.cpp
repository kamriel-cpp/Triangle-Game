///Constructors/Destructors
Enemy::Enemy(const sf::Vector2f& position, std::string type, const int& level) : type(type)
{
	this->createAttributeComponent(level);
	this->createMovementComponent(100.f, 15.f, 5.f);

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

void Enemy::update(const float& dt, const sf::Vector2f& target_position)
{
	///Update some components
	this->attributeComponent->update();
	this->movementComponent->update(dt);

	///Update collisionCheckers
	this->updateCollisionCheckers();
	
	///Looking to the target
	sf::Vector2f look_dir(target_position - this->getPosition());
	const float angle = atan2(look_dir.y, look_dir.x) * (180.f / 3.14159265358979323846f) + 90.f;
	this->setRotation(angle);
	
	///Moving to the target
	sf::Vector2f move_dir;
	if (target_position.x - this->getPosition().x > 1.f)
		move_dir.x = 1.f;
	else if (target_position.x - this->getPosition().x < -1.f)
		move_dir.x = -1.f;
	else
		move_dir.x = 0.f;

	if (target_position.y - this->getPosition().y > 1.f)
		move_dir.y = 1.f;
	else if (target_position.y - this->getPosition().y < -1.f)
		move_dir.y = -1.f;
	else
		move_dir.y = 0.f;
	
	this->move(move_dir.x, move_dir.y, dt);

	//this->attributeComponent->debugPrint();
}
