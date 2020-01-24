///Initialization
void Player::initComponents()
{
	this->createMovementComponent(this->defaultMaxVelocity, 15.f, 5.f);
	this->createAttributeComponent(1);
	this->createAttackComponent(true, false, true, 0.f, 1.f, 1.f, 3);
}

///Constructors/Destructors
Player::Player(const sf::Vector2f& position) : stopped(false)
{
	this->defaultMaxVelocity *= 2.f;
	
	this->initComponents();

	this->defaultColor.r = 50;
	this->defaultColor.g = 250;
	this->defaultColor.b = 250;

	this->setFillColor(this->defaultColor);
	this->setPosition(position);
}

Player::~Player()
{
	///empty
}

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
	if (this->movementComponent)
		this->movementComponent->update(dt);
	if (this->attributeComponent)
		this->attributeComponent->update();
	if (this->attackComponent)
		this->attackComponent->update(dt);

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

	///Print all attributes in the console
	//system("cls");
	//std::cout << this->attributeComponent->debugPrint() << std::endl;
}
