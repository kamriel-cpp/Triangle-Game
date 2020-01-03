//Initialization
void Player::initVariables()
{
	this->defaultColor.r = 49;
	this->defaultColor.g = 252;
	this->defaultColor.b = 252;

	this->shape.setFillColor(this->defaultColor);
	this->intersectsWall = false;
}

void Player::initWallCheckers()
{
	for (int i = LEFT; i <= DOWN; i++)
		this->wallCheckers.push_back(sf::RectangleShape());
}

void Player::initMovementComponent()
{
	this->movementComponent = new MovementComponent(&this->shape, 300.f, 15.f, 5.f);
}

void Player::initAttributeComponent()
{
	this->attributeComponent = new AttributeComponent(1);
}

//Constructors/Destructors
Player::Player(const sf::Vector2f& position)
{
	this->initVariables();
	this->initWallCheckers();
	this->initMovementComponent();
	this->initAttributeComponent();

	this->shape.setPosition(position);
}

Player::~Player()
{
	this->movementComponent = nullptr;
	this->attributeComponent = nullptr;
	delete this->movementComponent;
	delete this->attributeComponent;
}

//Functions
void Player::loseHP(const int hp)
{
	if (this->attributeComponent)
		this->attributeComponent->loseHP(hp);
}

void Player::gainHP(const int hp)
{
	if (this->attributeComponent)
		this->attributeComponent->gainHP(hp);
}

void Player::loseEXP(const int exp)
{
	if (this->attributeComponent)
		this->attributeComponent->loseEXP(exp);
}

void Player::gainEXP(const int exp)
{
	if (this->attributeComponent)
		this->attributeComponent->gainEXP(exp);
}

void Player::move(float dir_x, float dir_y, const float& dt)
{
	if (this->movementComponent)
		this->movementComponent->move(dir_x, dir_y, dt);
}

void Player::move(float offsetX, float offsetY)
{
	this->shape.move(offsetX, offsetY);
}

void Player::move(const sf::Vector2f& offset)
{
	this->shape.move(offset.x, offset.y);
}

void Player::resetVelocityX()
{
	if (this->movementComponent)
		this->movementComponent->resetVelocityX();
}

void Player::resetVelocityY()
{
	if (this->movementComponent)
		this->movementComponent->resetVelocityY();
}

void Player::update(const float& dt)
{
	//Update some components
	this->movementComponent->update(dt);
	this->attributeComponent->update();

	//Update wallcheckers
	char counter = 0;
	for (auto& wallChecker : this->wallCheckers)
	{
		if (counter == LEFT || counter == RIGHT)
			wallChecker.setSize(sf::Vector2f(2.f, this->shape.getGlobalBounds().height * 0.75f));
		else if (counter == UP || counter == DOWN)
			wallChecker.setSize(sf::Vector2f(this->shape.getGlobalBounds().width * 0.75f, 2.f));
		if (counter == LEFT)
			wallChecker.setPosition(sf::Vector2f(
				this->shape.getPosition().x - this->shape.getGlobalBounds().width / 2.f,
				this->shape.getPosition().y));
		else if (counter == RIGHT)
			wallChecker.setPosition(sf::Vector2f(
				this->shape.getPosition().x + this->shape.getGlobalBounds().width / 2.f,
				this->shape.getPosition().y));
		else if (counter == UP)
			wallChecker.setPosition(sf::Vector2f(
				this->shape.getPosition().x,
				this->shape.getPosition().y - this->shape.getGlobalBounds().height / 2.f));
		else if (counter == DOWN)
			wallChecker.setPosition(sf::Vector2f(
				this->shape.getPosition().x,
				this->shape.getPosition().y + this->shape.getGlobalBounds().height / 2.f));
		wallChecker.setOrigin(wallChecker.getSize() / 2.f);
		counter++;
	}

	//Print all attributes in the console
	//system("cls");
	//std::cout << this->attributeComponent->debugPrint() << std::endl;
}

void Player::render(sf::RenderTarget* target)
{
	//DEBUG FEATURE
	//for (auto& wallChecker : this->wallCheckers)
	//	target->draw(wallChecker);
	target->draw(this->shape);
}
