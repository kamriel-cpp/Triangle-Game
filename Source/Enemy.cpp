//Initialization
void Enemy::initMovementComponent()
{
	this->movementComponent.initVariables(&this->shape, 100.f, 15.f, 5.f);
}

//Constructors/Destructors
Enemy::Enemy()
{
	this->shape.setFillColor(sf::Color(252, 49, 49));
	this->initMovementComponent();
}

Enemy::Enemy(const sf::Vector2f& position)
{
	this->shape.setPosition(position);
	this->shape.setFillColor(sf::Color(252, 49, 49));
	this->initMovementComponent();
}

Enemy::~Enemy()
{
	/* code */
}

//Functions
void Enemy::move(float dir_x, float dir_y, const float& dt)
{
	this->movementComponent.move(dir_x, dir_y, dt);
}

void Enemy::move(float offsetX, float offsetY)
{
	this->shape.move(offsetX, offsetY);
}

void Enemy::move(const sf::Vector2f& offset)
{
	this->shape.move(offset.x, offset.y);
}

void Enemy::update(const float& dt)
{
	this->movementComponent.update(dt);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
