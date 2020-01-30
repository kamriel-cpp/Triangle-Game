///Constructors/Destructors
Room::Room(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color,
	const unsigned char tag, const unsigned char nearby_cells[4]) : tag(tag), isVisited(false)
{
	///Shape Settings
	this->shape.setPosition(position);
	if (this->tag == RT_CORRIDOR_HORIZONTAL)
		this->shape.setSize(sf::Vector2f(size.x + 1.f, size.y));
	else if (this->tag == RT_CORRIDOR_VERTICAL)
		this->shape.setSize(sf::Vector2f(size.x, size.y + 1.f));
	else
		this->shape.setSize(size);
	this->shape.setOrigin(this->shape.getSize() / 2.f);
	this->shape.setFillColor(color);

	#ifdef DEBUG_FLOOR_VIEW
	this->shape.setFillColor({ color.r, color.g, color.b, 150 });
	this->shape.setOutlineThickness(-0.5f);
	this->shape.setOutlineColor({ color.r, color.g, color.b, 250 });
	#endif

	///Wall Settings
	this->wallThickness = 6.f;
	this->wallColor = { 255, 255, 255 };

	///Position Settings
	this->centerPosition = position;
	this->leftSidePosition = sf::Vector2f(position.x - size.x / 2.f + this->wallThickness / 2.f, position.y);
	this->rightSidePosition = sf::Vector2f(position.x + size.x / 2.f - this->wallThickness / 2.f, position.y);
	this->upSidePosition = sf::Vector2f(position.x, position.y - size.y / 2.f + this->wallThickness / 2.f);
	this->downSidePosition = sf::Vector2f(position.x, position.y + size.y / 2.f - this->wallThickness / 2.f);

	///Wall Placing
	if (this->tag == RT_CORRIDOR_HORIZONTAL)
	{
		this->placeWall(upSidePosition, sf::Vector2f(size.x + this->wallThickness * 2.f, this->wallThickness));
		this->placeWall(downSidePosition, sf::Vector2f(size.x + this->wallThickness * 2.f, this->wallThickness));
	}
	else if (this->tag == RT_CORRIDOR_VERTICAL)
	{
		this->placeWall(leftSidePosition, sf::Vector2f(this->wallThickness, size.y + this->wallThickness * 2.f));
		this->placeWall(rightSidePosition, sf::Vector2f(this->wallThickness, size.y + this->wallThickness * 2.f));
	}
	else
	{
		///Left Wall
		if (nearby_cells[DIR_LEFT] == RT_NONE)
		{
			this->placeWall(leftSidePosition, sf::Vector2f(this->wallThickness, size.y));
		}
		else
		{
			sf::Vector2f upper_wall_pos = sf::Vector2f(
				leftSidePosition.x,
				leftSidePosition.y - (size.y / 8.f + (size.y - size.y / 4.f) / 4.f) + this->wallThickness / 2.f);
			sf::Vector2f lower_wall_pos = sf::Vector2f(
				leftSidePosition.x,
				leftSidePosition.y + (size.y / 8.f + (size.y - size.y / 4.f) / 4.f) - this->wallThickness / 2.f);

			sf::Vector2f wall_size = sf::Vector2f(this->wallThickness, (size.y - size.y / 4.f) / 2.f + this->wallThickness);

			this->placeWall(upper_wall_pos, wall_size);
			this->placeWall(lower_wall_pos, wall_size);
		}
		///Right Wall
		if (nearby_cells[DIR_RIGHT] == RT_NONE)
		{
			this->placeWall(rightSidePosition, sf::Vector2f(this->wallThickness, size.y));
		}
		else
		{
			sf::Vector2f upper_wall_pos = sf::Vector2f(
				rightSidePosition.x,
				rightSidePosition.y - (size.y / 8.f + (size.y - size.y / 4.f) / 4.f) + this->wallThickness / 2.f);
			sf::Vector2f lower_wall_pos = sf::Vector2f(
				rightSidePosition.x,
				rightSidePosition.y + (size.y / 8.f + (size.y - size.y / 4.f) / 4.f) - this->wallThickness / 2.f);

			sf::Vector2f wall_size = sf::Vector2f(this->wallThickness, (size.y - size.y / 4.f) / 2.f + this->wallThickness);

			this->placeWall(upper_wall_pos, wall_size);
			this->placeWall(lower_wall_pos, wall_size);
		}
		///Upper Wall
		if (nearby_cells[DIR_UP] == RT_NONE)
		{
			this->placeWall(upSidePosition, sf::Vector2f(size.x, this->wallThickness));
		}
		else
		{
			sf::Vector2f left_wall_pos = sf::Vector2f(
				upSidePosition.x - (size.x / 8.f + (size.x - size.x / 4.f) / 4.f) + this->wallThickness / 2.f,
				upSidePosition.y);
			sf::Vector2f right_wall_pos = sf::Vector2f(
				upSidePosition.x + (size.x / 8.f + (size.x - size.x / 4.f) / 4.f) - this->wallThickness / 2.f,
				upSidePosition.y);

			sf::Vector2f wall_size = sf::Vector2f((size.x - size.x / 4.f) / 2.f + this->wallThickness, this->wallThickness);

			this->placeWall(left_wall_pos, wall_size);
			this->placeWall(right_wall_pos, wall_size);
		}
		///Lower Wall
		if (nearby_cells[DIR_DOWN] == RT_NONE)
		{
			this->placeWall(downSidePosition, sf::Vector2f(size.x, this->wallThickness));
		}
		else
		{
			sf::Vector2f left_wall_pos = sf::Vector2f(
				downSidePosition.x - (size.x / 8.f + (size.x - size.x / 4.f) / 4.f) + this->wallThickness / 2.f,
				downSidePosition.y);
			sf::Vector2f right_wall_pos = sf::Vector2f(
				downSidePosition.x + (size.x / 8.f + (size.x - size.x / 4.f) / 4.f) - this->wallThickness / 2.f,
				downSidePosition.y);

			sf::Vector2f wall_size = sf::Vector2f((size.x - size.x / 4.f) / 2.f + this->wallThickness, this->wallThickness);

			this->placeWall(left_wall_pos, wall_size);
			this->placeWall(right_wall_pos, wall_size);
		}
	}
}

