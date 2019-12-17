//Constructors/Destructors
Triangle::Triangle()
:	moveDirection(IDLE)  { }

Triangle::Triangle(float x, float y, const short unsigned moveDirection)
:	moveDirection(moveDirection)
{
	this->head = sf::RectangleShape(sf::Vector2f(32.f, 32.f));
	this->head.setPosition(sf::Vector2f(x, y));
	this->head.setFillColor(sf::Color::Green);
	/*this->head.setOutlineThickness(-2.f);
	this->head.setOutlineColor(sf::Color::Yellow);*/
}

Triangle& Triangle::operator=(const Triangle& other)
{
	this->head = other.head;
	this->tail = other.tail;
	this->moveDirection = other.moveDirection;
}

Triangle::~Triangle()
{
	this->tail.clear();
}

//Functions
sf::FloatRect Triangle::getBoundingRect() const
{
	return head.getGlobalBounds();
}

sf::Vector2f Triangle::getPosition()
{
	return head.getPosition();
}

void Triangle::pushTail()
{
	sf::Vector2f new_position;
	for (int i = 0; i < 32; i++)
	{
		if (this->tail.size() != 0)
			new_position = sf::Vector2f(this->tail.back().getPosition().x , this->tail.back().getPosition().y);
		else
			new_position = sf::Vector2f(this->head.getPosition().x, this->head.getPosition().y);
		this->tail.push_back(sf::RectangleShape(sf::Vector2f(32.f, 32.f)));
		this->tail.back().setPosition(new_position);
		this->tail.back().setFillColor(sf::Color::Red);
		this->tail.back().setOutlineThickness(-4.f);
		this->tail.back().setOutlineColor(sf::Color::Green);
	}
}

void Triangle::setFillColor(sf::Color color)
{
	this->head.setFillColor(color);
	for (auto&& shape : this->tail)
		shape.setFillColor(color);
}

void Triangle::setDirection(const short unsigned moveDirection)
{
	/*	switch (moveDirection)
	{
	case MOVING_LEFT:
		this->boundingBox.intersect(this->head.getPosition.x - 32, this->head.getPosition.y);
		break;
	case MOVING_RIGHT:
		this->boundingBox.setPosition(this->head.getPosition.x + 32, this->head.getPosition.y);
		break;
	case MOVING_UP:
		this->boundingBox.setPosition(this->head.getPosition.x, this->head.getPosition.y - 32);
		break;
	case MOVING_DOWN:
		this->boundingBox.setPosition(this->head.getPosition.x, this->head.getPosition.y + 32);
		break;
	default:
		break;
	}*/

	/*for (auto shape : this->tail)
		if (!boundingBox.intersects(shape.getGlobalBounds()))
			this->moveDirection = moveDirection;*/
	this->moveDirection = moveDirection;
}

void Triangle::setPosition(const float x, const float y)
{
	this->head.setPosition(sf::Vector2f(x, y));
}

void Triangle::move(const float& dt)
{
	switch (this->moveDirection)
	{
	case MOVING_LEFT:
		this->head.move(-dt * 100, 0);
		break;
	case MOVING_RIGHT:
		this->head.move(dt * 100, 0);
		break;
	case MOVING_UP:
		this->head.move(0, -dt * 100);
		break;
	case MOVING_DOWN:
		this->head.move(0, dt * 100);
		break;
	default:
		break;
	}

	auto prev = this->tail.begin();

	for (auto&& shape : this->tail)
	{
		if (shape.getPosition().x - 32.f > prev->getPosition().x)
			shape.move(-dt * 100, 0);
		else if (shape.getPosition().x + 32.f < prev->getPosition().x)
			shape.move(dt * 100, 0);
		if (shape.getPosition().y - 32.f > prev->getPosition().y)
			shape.move(0, -dt * 100);
		else if (shape.getPosition().y + 32.f < prev->getPosition().y)
			shape.move(0, dt * 100);
		prev++;
	}
}

void Triangle::update(const float& dt)
{
	boundingBox = this->head.getGlobalBounds();
	this->move(dt);
}

void Triangle::render(sf::RenderTarget* target)
{
	for (auto shape : this->tail)
		target->draw(shape);
	target->draw(this->head);
}
