///Initialization
void Floor::initVariables()
{
	this->number = 0;

	this->roomSize.x = 1000.f;
	this->roomSize.y = 1000.f;
	this->corridorLength = this->roomSize.x / 2.f;
	this->corridorWidth = this->corridorLength / 2.f;
	this->wallThickness = 6.f;

	this->centerPosition = sf::Vector2f(0.f, 0.f);
	this->startRoomPosition = mapCoordsToPixel(sf::Vector2i(25, 25));
	this->lastRoomPosition = this->startRoomPosition;

	floorColor.r = 30;
	floorColor.g = 30;
	floorColor.b = 30;

	this->wallColor.r = 255;
	this->wallColor.g = 255;
	this->wallColor.b = 255;
}

///Constructors/Destructors
Floor::Floor()
{
	this->initVariables();
}

Floor::~Floor()
{
	while (!this->rooms.empty())
	{
		delete this->rooms.back();
		this->rooms.pop_back();
	}

	while (!this->walls.empty())
	{
		delete this->walls.back();
		this->walls.pop_back();
	}
}

///Functions
sf::Vector2f Floor::mapCoordsToPixel(const sf::Vector2i &point) const
{
	sf::Vector2f position;
	position.x = (this->corridorLength + this->roomSize.x) / 2.f * point.x;
	position.y = (this->corridorLength + this->roomSize.y) / 2.f * point.y;
	return position;
}

const sf::Vector2f& Floor::getRoomSize()
{
	return this->roomSize;
}

void Floor::setRoomSize(sf::Vector2f room_size)
{
	this->roomSize = room_size;
	this->corridorLength = this->roomSize.x / 2.f;
	this->corridorWidth = this->corridorLength / 2.f;
}

void Floor::closeRoom(unsigned int index)
{
	///Closing room at index
	for (auto& room : this->rooms)
	{
		if (room->index == index)
		{
			///LEFT
			this->walls.push_back(new sf::RectangleShape());
			this->walls.back()->setFillColor(this->wallColor);
			this->walls.back()->setSize(sf::Vector2f(this->wallThickness, (this->roomSize.y - this->corridorWidth) / 2.f + this->wallThickness));
			this->walls.back()->setPosition(room->leftSidePosition);
			this->walls.back()->setOrigin(this->walls.back()->getSize() / 2.f);

			///RIGHT
			this->walls.push_back(new sf::RectangleShape());
			this->walls.back()->setFillColor(this->wallColor);
			this->walls.back()->setSize(sf::Vector2f(this->wallThickness, (this->roomSize.y - this->corridorWidth) / 2.f + this->wallThickness));
			this->walls.back()->setPosition(room->rightSidePosition);
			this->walls.back()->setOrigin(this->walls.back()->getSize() / 2.f);

			///UP
			this->walls.push_back(new sf::RectangleShape());
			this->walls.back()->setFillColor(this->wallColor);
			this->walls.back()->setSize(sf::Vector2f((this->roomSize.x - this->corridorWidth) / 2.f + this->wallThickness, this->wallThickness));
			this->walls.back()->setPosition(room->upSidePosition);
			this->walls.back()->setOrigin(this->walls.back()->getSize() / 2.f);

			///DOWN
			this->walls.push_back(new sf::RectangleShape());
			this->walls.back()->setFillColor(this->wallColor);
			this->walls.back()->setSize(sf::Vector2f((this->roomSize.x - this->corridorWidth) / 2.f + this->wallThickness, this->wallThickness));
			this->walls.back()->setPosition(room->downSidePosition);
			this->walls.back()->setOrigin(this->walls.back()->getSize() / 2.f);

			///Deactivate current room
			room->is_active = false;
		}
	}
}

void Floor::destroyLastCreatedWalls()
{
	for (int i = 0; i < 4; i++)
	{
		if (!this->walls.empty())
		{
			delete this->walls.back();
			this->walls.pop_back();
		}
	}
}

void Floor::fillRoomsList(unsigned char floor[50][50])
{
	for (size_t i = 0; i < 50; i++)
	{
		for (size_t j = 0; j < 50; j++)
		{
			if (floor[i][j])
			{
				sf::Vector2f position(mapCoordsToPixel(sf::Vector2i(i, j)));
				sf::Vector2f size;

				if (floor[i][j] == CORRIDOR_HORIZONTAL)
					size = sf::Vector2f(this->corridorLength, this->corridorWidth);
				else if (floor[i][j] == CORRIDOR_VERTICAL)
					size = sf::Vector2f(this->corridorWidth, this->corridorLength);
				else
					size = this->roomSize;

				if (floor[i][j] == CORRIDOR_HORIZONTAL || floor[i][j] == CORRIDOR_VERTICAL)
					this->rooms.push_back(new Room(position, size, floorColor, floor[i][j]));
				else if (floor[i][j] == CORRIDOR_VERTICAL)
					this->rooms.push_back(new Room(position, size, floorColor, floor[i][j]));
				else
					this->rooms.push_back(new Room(position, size, floorColor, floor[i][j]));
				this->rooms.back()->floorCoord = sf::Vector2i(i, j);
				this->rooms.back()->index = this->rooms.size() - 1;
			}
		}
	}
	this->rooms.back()->is_active = false;
	this->rooms.front()->is_active = false;
}

