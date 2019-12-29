//Initialization
void Player::initMovementComponent()
{
	this->movementComponent.initVariables(&this->shape, 300.f, 15.f, 5.f);
}

void Player::initAttributeComponent()
{
	this->attributeComponent.initVariables(1);
}

//Constructors/Destructors
Player::Player()
{
	this->initMovementComponent();
	this->initAttributeComponent();

	this->defaultColor.r = 49;
	this->defaultColor.g = 252;
	this->defaultColor.b = 252;

	this->shape.setFillColor(this->defaultColor);
	this->intersectsWall = false;
}

Player::~Player()
{

}

//Functions
void Player::move(const float dir_x, const float dir_y, const float& dt)
{
	this->movementComponent.move(dir_x, dir_y, dt);
}

void Player::move(const float offsetX, const float offsetY)
{
	this->shape.move(offsetX, offsetY);
}

void Player::resetVelocity()
{
	this->movementComponent.resetVelocity();
}

void Player::update(const float& dt)
{
	//Update some components
	this->movementComponent.update(dt);
	this->attributeComponent.update();

	//Update wallcheckers
	char counter = 0;
	for (auto& wallChecker : this->wallCheckers)
	{
		if (counter == LEFT || counter == RIGHT)
			wallChecker.setSize(sf::Vector2f(1.f, this->shape.getGlobalBounds().height));
		else if (counter == UP || counter == DOWN)
			wallChecker.setSize(sf::Vector2f(this->shape.getGlobalBounds().width, 1.f));
		if (counter == LEFT)
			wallChecker.setPosition(sf::Vector2f(
				this->shape.getPosition().x - this->shape.getGlobalBounds().width / 2.f,
				this->shape.getPosition().y));
		if (counter == RIGHT)
			wallChecker.setPosition(sf::Vector2f(
				this->shape.getPosition().x + this->shape.getGlobalBounds().width / 2.f,
				this->shape.getPosition().y));
		if (counter == UP)
			wallChecker.setPosition(sf::Vector2f(
				this->shape.getPosition().x,
				this->shape.getPosition().y - this->shape.getGlobalBounds().height / 2.f));
		if (counter == DOWN)
			wallChecker.setPosition(sf::Vector2f(
				this->shape.getPosition().x,
				this->shape.getPosition().y + this->shape.getGlobalBounds().height / 2.f));
		wallChecker.setOrigin(wallChecker.getSize() / 2.f);
		counter++;
	}

	//Print all attributes in the console
	//system("cls");
	//std::cout << this->attributeComponent.debugPrint() << std::endl;
}

void Player::render(sf::RenderTarget* target)
{
	//This is for the future.
	//for (auto& wallChecker : this->wallCheckers)
	//	target->draw(wallChecker);
	target->draw(this->shape);
}
