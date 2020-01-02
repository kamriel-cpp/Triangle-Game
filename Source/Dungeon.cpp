//Initialization
void Dungeon::initVariables()
{
	for (size_t i = 0; i < 50; i++)
		for (size_t j = 0; j < 50; j++)
			this->floor[i][j] = NONE;
	this->roomSize.x = 500.f;
	this->roomSize.y = 500.f;
	this->corridorLength = this->roomSize.x / 2.f;
	this->corridorWidth = this->corridorLength * 0.5f;
	this->wallThickness = 6.f;

	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
	this->center.x = window_bounds.width / 2.f;
	this->center.y = window_bounds.height / 2.f;

	this->floorColor.r = 31;
	this->floorColor.g = 31;
	this->floorColor.b = 31;

	this->wallColor.r = 255;
	this->wallColor.g = 255;
	this->wallColor.b = 255;
}

//Constructors/Destructors
Dungeon::Dungeon()
{
	this->initVariables();
}

//Functions
const sf::Vector2f Dungeon::getRoomSize()
{
	return this->roomSize;
}

void Dungeon::setRoomSize(sf::Vector2f room_size)
{
	this->roomSize = room_size;
	this->corridorLength = this->roomSize.x / 2.f;
	this->corridorWidth = this->corridorLength * 0.5f;
}

void Dungeon::addStartRoom()
{
	this->rooms.push_back(sf::Vector2u(25, 25));
	this->roomCounter++;
}

void Dungeon::addRoom(sf::Vector2u position)
{
	this->rooms.push_back(position);
	this->roomCounter++;
}

void Dungeon::addBonusRoom(sf::Vector2u position)
{
	this->bonusRooms.push_back(position);
	this->roomCounter++;
}

void Dungeon::addCorridorHorizontal(sf::Vector2u position)
{
	this->corridorsHorizontal.push_back(position);
}

void Dungeon::addCorridorVertical(sf::Vector2u position)
{
	this->corridorsVertical.push_back(position);
}

void Dungeon::fillFloor()
{
	if (!this->rooms.empty())
	{
		for (auto& room : this->rooms)
			this->floor[room.x][room.y] = DEFAULT;

		this->floor[this->rooms.front().x][this->rooms.front().y] = FRONT;
		this->floor[this->rooms.back().x][this->rooms.back().y] = BACK;
	}

	if (!this->bonusRooms.empty())
		for (auto& bonus_room : this->bonusRooms)
			this->floor[bonus_room.x][bonus_room.y] = BONUS;

	if (!this->corridorsHorizontal.empty())
		for (auto& corridor : this->corridorsHorizontal)
			this->floor[corridor.x][corridor.y] = CORRIDOR_HORIZONTAL;

	if (!this->corridorsVertical.empty())
		for (auto& corridor : this->corridorsVertical)
			this->floor[corridor.x][corridor.y] = CORRIDOR_VERTICAL;
}

void Dungeon::fillShapesList()
{
	for (size_t i = 0; i < 50; i++)
	{
		for (size_t j = 0; j < 50; j++)
		{
			if (this->floor[i][j])
			{
				this->shapes.push_back(sf::RectangleShape(this->roomSize));

				if (this->floor[i][j] == CORRIDOR_HORIZONTAL || this->floor[i][j] == CORRIDOR_VERTICAL)
				{
					if (this->floor[i][j] == CORRIDOR_HORIZONTAL)
						this->shapes.back().setSize(sf::Vector2f(this->corridorLength, this->corridorWidth));
					else if (this->floor[i][j] == CORRIDOR_VERTICAL)
						this->shapes.back().setSize(sf::Vector2f(this->corridorWidth, this->corridorLength));
				}
				this->shapes.back().setFillColor(this->floorColor);
				this->shapes.back().setPosition(sf::Vector2f(
					this->roomSize.x * 0.75f * i - this->roomSize.x * 0.75f * 25.f + this->center.x,
					this->roomSize.y * 0.75f * j - this->roomSize.x * 0.75f * 25.f + this->center.y));
				this->shapes.back().setOrigin(this->shapes.back().getSize() / 2.f);
			}
		}
	}
}

