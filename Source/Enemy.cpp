///Initialization
void Enemy::initComponents()
{
	this->createMovementComponent(this->defaultMaxVelocity, 15.f, 5.f);
	this->createAttributeComponent(1);
}

///Constructors/Destructors
Enemy::Enemy(const sf::Vector2f& position, std::string type)
{
	this->initComponents();

	this->type = type;
	if (this->type == "Melee")
	{
		this->defaultColor.r = 250;
		this->defaultColor.g = 50;
		this->defaultColor.b = 50;
	}
	else if (this->type == "Shooter")
	{
		this->defaultColor.r = 250;
		this->defaultColor.g = 250;
		this->defaultColor.b = 50;
	}

	this->setPosition(position);
	this->setFillColor(this->defaultColor);
}

Enemy::~Enemy()
{
	
}

///Functions
const std::string& Enemy::getType() const
{
	return this->type;
}

void Enemy::update(const float& dt, const sf::Vector2f& target_position)
{
	///Update some components
	if (this->movementComponent)
		this->movementComponent->update(dt);
	if (this->attributeComponent)
		this->attributeComponent->update();

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
}
