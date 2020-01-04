//Initialization
void Enemy::initMovementComponent()
{
	this->movementComponent = new MovementComponent(&this->shape, 100.f, 15.f, 5.f);
}

//Constructors/Destructors
Enemy::Enemy(const sf::Vector2f& position = sf::Vector2f(0.f, 0.f), sf::Color color = sf::Color(250, 50, 50))
{
	this->shape.setPosition(position);
	this->shape.setFillColor(color);
	this->initMovementComponent();
	this->intersectsWall = false;

	for (int i = LEFT; i <= DOWN; i++)
		this->wallCheckers.push_back(sf::RectangleShape());
}

Enemy::~Enemy()
{
	this->movementComponent = nullptr;
	delete movementComponent;
}

//Functions
void Enemy::move(float dir_x, float dir_y, const float& dt)
{
	if (this->movementComponent)
		this->movementComponent->move(dir_x, dir_y, dt);
}

void Enemy::move(float offsetX, float offsetY)
{
	this->shape.move(offsetX, offsetY);
}

void Enemy::move(const sf::Vector2f& offset)
{
	this->shape.move(offset.x, offset.y);
}

void Enemy::resetVelocityX()
{
	if (this->movementComponent)
		this->movementComponent->resetVelocityX();
}

void Enemy::resetVelocityY()
{
	if (this->movementComponent)
		this->movementComponent->resetVelocityY();
}

void Enemy::update(const float& dt)
{
	this->movementComponent->update(dt);

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
}

void Enemy::render(sf::RenderTarget* target)
{
	//DEBUG FEATURE
	//for (auto& wallChecker : this->wallCheckers)
	//	target->draw(wallChecker);
	target->draw(this->shape);
}