void Dungeon::fillWallsList()
{
	sf::Vector2f position;
	for (size_t i = 0; i < 50; i++)
	{
		for (size_t j = 0; j < 50; j++)
		{
			if (this->floor[i][j])
			{
				position.x = this->roomSize.x * 0.75f * i - this->roomSize.x * 0.75f * 25.f + this->center.x;
				position.y = this->roomSize.y * 0.75f * j - this->roomSize.y * 0.75f * 25.f + this->center.y;

				//LEFT
				if (this->floor[i][j] != CORRIDOR_HORIZONTAL)
				{
					this->walls.push_back(sf::RectangleShape());
					this->walls.back().setFillColor(this->wallColor);
					if (this->floor[i][j] == CORRIDOR_VERTICAL)
					{
						this->walls.back().setSize(sf::Vector2f(this->wallThickness, this->corridorLength + this->wallThickness));
						this->walls.back().setPosition(sf::Vector2f(
							position.x - this->corridorWidth / 2.f,
							position.y));
						this->walls.back().setOrigin(this->walls.back().getSize() / 2.f);
					}
					else
					{
						if (this->floor[i - 1][j] == NONE)
						{
							this->walls.back().setSize(sf::Vector2f(this->wallThickness, this->roomSize.y + this->wallThickness));
							this->walls.back().setPosition(sf::Vector2f(
								position.x - this->roomSize.x / 2.f,
								position.y));
							this->walls.back().setOrigin(this->walls.back().getSize() / 2.f);
						}
						else 
						{
							this->walls.back().setSize(sf::Vector2f(this->wallThickness, (this->roomSize.y - this->corridorWidth) / 2.f + this->wallThickness));
							this->walls.back().setPosition(sf::Vector2f(
								position.x - this->roomSize.x / 2.f,
								position.y - (this->corridorWidth / 2.f + (this->roomSize.y - this->corridorWidth) / 4.f)));
							this->walls.back().setOrigin(this->walls.back().getSize() / 2.f);

							this->walls.push_back(sf::RectangleShape());
							this->walls.back().setFillColor(this->wallColor);
							this->walls.back().setSize(sf::Vector2f(this->wallThickness, (this->roomSize.y - this->corridorWidth) / 2.f + this->wallThickness));
							this->walls.back().setPosition(sf::Vector2f(
								position.x - this->roomSize.x / 2.f,
								position.y + (this->corridorWidth / 2.f + (this->roomSize.y - this->corridorWidth) / 4.f)));
							this->walls.back().setOrigin(this->walls.back().getSize() / 2.f);
						}
					}
				}

				//RIGHT
				if (this->floor[i][j] != CORRIDOR_HORIZONTAL)
				{
					this->walls.push_back(sf::RectangleShape());
					this->walls.back().setFillColor(this->wallColor);
					if (this->floor[i][j] == CORRIDOR_VERTICAL)
					{
						this->walls.back().setSize(sf::Vector2f(this->wallThickness, this->corridorLength + this->wallThickness));
						this->walls.back().setPosition(sf::Vector2f(
							position.x + this->corridorWidth / 2.f,
							position.y));
						this->walls.back().setOrigin(this->walls.back().getSize() / 2.f);
					}
					else
					{
						if (this->floor[i + 1][j] == NONE)
						{
							this->walls.back().setSize(sf::Vector2f(this->wallThickness, this->roomSize.y + this->wallThickness));
							this->walls.back().setPosition(sf::Vector2f(
								position.x + this->roomSize.x / 2.f,
								position.y));
							this->walls.back().setOrigin(this->walls.back().getSize() / 2.f);
						}
						else 
						{
							this->walls.back().setSize(sf::Vector2f(this->wallThickness, (this->roomSize.y - this->corridorWidth) / 2.f + this->wallThickness));
							this->walls.back().setPosition(sf::Vector2f(
								position.x + this->roomSize.x / 2.f,
								position.y - (this->corridorWidth / 2.f + (this->roomSize.y - this->corridorWidth) / 4.f)));
							this->walls.back().setOrigin(this->walls.back().getSize() / 2.f);

							this->walls.push_back(sf::RectangleShape());
							this->walls.back().setFillColor(this->wallColor);
							this->walls.back().setSize(sf::Vector2f(this->wallThickness, (this->roomSize.y - this->corridorWidth) / 2.f + this->wallThickness));
							this->walls.back().setPosition(sf::Vector2f(
								position.x + this->roomSize.x / 2.f,
								position.y + (this->corridorWidth / 2.f + (this->roomSize.y - this->corridorWidth) / 4.f)));
							this->walls.back().setOrigin(this->walls.back().getSize() / 2.f);
						}
					}
				}

				//UP
				if (this->floor[i][j] != CORRIDOR_VERTICAL)
				{
					this->walls.push_back(sf::RectangleShape());
					this->walls.back().setFillColor(this->wallColor);
					if (this->floor[i][j] == CORRIDOR_HORIZONTAL)
					{
						this->walls.back().setSize(sf::Vector2f(this->corridorLength + this->wallThickness, this->wallThickness));
						this->walls.back().setPosition(sf::Vector2f(
							position.x,
							position.y - this->corridorWidth / 2.f));
						this->walls.back().setOrigin(this->walls.back().getSize() / 2.f);
					}
					else
					{
						if (this->floor[i][j - 1] == NONE)
						{
							this->walls.back().setSize(sf::Vector2f(this->roomSize.y + this->wallThickness, this->wallThickness));
							this->walls.back().setPosition(sf::Vector2f(
								position.x,
								position.y - this->roomSize.y / 2.f));
							this->walls.back().setOrigin(this->walls.back().getSize() / 2.f);
						}
						else 
						{
							this->walls.back().setSize(sf::Vector2f((this->roomSize.y - this->corridorWidth) / 2.f + this->wallThickness, this->wallThickness));
							this->walls.back().setPosition(sf::Vector2f(
								position.x - (this->corridorWidth / 2.f + (this->roomSize.y - this->corridorWidth) / 4.f),
								position.y - this->roomSize.x / 2.f));
							this->walls.back().setOrigin(this->walls.back().getSize() / 2.f);

							this->walls.push_back(sf::RectangleShape());
							this->walls.back().setFillColor(this->wallColor);
							this->walls.back().setSize(sf::Vector2f((this->roomSize.y - this->corridorWidth) / 2.f + this->wallThickness, this->wallThickness));
							this->walls.back().setPosition(sf::Vector2f(
								position.x + (this->corridorWidth / 2.f + (this->roomSize.y - this->corridorWidth) / 4.f),
								position.y - this->roomSize.x / 2.f));
							this->walls.back().setOrigin(this->walls.back().getSize() / 2.f);
						}
					}
				}

				//DOWN
				if (this->floor[i][j] != CORRIDOR_VERTICAL)
				{
					this->walls.push_back(sf::RectangleShape());
					this->walls.back().setFillColor(this->wallColor);
					if (this->floor[i][j] == CORRIDOR_HORIZONTAL)
					{
						this->walls.back().setSize(sf::Vector2f(this->corridorLength + this->wallThickness, this->wallThickness));
						this->walls.back().setPosition(sf::Vector2f(
							position.x,
							position.y + this->corridorWidth / 2.f));
						this->walls.back().setOrigin(this->walls.back().getSize() / 2.f);
					}
					else
					{
						if (this->floor[i][j + 1] == NONE)
						{
							this->walls.back().setSize(sf::Vector2f(this->roomSize.y + this->wallThickness, this->wallThickness));
							this->walls.back().setPosition(sf::Vector2f(
								position.x,
								position.y + this->roomSize.y / 2.f));
							this->walls.back().setOrigin(this->walls.back().getSize() / 2.f);
						}
						else 
						{
							this->walls.back().setSize(sf::Vector2f((this->roomSize.y - this->corridorWidth) / 2.f + this->wallThickness, this->wallThickness));
							this->walls.back().setPosition(sf::Vector2f(
								position.x - (this->corridorWidth / 2.f + (this->roomSize.y - this->corridorWidth) / 4.f),
								position.y + this->roomSize.x / 2.f));
							this->walls.back().setOrigin(this->walls.back().getSize() / 2.f);

							this->walls.push_back(sf::RectangleShape());
							this->walls.back().setFillColor(this->wallColor);
							this->walls.back().setSize(sf::Vector2f((this->roomSize.y - this->corridorWidth) / 2.f + this->wallThickness, this->wallThickness));
							this->walls.back().setPosition(sf::Vector2f(
								position.x + (this->corridorWidth / 2.f + (this->roomSize.y - this->corridorWidth) / 4.f),
								position.y + this->roomSize.x / 2.f));
							this->walls.back().setOrigin(this->walls.back().getSize() / 2.f);
						}
					}
				}
			}
		}
	}
}