void Floor::fillWallsList(unsigned char floor[50][50])
{
	for (size_t i = 0; i < 50; i++)
	{
		for (size_t j = 0; j < 50; j++)
		{
			if (floor[i][j])
			{
				sf::Vector2f position(mapCoordsToPixel(sf::Vector2i(i, j)));

				///LEFT
				if (floor[i][j] != CORRIDOR_HORIZONTAL)
				{
					this->walls.push_back(new sf::RectangleShape());
					this->walls.back()->setFillColor(this->wallColor);
					if (floor[i][j] == CORRIDOR_VERTICAL)
					{
						this->walls.back()->setSize(sf::Vector2f(this->wallThickness, this->corridorLength + this->wallThickness));
						this->walls.back()->setPosition(sf::Vector2f(
							position.x - this->corridorWidth / 2.f,
							position.y));
						this->walls.back()->setOrigin(this->walls.back()->getSize() / 2.f);
					}
					else
					{
						if (floor[i - 1][j] == NONE)
						{
							this->walls.back()->setSize(sf::Vector2f(this->wallThickness, this->roomSize.y + this->wallThickness));
							this->walls.back()->setPosition(sf::Vector2f(
								position.x - this->roomSize.x / 2.f,
								position.y));
							this->walls.back()->setOrigin(this->walls.back()->getSize() / 2.f);
						}
						else 
						{
							this->walls.back()->setSize(sf::Vector2f(this->wallThickness, (this->roomSize.y - this->corridorWidth) / 2.f + this->wallThickness));
							this->walls.back()->setPosition(sf::Vector2f(
								position.x - this->roomSize.x / 2.f,
								position.y - (this->corridorWidth / 2.f + (this->roomSize.y - this->corridorWidth) / 4.f)));
							this->walls.back()->setOrigin(this->walls.back()->getSize() / 2.f);

							this->walls.push_back(new sf::RectangleShape());
							this->walls.back()->setFillColor(this->wallColor);
							this->walls.back()->setSize(sf::Vector2f(this->wallThickness, (this->roomSize.y - this->corridorWidth) / 2.f + this->wallThickness));
							this->walls.back()->setPosition(sf::Vector2f(
								position.x - this->roomSize.x / 2.f,
								position.y + (this->corridorWidth / 2.f + (this->roomSize.y - this->corridorWidth) / 4.f)));
							this->walls.back()->setOrigin(this->walls.back()->getSize() / 2.f);
						}
					}
				}

				///RIGHT
				if (floor[i][j] != CORRIDOR_HORIZONTAL)
				{
					this->walls.push_back(new sf::RectangleShape());
					this->walls.back()->setFillColor(this->wallColor);
					if (floor[i][j] == CORRIDOR_VERTICAL)
					{
						this->walls.back()->setSize(sf::Vector2f(this->wallThickness, this->corridorLength + this->wallThickness));
						this->walls.back()->setPosition(sf::Vector2f(
							position.x + this->corridorWidth / 2.f,
							position.y));
						this->walls.back()->setOrigin(this->walls.back()->getSize() / 2.f);
					}
					else
					{
						if (floor[i + 1][j] == NONE)
						{
							this->walls.back()->setSize(sf::Vector2f(this->wallThickness, this->roomSize.y + this->wallThickness));
							this->walls.back()->setPosition(sf::Vector2f(
								position.x + this->roomSize.x / 2.f,
								position.y));
							this->walls.back()->setOrigin(this->walls.back()->getSize() / 2.f);
						}
						else 
						{
							this->walls.back()->setSize(sf::Vector2f(this->wallThickness, (this->roomSize.y - this->corridorWidth) / 2.f + this->wallThickness));
							this->walls.back()->setPosition(sf::Vector2f(
								position.x + this->roomSize.x / 2.f,
								position.y - (this->corridorWidth / 2.f + (this->roomSize.y - this->corridorWidth) / 4.f)));
							this->walls.back()->setOrigin(this->walls.back()->getSize() / 2.f);

							this->walls.push_back(new sf::RectangleShape());
							this->walls.back()->setFillColor(this->wallColor);
							this->walls.back()->setSize(sf::Vector2f(this->wallThickness, (this->roomSize.y - this->corridorWidth) / 2.f + this->wallThickness));
							this->walls.back()->setPosition(sf::Vector2f(
								position.x + this->roomSize.x / 2.f,
								position.y + (this->corridorWidth / 2.f + (this->roomSize.y - this->corridorWidth) / 4.f)));
							this->walls.back()->setOrigin(this->walls.back()->getSize() / 2.f);
						}
					}
				}

				///UP
				if (floor[i][j] != CORRIDOR_VERTICAL)
				{
					this->walls.push_back(new sf::RectangleShape());
					this->walls.back()->setFillColor(this->wallColor);
					if (floor[i][j] == CORRIDOR_HORIZONTAL)
					{
						this->walls.back()->setSize(sf::Vector2f(this->corridorLength + this->wallThickness, this->wallThickness));
						this->walls.back()->setPosition(sf::Vector2f(
							position.x,
							position.y - this->corridorWidth / 2.f));
						this->walls.back()->setOrigin(this->walls.back()->getSize() / 2.f);
					}
					else
					{
						if (floor[i][j - 1] == NONE)
						{
							this->walls.back()->setSize(sf::Vector2f(this->roomSize.x + this->wallThickness, this->wallThickness));
							this->walls.back()->setPosition(sf::Vector2f(
								position.x,
								position.y - this->roomSize.y / 2.f));
							this->walls.back()->setOrigin(this->walls.back()->getSize() / 2.f);
						}
						else 
						{
							this->walls.back()->setSize(sf::Vector2f((this->roomSize.x - this->corridorWidth) / 2.f + this->wallThickness, this->wallThickness));
							this->walls.back()->setPosition(sf::Vector2f(
								position.x - (this->corridorWidth / 2.f + (this->roomSize.x - this->corridorWidth) / 4.f),
								position.y - this->roomSize.y / 2.f));
							this->walls.back()->setOrigin(this->walls.back()->getSize() / 2.f);

							this->walls.push_back(new sf::RectangleShape());
							this->walls.back()->setFillColor(this->wallColor);
							this->walls.back()->setSize(sf::Vector2f((this->roomSize.x - this->corridorWidth) / 2.f + this->wallThickness, this->wallThickness));
							this->walls.back()->setPosition(sf::Vector2f(
								position.x + (this->corridorWidth / 2.f + (this->roomSize.x - this->corridorWidth) / 4.f),
								position.y - this->roomSize.y / 2.f));
							this->walls.back()->setOrigin(this->walls.back()->getSize() / 2.f);
						}
					}
				}

				///DOWN
				if (floor[i][j] != CORRIDOR_VERTICAL)
				{
					this->walls.push_back(new sf::RectangleShape());
					this->walls.back()->setFillColor(this->wallColor);
					if (floor[i][j] == CORRIDOR_HORIZONTAL)
					{
						this->walls.back()->setSize(sf::Vector2f(this->corridorLength + this->wallThickness, this->wallThickness));
						this->walls.back()->setPosition(sf::Vector2f(
							position.x,
							position.y + this->corridorWidth / 2.f));
						this->walls.back()->setOrigin(this->walls.back()->getSize() / 2.f);
					}
					else
					{
						if (floor[i][j + 1] == NONE)
						{
							this->walls.back()->setSize(sf::Vector2f(this->roomSize.x + this->wallThickness, this->wallThickness));
							this->walls.back()->setPosition(sf::Vector2f(
								position.x,
								position.y + this->roomSize.y / 2.f));
							this->walls.back()->setOrigin(this->walls.back()->getSize() / 2.f);
						}
						else 
						{
							this->walls.back()->setSize(sf::Vector2f((this->roomSize.x - this->corridorWidth) / 2.f + this->wallThickness, this->wallThickness));
							this->walls.back()->setPosition(sf::Vector2f(
								position.x - (this->corridorWidth / 2.f + (this->roomSize.x - this->corridorWidth) / 4.f),
								position.y + this->roomSize.y / 2.f));
							this->walls.back()->setOrigin(this->walls.back()->getSize() / 2.f);

							this->walls.push_back(new sf::RectangleShape());
							this->walls.back()->setFillColor(this->wallColor);
							this->walls.back()->setSize(sf::Vector2f((this->roomSize.x - this->corridorWidth) / 2.f + this->wallThickness, this->wallThickness));
							this->walls.back()->setPosition(sf::Vector2f(
								position.x + (this->corridorWidth / 2.f + (this->roomSize.x - this->corridorWidth) / 4.f),
								position.y + this->roomSize.y / 2.f));
							this->walls.back()->setOrigin(this->walls.back()->getSize() / 2.f);
						}
					}
				}
			}
		}
	}
}