Room::~Room()
{
	while (!this->walls.empty())
	{
		delete this->walls.back();
		this->walls.pop_back();
	}

	while (!this->doors.empty())
	{
		delete this->doors.back();
		this->doors.pop_back();
	}
}

///Functions
const std::list<sf::RectangleShape*> Room::getWalls() const
{
	return this->walls;
}

const std::list<sf::RectangleShape*> Room::getDoors() const
{
	return this->doors;
}

void Room::placeWall(const sf::Vector2f& position, const sf::Vector2f& size)
{
	this->walls.push_back(new sf::RectangleShape());
	this->walls.back()->setPosition(position);
	this->walls.back()->setSize(size);
	this->walls.back()->setOrigin(size / 2.f);
	this->walls.back()->setFillColor(this->wallColor);

	#ifdef DEBUG_FLOOR_VIEW
	this->walls.back()->setFillColor({ this->wallColor.r, this->wallColor.g, this->wallColor.b, 150 });
	this->walls.back()->setOutlineThickness(-0.5f);
	this->walls.back()->setOutlineColor({ this->wallColor.r, this->wallColor.g, this->wallColor.b, 250 });
	#endif
}

void Room::placeDoor(const sf::Vector2f& position, const sf::Vector2f& size)
{
	for (auto& wall : this->walls)
		if (wall->getPosition() == position)
			return;
	this->doors.push_back(new sf::RectangleShape());
	this->doors.back()->setPosition(position);
	this->doors.back()->setSize(size);
	this->doors.back()->setOrigin(size / 2.f);
	this->doors.back()->setFillColor(this->wallColor);

	#ifdef DEBUG_FLOOR_VIEW
	this->doors.back()->setFillColor({ this->wallColor.r, this->wallColor.g, this->wallColor.b, 150 });
	this->doors.back()->setOutlineThickness(-0.5f);
	this->doors.back()->setOutlineColor({ this->wallColor.r, this->wallColor.g, this->wallColor.b, 250 });
	#endif
}

void Room::open()
{
	while (!this->doors.empty())
	{
		delete this->doors.back();
		this->doors.pop_back();
	}
}

void Room::close()
{
	this->placeDoor(this->leftSidePosition, sf::Vector2f(this->wallThickness, this->shape.getSize().y / 4.f));
	this->placeDoor(this->rightSidePosition, sf::Vector2f(this->wallThickness, this->shape.getSize().y / 4.f));
	this->placeDoor(this->upSidePosition, sf::Vector2f(this->shape.getSize().y / 4.f, this->wallThickness));
	this->placeDoor(this->downSidePosition, sf::Vector2f(this->shape.getSize().y / 4.f, this->wallThickness));
}

void Room::render(sf::RenderTarget* target)
{
	target->draw(this->shape);

	for (auto& wall : this->walls)
		target->draw(*wall);

	for (auto& door : this->doors)
		target->draw(*door);
}
