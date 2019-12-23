//Constructors/Destructors
Player::Player()
{
	this->shape.setFillColor(sf::Color(49, 252, 252));
	this->initMovementComponent();
	this->mousePosition = nullptr;
}

Player::~Player()
{
	this->mousePosition = nullptr;
	delete this->mousePosition;
}

void Player::initMovementComponent()
{
	this->movementComponent.initVariables(&this->shape, 300.f, 15.f, 5.f);
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

void Player::update(const float& dt)
{
	this->movementComponent.update(dt);

	this->lookDir.x = (*this->mousePosition).x - 1130 / 2;
	this->lookDir.y = (*this->mousePosition).y - 640 / 2;

	const double pi = 3.14159265358979323846;
	float angle = atan2(this->lookDir.y, this->lookDir.x) * (180.f/pi) + 90.f;
	this->shape.setRotation(angle);
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
