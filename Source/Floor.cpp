///Initialization
void Floor::initVariables()
{
	this->number = 0;

	this->roomSize.x = 1000.f;
	this->roomSize.y = 1000.f;
	this->corridorLength = this->roomSize.x / 2.f;
	this->corridorWidth = this->roomSize.y / 4.f;

	this->centerPosition = sf::Vector2f(0.f, 0.f);
	this->startRoomPosition = mapCoordsToPixel(sf::Vector2i(25, 25));
	this->lastRoomPosition = this->startRoomPosition;

	this->floorColor = { 30, 30, 30 };
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

void Floor::openRoom(unsigned int index)
{
	for (auto& room : this->rooms)
		if (room->index == index)
			room->open();
}

void Floor::closeRoom(unsigned int index)
{
	for (auto& room : this->rooms)
		if (room->index == index)
			room->close();
}

void Floor::fillRoomsList(unsigned char cells[50][50])
{
	for (size_t i = 0; i < 50; i++)
	{
		for (size_t j = 0; j < 50; j++)
		{
			if (cells[i][j])
			{
				sf::Vector2f position(mapCoordsToPixel(sf::Vector2i(i, j)));
				sf::Vector2f size;

				size = cells[i][j] == RT_CORRIDOR_HORIZONTAL || cells[i][j] == RT_CORRIDOR_VERTICAL
					? cells[i][j] == RT_CORRIDOR_HORIZONTAL
						? sf::Vector2f(this->corridorLength, this->corridorWidth)
						: sf::Vector2f(this->corridorWidth, this->corridorLength)
					: this->roomSize;

				unsigned char nearby_cells[4] = { cells[i - 1][j], cells[i + 1][j], cells[i][j - 1], cells[i][j + 1] };

				this->rooms.push_back(new Room(position, size, floorColor, cells[i][j], nearby_cells));
				this->rooms.back()->floorCoord = sf::Vector2i(i, j);
				this->rooms.back()->index = this->rooms.size() - 1;
			}
		}
	}
	for (auto& room : this->rooms)
		if (room->shape.getPosition() == this->startRoomPosition || room->shape.getPosition() == this->lastRoomPosition)
			room->isVisited = true;
}

void Floor::generate()
{
	this->number++;

	///Lists the coordinates of rooms of each tag in the array cells[][]
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

	unsigned char cells[50][50] = { { RT_NONE } };

	while (main_rooms_count)
	{
		is_empty = false;
		do
		{
			///random direction for creating future room
			is_empty = true;
			new_direction = rand() % 4;
			if (new_direction == DIR_LEFT)
			{
				corridor_coords = room_coords = rooms_coords.back();
				corridor_coords.x -= 1;
				room_coords.x -= 2;
				is_horizontal = true;
			}
			else if (new_direction == DIR_RIGHT)
			{
				corridor_coords = room_coords = rooms_coords.back();
				corridor_coords.x += 1;
				room_coords.x += 2;
				is_horizontal = true;
			}
			else if (new_direction == DIR_UP)
			{
				corridor_coords = room_coords = rooms_coords.back();
				corridor_coords.y -= 1;
				room_coords.y -= 2;
				is_horizontal = false;
			}
			else if (new_direction == DIR_DOWN)
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
		selected_room_tag = rand() % 2 ? RT_HALL_MAIN : RT_HALL_SECONDARY;
		if (secondary_rooms_coords.size() == 0)
			selected_room_tag = RT_HALL_MAIN;
		else if (secondary_rooms_coords.size() >= rooms_coords.size() - 2)
			selected_room_tag = RT_HALL_SECONDARY;

		is_empty = false;
		do
		{
			///random selection room from the list
			if (selected_room_tag == RT_HALL_MAIN)
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
			if (new_direction == DIR_LEFT)
			{
				corridor_coords = room_coords = selected_room_coords;
				corridor_coords.x -= 1;
				room_coords.x -= 2;
				is_horizontal = true;
			}
			else if (new_direction == DIR_RIGHT)
			{
				corridor_coords = room_coords = selected_room_coords;
				corridor_coords.x += 1;
				room_coords.x += 2;
				is_horizontal = true;
			}
			else if (new_direction == DIR_UP)
			{
				corridor_coords = room_coords = selected_room_coords;
				corridor_coords.y -= 1;
				room_coords.y -= 2;
				is_horizontal = false;
			}
			else if (new_direction == DIR_DOWN)
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

	///Filling the cells[][]
	for (auto& room : rooms_coords)
		cells[room.x][room.y] = RT_HALL_MAIN;

	for (auto& secondary_room : secondary_rooms_coords)
		cells[secondary_room.x][secondary_room.y] = RT_HALL_SECONDARY;

	for (auto& corridor : horizontal_corridors_coords)
		cells[corridor.x][corridor.y] = RT_CORRIDOR_HORIZONTAL;

	for (auto& corridor : vertical_corridors_coords)
		cells[corridor.x][corridor.y] = RT_CORRIDOR_VERTICAL;

	///Getting the real center position of the cells
	sf::Vector2i minRoomsCoords(50, 50);
	sf::Vector2i maxRoomsCoords(0, 0);

	for (int i = 0; i < 50; i++)
		for (int j = 0; j < 50; j++)
			if (cells[i][j] != RT_NONE)
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

	this->fillRoomsList(cells);
}

void Floor::destroy()
{
	while (!this->rooms.empty())
	{
		delete this->rooms.back();
		this->rooms.pop_back();
	}
}

void Floor::render(sf::RenderTarget* target)
{
	for (auto& room : this->rooms)
		room->render(target);
}
