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
	this->shape.setFillColor(sf::Color(49, 252, 252));
	this->initMovementComponent();
	this->mousePosition = nullptr;
	this->intersectsWall = false;

	this->frame.setFillColor(sf::Color::Transparent);
	this->frame.setOutlineColor(sf::Color::White);
	this->frame.setOutlineThickness(1.f);
	this->frame.setOrigin(sf::Vector2f(
		this->frame.getSize().x / 2,
		this->frame.getSize().y / 2));
}

Player::~Player()
{
	this->mousePosition = nullptr;
	delete this->mousePosition;
}

//Functions
void Player::setMousePosition(sf::Vector2i* mousePosition)
{
	this->mousePosition = mousePosition;
}

void Player::setMousePosition2(sf::Vector2f* mousePosition)
{
	this->mousePosition2 = mousePosition;
}

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
	this->movementComponent.update(dt);
	this->attributeComponent.update();

	this->lookDir.x = (*this->mousePosition).x - 1130 / 2;
	this->lookDir.y = (*this->mousePosition).y - 640 / 2;

	const double pi = 3.14159265358979323846;
	float angle = atan2(this->lookDir.y, this->lookDir.x) * (180.f/pi) + 90.f;
	this->shape.setRotation(angle);

	this->frame.setPosition(this->shape.getPosition());
	this->frame.setSize(sf::Vector2f(
		this->shape.getGlobalBounds().width,
		this->shape.getGlobalBounds().height));

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
