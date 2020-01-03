//Initialization
void Dungeon::initVariables()
{
	for (size_t i = 0; i < 50; i++)
		for (size_t j = 0; j < 50; j++)
			this->floor[i][j] = NONE;
	this->roomSize.x = 1000.f;
	this->roomSize.y = 1000.f;
	this->corridorLength = this->roomSize.x / 2.f;
	this->corridorWidth = this->corridorLength / 2.f;
	this->wallThickness = 6.f;

	this->centerPosition.x = sf::VideoMode::getDesktopMode().width / 2.f;
	this->centerPosition.y = sf::VideoMode::getDesktopMode().height / 2.f;

	this->startRoomPosition = this->centerPosition;
	this->lastRoomPosition = this->centerPosition;

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
	this->corridorWidth = this->corridorLength / 2.f;
}

void Dungeon::closeRoom(unsigned int index)
{
	//closing room at index
	/*int i = 0;
	for (auto& room : this->rooms)
	{
		if (i == index)
		{
			//do something
		}
		i++;
	}*/
}

void Dungeon::fillRoomsList()
{
	sf::Vector2f position;
	sf::Vector2f size;
	for (size_t i = 0; i < 50; i++)
	{
		for (size_t j = 0; j < 50; j++)
		{
			if (this->floor[i][j])
			{
				position.x = (this->corridorLength + this->roomSize.x) / 2.f * i - (this->corridorLength + this->roomSize.x) / 2.f * 25.f + this->centerPosition.x;
				position.y = (this->corridorLength + this->roomSize.y) / 2.f * j - (this->corridorLength + this->roomSize.y) / 2.f * 25.f + this->centerPosition.y;
				if (this->floor[i][j] == CORRIDOR_HORIZONTAL)
					size = sf::Vector2f(this->corridorLength, this->corridorWidth);
				else if (this->floor[i][j] == CORRIDOR_VERTICAL)
					size = sf::Vector2f(this->corridorWidth, this->corridorLength);
				else
					size = this->roomSize;

				if (this->floor[i][j] == CORRIDOR_HORIZONTAL || this->floor[i][j] == CORRIDOR_VERTICAL)
					this->rooms.push_back(new Corridor(position, size, this->floorColor, this->floor[i][j]));
				else if (this->floor[i][j] == CORRIDOR_VERTICAL)
					this->rooms.push_back(new Corridor(position, size, this->floorColor, this->floor[i][j]));
				else
					this->rooms.push_back(new Room(position, size, this->floorColor, this->floor[i][j]));
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
				position.x = (this->corridorLength + this->roomSize.x) / 2.f * i - (this->corridorLength + this->roomSize.x) / 2.f * 25.f + this->centerPosition.x;
				position.y = (this->corridorLength + this->roomSize.y) / 2.f * j - (this->corridorLength + this->roomSize.y) / 2.f * 25.f + this->centerPosition.y;

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
							this->walls.back().setSize(sf::Vector2f(this->roomSize.x + this->wallThickness, this->wallThickness));
							this->walls.back().setPosition(sf::Vector2f(
								position.x,
								position.y - this->roomSize.y / 2.f));
							this->walls.back().setOrigin(this->walls.back().getSize() / 2.f);
						}
						else 
						{
							this->walls.back().setSize(sf::Vector2f((this->roomSize.x - this->corridorWidth) / 2.f + this->wallThickness, this->wallThickness));
							this->walls.back().setPosition(sf::Vector2f(
								position.x - (this->corridorWidth / 2.f + (this->roomSize.x - this->corridorWidth) / 4.f),
								position.y - this->roomSize.y / 2.f));
							this->walls.back().setOrigin(this->walls.back().getSize() / 2.f);

							this->walls.push_back(sf::RectangleShape());
							this->walls.back().setFillColor(this->wallColor);
							this->walls.back().setSize(sf::Vector2f((this->roomSize.x - this->corridorWidth) / 2.f + this->wallThickness, this->wallThickness));
							this->walls.back().setPosition(sf::Vector2f(
								position.x + (this->corridorWidth / 2.f + (this->roomSize.x - this->corridorWidth) / 4.f),
								position.y - this->roomSize.y / 2.f));
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
							this->walls.back().setSize(sf::Vector2f(this->roomSize.x + this->wallThickness, this->wallThickness));
							this->walls.back().setPosition(sf::Vector2f(
								position.x,
								position.y + this->roomSize.y / 2.f));
							this->walls.back().setOrigin(this->walls.back().getSize() / 2.f);
						}
						else 
						{
							this->walls.back().setSize(sf::Vector2f((this->roomSize.x - this->corridorWidth) / 2.f + this->wallThickness, this->wallThickness));
							this->walls.back().setPosition(sf::Vector2f(
								position.x - (this->corridorWidth / 2.f + (this->roomSize.x - this->corridorWidth) / 4.f),
								position.y + this->roomSize.y / 2.f));
							this->walls.back().setOrigin(this->walls.back().getSize() / 2.f);

							this->walls.push_back(sf::RectangleShape());
							this->walls.back().setFillColor(this->wallColor);
							this->walls.back().setSize(sf::Vector2f((this->roomSize.x - this->corridorWidth) / 2.f + this->wallThickness, this->wallThickness));
							this->walls.back().setPosition(sf::Vector2f(
								position.x + (this->corridorWidth / 2.f + (this->roomSize.x - this->corridorWidth) / 4.f),
								position.y + this->roomSize.y / 2.f));
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
	//Lists the positions of rooms of each type in the array floor[][]
	std::list<sf::Vector2u> rooms_coords;
	std::list<sf::Vector2u> bonus_rooms_coords;
	std::list<sf::Vector2u> horizontal_corridors_coords;
	std::list<sf::Vector2u> vertical_corridors_coords;

	rooms_coords.push_back(sf::Vector2u(25, 25));

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
					rooms_coords.back().x - 1,
					rooms_coords.back().y);
				new_room_position = sf::Vector2u(
					rooms_coords.back().x - 2,
					rooms_coords.back().y);
				is_horizontal = true;
			}
			else if (new_direction == RIGHT)
			{
				new_corridor_position = sf::Vector2u(
					rooms_coords.back().x + 1,
					rooms_coords.back().y);
				new_room_position = sf::Vector2u(
					rooms_coords.back().x + 2,
					rooms_coords.back().y);
				is_horizontal = true;
			}
			else if (new_direction == UP)
			{
				new_corridor_position = sf::Vector2u(
					rooms_coords.back().x,
					rooms_coords.back().y - 1);
				new_room_position = sf::Vector2u(
					rooms_coords.back().x,
					rooms_coords.back().y - 2);
				is_horizontal = false;
			}
			else if (new_direction == DOWN)
			{
				new_corridor_position = sf::Vector2u(
					rooms_coords.back().x,
					rooms_coords.back().y + 1);
				new_room_position = sf::Vector2u(
					rooms_coords.back().x,
					rooms_coords.back().y + 2);
				is_horizontal = false;
			}
			for (auto& room : rooms_coords)
				if (room.x == new_room_position.x && room.y == new_room_position.y)
					is_empty = false;
		} while (!is_empty);

		//spawning new room and corridor
		rooms_coords.push_back(new_room_position);
		if (is_horizontal)
			horizontal_corridors_coords.push_back(new_corridor_position);
		else
			vertical_corridors_coords.push_back(new_corridor_position);

		this->lastRoomPosition.x = (this->corridorLength + this->roomSize.x) / 2.f * new_room_position.x - (this->corridorLength + this->roomSize.x) / 2.f * 25.f + this->centerPosition.x;
		this->lastRoomPosition.y = (this->corridorLength + this->roomSize.y) / 2.f * new_room_position.y - (this->corridorLength + this->roomSize.y) / 2.f * 25.f + this->centerPosition.y;

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
		if (bonus_rooms_coords.size() == 0)
			start_room_type = DEFAULT;
		else if (bonus_rooms_coords.size() >= rooms_coords.size() - 2)
			start_room_type = BONUS;

		bool is_empty = false;
		do
		{
			//random selection of the parent-room from the list
			if (start_room_type == DEFAULT)
			{
				auto room = rooms_coords.begin();
				std::advance(room, rand() % (rooms_coords.size() - 2) + 1);
				start_room = sf::Vector2u((*room).x, (*room).y);
			}
			else
			{
				auto room = bonus_rooms_coords.begin();
				std::advance(room, rand() % bonus_rooms_coords.size());
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
			for (auto& room : rooms_coords)
				if (room.x == new_room_position.x && room.y == new_room_position.y)
					is_empty = false;
			for (auto& room : bonus_rooms_coords)
				if (room.x == new_room_position.x && room.y == new_room_position.y)
					is_empty = false;
		} while (!is_empty);

		//spawning new room and corridor
		bonus_rooms_coords.push_back(new_room_position);
		if (is_horizontal)
			horizontal_corridors_coords.push_back(new_corridor_position);
		else
			vertical_corridors_coords.push_back(new_corridor_position);

		bonus_rooms_count--;
	}

	//Filling the floor[][]
	for (auto& room : rooms_coords)
		this->floor[room.x][room.y] = DEFAULT;

	this->floor[rooms_coords.front().x][rooms_coords.front().y] = FRONT;
	this->floor[rooms_coords.back().x][rooms_coords.back().y] = BACK;

	for (auto& bonus_room : bonus_rooms_coords)
		this->floor[bonus_room.x][bonus_room.y] = BONUS;

	for (auto& corridor : horizontal_corridors_coords)
		this->floor[corridor.x][corridor.y] = CORRIDOR_HORIZONTAL;

	for (auto& corridor : vertical_corridors_coords)
		this->floor[corridor.x][corridor.y] = CORRIDOR_VERTICAL;

	this->fillRoomsList();
	this->fillWallsList();
}

void Dungeon::render(sf::RenderTarget* target)
{
	for (auto& room : this->rooms)
		room->render(target);

	for (auto& wall : this->walls)
		target->draw(wall);
}
