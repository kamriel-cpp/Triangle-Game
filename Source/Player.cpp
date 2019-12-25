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
	this->lastMove = IDLE;
	this->insideDungeon = true;
	this->frame.setFillColor(sf::Color::Transparent);
	this->frame.setOutlineColor(sf::Color::White);
	this->frame.setOutlineThickness(1.f);
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

void Player::update(const float& dt)
{
	this->movementComponent.update(dt);
	this->attributeComponent.update();

	this->lookDir.x = (*this->mousePosition).x - 1130 / 2;
	this->lookDir.y = (*this->mousePosition).y - 640 / 2;

	const double pi = 3.14159265358979323846;
	float angle = atan2(this->lookDir.y, this->lookDir.x) * (180.f/pi) + 90.f;
	this->shape.setRotation(angle);

	if (!this->insideDungeon)
	{
		switch (this->lastMove)
		{
		case MOVING_LEFT:
			this->move(1.f, 0.f, dt);
			break;
		case MOVING_RIGHT:
			this->move(-1.f, 0.f, dt);
			break;
		case MOVING_UP:
			this->move(0.f, 1.f, dt);
			break;
		case MOVING_DOWN:
			this->move(0.f, -1.f, dt);
			break;
		default:
			break;
		}
	}

	this->frame.setSize(sf::Vector2f(
		this->shape.getGlobalBounds().width,
		this->shape.getGlobalBounds().height));

	this->frame.setPosition(this->shape.getPosition());

	this->frame.setOrigin(sf::Vector2f(
		this->frame.getSize().x / 2,
		this->frame.getSize().y / 2));

	/*
	system("cls");
	std::cout << this->attributeComponent.debugPrint() << std::endl;
	*/
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->frame);
}
