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

	this->centerPosition = sf::Vector2f(0.f, 0.f);
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
					this->rooms.push_back(new Room(position, size, this->floorColor, this->floor[i][j]));
				else if (this->floor[i][j] == CORRIDOR_VERTICAL)
					this->rooms.push_back(new Room(position, size, this->floorColor, this->floor[i][j]));
				else
					this->rooms.push_back(new Room(position, size, this->floorColor, this->floor[i][j]));
				this->rooms.back()->floorCoord = sf::Vector2u(i, j);
				this->rooms.back()->index = this->rooms.size() - 1;
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
	//Lists the coordinates of rooms of each tag in the array floor[][]
	std::list<sf::Vector2u> rooms_coords;
	std::list<sf::Vector2u> secondary_rooms_coords;
	std::list<sf::Vector2u> horizontal_corridors_coords;
	std::list<sf::Vector2u> vertical_corridors_coords;

	//creating a start room
	rooms_coords.push_back(sf::Vector2u(25, 25));

	unsigned int main_rooms_count = rand() % 2 + 4;
	unsigned int secondary_rooms_count = rand() % 2 + 5;
	unsigned int new_direction = 4;
	sf::Vector2u room_coords(25, 25);
	sf::Vector2u corridor_coords;
	bool is_horizontal;
	bool is_empty;

	while (main_rooms_count)
	{
		is_empty = false;
		do
		{
			//random direction for creating future room
			is_empty = true;
			new_direction = rand() % 4;
			if (new_direction == LEFT)
			{
				corridor_coords = room_coords = rooms_coords.back();
				corridor_coords.x -= 1;
				room_coords.x -= 2;
				is_horizontal = true;
			}
			else if (new_direction == RIGHT)
			{
				corridor_coords = room_coords = rooms_coords.back();
				corridor_coords.x += 1;
				room_coords.x += 2;
				is_horizontal = true;
			}
			else if (new_direction == UP)
			{
				corridor_coords = room_coords = rooms_coords.back();
				corridor_coords.y -= 1;
				room_coords.y -= 2;
				is_horizontal = false;
			}
			else if (new_direction == DOWN)
			{
				corridor_coords = room_coords = rooms_coords.back();
				corridor_coords.y += 1;
				room_coords.y += 2;
				is_horizontal = false;
			}
			for (auto& room : rooms_coords)
				if (room.x == room_coords.x && room.y == room_coords.y)
					is_empty = false;
		} while (!is_empty);

		//recording new rooms and corridors coordinates
		rooms_coords.push_back(room_coords);
		if (is_horizontal)
			horizontal_corridors_coords.push_back(corridor_coords);
		else
			vertical_corridors_coords.push_back(corridor_coords);

		this->lastRoomPosition.x = (this->corridorLength + this->roomSize.x) / 2.f * room_coords.x - (this->corridorLength + this->roomSize.x) / 2.f * 25.f + this->centerPosition.x;
		this->lastRoomPosition.y = (this->corridorLength + this->roomSize.y) / 2.f * room_coords.y - (this->corridorLength + this->roomSize.y) / 2.f * 25.f + this->centerPosition.y;

		main_rooms_count--;
	}

	while (secondary_rooms_count)
	{
		room_coords = sf::Vector2u(25, 25);
		sf::Vector2u selected_room_coords;
		unsigned int selected_room_tag;

		//random selection type of the room
		selected_room_tag = rand() % 2 ? MAIN : SECONDARY;
		if (secondary_rooms_coords.size() == 0)
			selected_room_tag = MAIN;
		else if (secondary_rooms_coords.size() >= rooms_coords.size() - 2)
			selected_room_tag = SECONDARY;

		is_empty = false;
		do
		{
			//random selection room from the list
			if (selected_room_tag == MAIN)
			{
				auto room = rooms_coords.begin();
				std::advance(room, rand() % (rooms_coords.size() - 2) + 1);
				selected_room_coords = sf::Vector2u((*room).x, (*room).y);
			}
			else
			{
				auto room = secondary_rooms_coords.begin();
				std::advance(room, rand() % secondary_rooms_coords.size());
				selected_room_coords = sf::Vector2u((*room).x, (*room).y);
			}

			//random selection of the direction for creating the future room
			//and recording the received coordinates in room_coords
			is_empty = true;
			new_direction = rand() % 4;
			if (new_direction == LEFT)
			{
				corridor_coords = room_coords = selected_room_coords;
				corridor_coords.x -= 1;
				room_coords.x -= 2;
				is_horizontal = true;
			}
			else if (new_direction == RIGHT)
			{
				corridor_coords = room_coords = selected_room_coords;
				corridor_coords.x += 1;
				room_coords.x += 2;
				is_horizontal = true;
			}
			else if (new_direction == UP)
			{
				corridor_coords = room_coords = selected_room_coords;
				corridor_coords.y -= 1;
				room_coords.y -= 2;
				is_horizontal = false;
			}
			else if (new_direction == DOWN)
			{
				corridor_coords = room_coords = selected_room_coords;
				corridor_coords.y += 1;
				room_coords.y += 2;
				is_horizontal = false;
			}

			//comparing the coordinates of each room from the lists with the new coordinates
			//and if they coincide, then the cycle starts again
			for (auto& room : rooms_coords)
				if (room.x == room_coords.x && room.y == room_coords.y)
					is_empty = false;
			for (auto& room : secondary_rooms_coords)
				if (room.x == room_coords.x && room.y == room_coords.y)
					is_empty = false;
		} while (!is_empty);

		//recording new rooms and corridors coordinates
		secondary_rooms_coords.push_back(room_coords);
		if (is_horizontal)
			horizontal_corridors_coords.push_back(corridor_coords);
		else
			vertical_corridors_coords.push_back(corridor_coords);

		secondary_rooms_count--;
	}

	//Filling the floor[][]
	for (auto& room : rooms_coords)
		this->floor[room.x][room.y] = MAIN;

	this->floor[rooms_coords.front().x][rooms_coords.front().y] = FRONT;
	this->floor[rooms_coords.back().x][rooms_coords.back().y] = BACK;

	for (auto& secondary_room : secondary_rooms_coords)
		this->floor[secondary_room.x][secondary_room.y] = SECONDARY;

	for (auto& corridor : horizontal_corridors_coords)
		this->floor[corridor.x][corridor.y] = CORRIDOR_HORIZONTAL;

	for (auto& corridor : vertical_corridors_coords)
		this->floor[corridor.x][corridor.y] = CORRIDOR_VERTICAL;

	this->fillRoomsList();
	this->fillWallsList();

	//DEBUG FEATURE
	/*for (auto& room : this->rooms)
	{
		std::cout << room->centerPosition.x << ' ' << room->centerPosition.y << ' ';
		if (room->tag == FRONT)
			std::cout << "FRONT";
		else if (room->tag == BACK)
			std::cout << "BACK";
		else if (room->tag == MAIN)
			std::cout << "MAIN";
		else if (room->tag == SECONDARY)
			std::cout << "SECONDARY";
		else if (room->tag == CORRIDOR_HORIZONTAL)
			std::cout << "CORRIDOR_HORIZONTAL";
		else if (room->tag == CORRIDOR_VERTICAL)
			std::cout << "CORRIDOR_VERTICAL";
		std::cout << std::endl;
	}*/
}

void Dungeon::render(sf::RenderTarget* target)
{
	for (auto& room : this->rooms)
		room->render(target);

	for (auto& wall : this->walls)
		target->draw(wall);
}