void Dungeon::generate()
{
	this->addStartRoom();

	unsigned int main_rooms_count = rand() % 2 + 4;
	unsigned int bonus_rooms_count = rand() % 2 + 5;
	unsigned int new_direction = 4;

	while (main_rooms_count)
	{
		sf::Vector2u new_room_position(25, 25);
		sf::Vector2u new_corridor_position;
		bool is_horizontal;

		bool is_empty = false;
		do
		{
			//random direction to spawn a new room
			is_empty = true;
			new_direction = rand() % 4;
			if (new_direction == LEFT)
			{
				new_corridor_position = sf::Vector2u(
					this->rooms.back().x - 1,
					this->rooms.back().y);
				new_room_position = sf::Vector2u(
					this->rooms.back().x - 2,
					this->rooms.back().y);
				is_horizontal = true;
			}
			else if (new_direction == RIGHT)
			{
				new_corridor_position = sf::Vector2u(
					this->rooms.back().x + 1,
					this->rooms.back().y);
				new_room_position = sf::Vector2u(
					this->rooms.back().x + 2,
					this->rooms.back().y);
				is_horizontal = true;
			}
			else if (new_direction == UP)
			{
				new_corridor_position = sf::Vector2u(
					this->rooms.back().x,
					this->rooms.back().y - 1);
				new_room_position = sf::Vector2u(
					this->rooms.back().x,
					this->rooms.back().y - 2);
				is_horizontal = false;
			}
			else if (new_direction == DOWN)
			{
				new_corridor_position = sf::Vector2u(
					this->rooms.back().x,
					this->rooms.back().y + 1);
				new_room_position = sf::Vector2u(
					this->rooms.back().x,
					this->rooms.back().y + 2);
				is_horizontal = false;
			}
			for (auto& room : this->rooms)
				if (room.x == new_room_position.x && room.y == new_room_position.y)
					is_empty = false;
		} while (!is_empty);

		//spawning new room and corridor
		this->addRoom(new_room_position);
		if (is_horizontal)
			this->addCorridorHorizontal(new_corridor_position);
		else
			this->addCorridorVertical(new_corridor_position);

		main_rooms_count--;
	}

	while (bonus_rooms_count)
	{
		sf::Vector2u new_room_position(25, 25);
		sf::Vector2u new_corridor_position;
		sf::Vector2u start_room;
		unsigned int start_room_type;
		bool is_horizontal;

		//parent-room type selection
		start_room_type = rand() % 2 ? DEFAULT : BONUS;
		if (this->bonusRooms.size() == 0)
			start_room_type = DEFAULT;
		else if (this->bonusRooms.size() >= this->rooms.size() - 2)
			start_room_type = BONUS;

		bool is_empty = false;
		do
		{
			//random selection of the parent-room from the list
			if (start_room_type == DEFAULT)
			{
				auto room = this->rooms.begin();
				std::advance(room, rand() % (this->rooms.size() - 2) + 1);
				start_room = sf::Vector2u((*room).x, (*room).y);
			}
			else
			{
				auto room = this->bonusRooms.begin();
				std::advance(room, rand() % this->bonusRooms.size());
				start_room = sf::Vector2u((*room).x, (*room).y);
			}

			//random selection of the direction for spawning the parent room
			//and recording the received coordinates in new_room_position
			is_empty = true;
			new_direction = rand() % 4;
			if (new_direction == LEFT)
			{
				new_corridor_position = sf::Vector2u(
					start_room.x - 1,
					start_room.y);
				new_room_position = sf::Vector2u(
					start_room.x - 2,
					start_room.y);
				is_horizontal = true;
			}
			else if (new_direction == RIGHT)
			{
				new_corridor_position = sf::Vector2u(
					start_room.x + 1,
					start_room.y);
				new_room_position = sf::Vector2u(
					start_room.x + 2,
					start_room.y);
				is_horizontal = true;
			}
			else if (new_direction == UP)
			{
				new_corridor_position = sf::Vector2u(
					start_room.x,
					start_room.y - 1);
				new_room_position = sf::Vector2u(
					start_room.x,
					start_room.y - 2);
				is_horizontal = false;
			}
			else if (new_direction == DOWN)
			{
				new_corridor_position = sf::Vector2u(
					start_room.x,
					start_room.y + 1);
				new_room_position = sf::Vector2u(
					start_room.x,
					start_room.y + 2);
				is_horizontal = false;
			}

			//comparing the coordinates of each room from the lists with the new coordinates
			//and if they coincide, then the cycle starts again
			for (auto& room : this->rooms)
				if (room.x == new_room_position.x && room.y == new_room_position.y)
					is_empty = false;
			for (auto& room : this->bonusRooms)
				if (room.x == new_room_position.x && room.y == new_room_position.y)
					is_empty = false;
		} while (!is_empty);

		//spawning new room and corridor
		this->addBonusRoom(new_room_position);
		if (is_horizontal)
			this->addCorridorHorizontal(new_corridor_position);
		else
			this->addCorridorVertical(new_corridor_position);

		bonus_rooms_count--;
	}
	this->fillFloor();
	this->fillShapesList();
	this->fillWallsList();
}

void Dungeon::render(sf::RenderTarget* target)
{
	for (auto& shape : this->shapes)
		target->draw(shape);

	for (auto& wall : this->walls)
		target->draw(wall);
}
