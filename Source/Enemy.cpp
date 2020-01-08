//Initialization
void Enemy::initVariables()
{
	this->defaultColor.r = 250;
	this->defaultColor.g = 50;
	this->defaultColor.b = 50;
	this->shape.setFillColor(this->defaultColor);
}

void Enemy::initComponents()
{
	this->createMovementComponent(this->defaultMaxVelocity , 15.f, 5.f);
	this->createAttributeComponent(1);
}

//Constructors/Destructors
Enemy::Enemy(const sf::Vector2f& position = sf::Vector2f(0.f, 0.f), sf::Color color = sf::Color::Transparent)
{
	this->initVariables();
	this->initComponents();

	this->shape.setPosition(position);

	if (color != sf::Color::Transparent)
		this->defaultColor = color;
	this->shape.setFillColor(this->defaultColor);
}

Enemy::~Enemy()
{
	//empty
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

void Enemy::update(const float& dt, const sf::Vector2f& target_position)
{
	this->movementComponent->update(dt);

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
	
	//Looking to the target
	sf::Vector2f look_dir(target_position - this->shape.getPosition());
	const float angle = atan2(look_dir.y, look_dir.x) * (180.f / 3.14159265358979323846f) + 90.f;
	this->shape.setRotation(angle);
	
	//Moving to the target
	sf::Vector2f move_dir;
	if (target_position.x - this->shape.getPosition().x > 1.f)
		move_dir.x = 1.f;
	else if (target_position.x - this->shape.getPosition().x < -1.f)
		move_dir.x = -1.f;
	else
		move_dir.x = 0.f;

	if (target_position.y - this->shape.getPosition().y > 1.f)
		move_dir.y = 1.f;
	else if (target_position.y - this->shape.getPosition().y < -1.f)
		move_dir.y = -1.f;
	else
		move_dir.y = 0.f;
	
	this->move(move_dir.x, move_dir.y, dt);
}

void Enemy::render(sf::RenderTarget* target)
{
	if (debugMode)
		if (debugShowCollisionCheckers)
			for (int i = LEFT; i <= DOWN; i++)
				target->draw(this->collisionCheckers[i]);
			
	target->draw(this->shape);
}
