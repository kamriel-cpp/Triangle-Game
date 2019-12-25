//Initialization
void Enemy::initMovementComponent()
{
	this->movementComponent.initVariables(&this->shape, 300.f, 15.f, 5.f);
}

//Constructors/Destructors
Enemy::Enemy()
{
	this->shape.setFillColor(sf::Color(252, 49, 49));
	this->initMovementComponent();
}

Enemy::~Enemy()
{
	/* code */
}

//Functions
void Enemy::move(const float dir_x, const float dir_y, const float& dt)
{
	this->movementComponent.move(dir_x, dir_y, dt);
}

void Enemy::update(const float& dt)
{
	this->movementComponent.move(rand() % 3 - 1, rand() % 3 - 1, dt);
	this->movementComponent.update(dt);
	this->shape.setRotation(this->shape.getRotation() + rand() % 3 - 1);

	//moving towards the player, tracking him.
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