void Floor::generate()
{
	this->number++;

	///Lists the coordinates of rooms of each tag in the array floor[][]
	std::list<sf::Vector2i> rooms_coords;
	std::list<sf::Vector2i> secondary_rooms_coords;
	std::list<sf::Vector2i> horizontal_corridors_coords;
	std::list<sf::Vector2i> vertical_corridors_coords;

	///creating a start room
	rooms_coords.push_back(sf::Vector2i(25, 25));

	unsigned int main_rooms_count = rand() % 2 + 4;
	unsigned int secondary_rooms_count = rand() % 2 + 5;
	unsigned int new_direction = 4;
	sf::Vector2i room_coords(25, 25);
	sf::Vector2i corridor_coords;
	bool is_horizontal;
	bool is_empty;

	unsigned char floor[50][50] = { { NONE } };

	while (main_rooms_count)
	{
		is_empty = false;
		do
		{
			///random direction for creating future room
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

		///recording new rooms and corridors coordinates
		rooms_coords.push_back(room_coords);
		if (is_horizontal)
			horizontal_corridors_coords.push_back(corridor_coords);
		else
			vertical_corridors_coords.push_back(corridor_coords);

		this->lastRoomPosition = this->mapCoordsToPixel(room_coords);

		main_rooms_count--;
	}

	while (secondary_rooms_count)
	{
		room_coords = sf::Vector2i(25, 25);
		sf::Vector2i selected_room_coords;
		unsigned int selected_room_tag;

		///random selection type of the room
		selected_room_tag = rand() % 2 ? MAIN : SECONDARY;
		if (secondary_rooms_coords.size() == 0)
			selected_room_tag = MAIN;
		else if (secondary_rooms_coords.size() >= rooms_coords.size() - 2)
			selected_room_tag = SECONDARY;

		is_empty = false;
		do
		{
			///random selection room from the list
			if (selected_room_tag == MAIN)
			{
				auto room = rooms_coords.begin();
				std::advance(room, rand() % (rooms_coords.size() - 2) + 1);
				selected_room_coords = sf::Vector2i((*room).x, (*room).y);
			}
			else
			{
				auto room = secondary_rooms_coords.begin();
				std::advance(room, rand() % secondary_rooms_coords.size());
				selected_room_coords = sf::Vector2i((*room).x, (*room).y);
			}

			///random selection of the direction for creating the future room
			///and recording the received coordinates in room_coords
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

			///comparing the coordinates of each room from the lists with the new coordinates
			///and if they coincide, then the cycle starts again
			for (auto& room : rooms_coords)
				if (room.x == room_coords.x && room.y == room_coords.y)
					is_empty = false;
			for (auto& room : secondary_rooms_coords)
				if (room.x == room_coords.x && room.y == room_coords.y)
					is_empty = false;
		} while (!is_empty);

		///recording new rooms and corridors coordinates
		secondary_rooms_coords.push_back(room_coords);
		if (is_horizontal)
			horizontal_corridors_coords.push_back(corridor_coords);
		else
			vertical_corridors_coords.push_back(corridor_coords);

		secondary_rooms_count--;
	}

	///Filling the floor[][]
	for (auto& room : rooms_coords)
		floor[room.x][room.y] = MAIN;

	floor[rooms_coords.front().x][rooms_coords.front().y] = FRONT;
	floor[rooms_coords.back().x][rooms_coords.back().y] = BACK;

	for (auto& secondary_room : secondary_rooms_coords)
		floor[secondary_room.x][secondary_room.y] = SECONDARY;

	for (auto& corridor : horizontal_corridors_coords)
		floor[corridor.x][corridor.y] = CORRIDOR_HORIZONTAL;

	for (auto& corridor : vertical_corridors_coords)
		floor[corridor.x][corridor.y] = CORRIDOR_VERTICAL;

	///Getting the real center position of the floor
	sf::Vector2i minRoomsCoords(50, 50);
	sf::Vector2i maxRoomsCoords(0, 0);

	for (int i = 0; i < 50; i++)
		for (int j = 0; j < 50; j++)
			if (floor[i][j] != NONE)
			{
				if (minRoomsCoords.x > i)
					minRoomsCoords.x = i;
				if (minRoomsCoords.y > j)
					minRoomsCoords.y = j;
				if (maxRoomsCoords.x < i)
					maxRoomsCoords.x = i;
				if (maxRoomsCoords.y < j)
					maxRoomsCoords.y = j;
			}

	this->centerPosition = (this->mapCoordsToPixel(maxRoomsCoords) + this->mapCoordsToPixel(minRoomsCoords)) / 2.f;

	this->fillRoomsList(floor);
	this->fillWallsList(floor);
}

void Floor::destroy()
{
	while (!this->rooms.empty())
	{
		delete this->rooms.back();
		this->rooms.pop_back();
	}

	while (!this->walls.empty())
	{
		delete this->walls.back();
		this->walls.pop_back();
	}
}

void Floor::render(sf::RenderTarget* target)
{
	for (auto& room : this->rooms)
		room->render(target);

	for (auto& wall : this->walls)
		target->draw(*wall);
}
