//Initialization
void Player::initVariables()
{
	this->defaultColor.r = 50;
	this->defaultColor.g = 250;
	this->defaultColor.b = 250;
	this->shape.setFillColor(this->defaultColor);
	this->defaultMaxVelocity *= 2.f;
}

void Player::initComponents()
{
	this->createMovementComponent(this->defaultMaxVelocity, 15.f, 5.f);
	this->createAttributeComponent(1);
}

//Constructors/Destructors
Player::Player(const sf::Vector2f& position)
{
	this->initVariables();
	this->initComponents();

	this->shape.setPosition(position);
}

Player::~Player()
{
	//empty
}

//Functions
void Player::update(const float& dt, const sf::Vector2f& target_position)
{
	//Update some components
	this->movementComponent->update(dt);
	this->attributeComponent->update();

	if (!this->isDashing)
	{
		//Looking to the target
		sf::Vector2f look_dir(target_position - this->shape.getPosition());
		const float angle = atan2(look_dir.y, look_dir.x) * (180.f / 3.14159265358979323846f) + 90.f;
		this->shape.setRotation(angle);
	}
	else
	{
		//Dashing
	}

	//Update collisionCheckers
	this->collisionCheckers[LEFT].setSize(sf::Vector2f(2.f, this->shape.getGlobalBounds().height * 0.75f));
	this->collisionCheckers[RIGHT].setSize(sf::Vector2f(2.f, this->shape.getGlobalBounds().height * 0.75f));
	this->collisionCheckers[UP].setSize(sf::Vector2f(this->shape.getGlobalBounds().width * 0.75f, 2.f));
	this->collisionCheckers[DOWN].setSize(sf::Vector2f(this->shape.getGlobalBounds().width * 0.75f, 2.f));
	
	this->collisionCheckers[LEFT].setPosition(sf::Vector2f(
				this->shape.getPosition().x - this->shape.getGlobalBounds().width / 2.f,
				this->shape.getPosition().y));
	this->collisionCheckers[RIGHT].setPosition(sf::Vector2f(
				this->shape.getPosition().x + this->shape.getGlobalBounds().width / 2.f,
				this->shape.getPosition().y));
	this->collisionCheckers[UP].setPosition(sf::Vector2f(
				this->shape.getPosition().x,
				this->shape.getPosition().y - this->shape.getGlobalBounds().height / 2.f));
	this->collisionCheckers[DOWN].setPosition(sf::Vector2f(
				this->shape.getPosition().x,
				this->shape.getPosition().y + this->shape.getGlobalBounds().height / 2.f));

	for (int i = LEFT; i <= DOWN; i++)
		this->collisionCheckers[i].setOrigin(this->collisionCheckers[i].getSize() / 2.f);

	//Print all attributes in the console
	//system("cls");
	//std::cout << this->attributeComponent->debugPrint() << std::endl;
}

void Player::render(sf::RenderTarget* target)
{
	if (debugMode)
		if (debugShowCollisionCheckers)
			for (int i = LEFT; i <= DOWN; i++)
				target->draw(this->collisionCheckers[i]);
	
	target->draw(this->shape);
}
