//Constructors/Destructors
Minimap::Minimap()
{
	this->roomColor.r = 86;
	this->roomColor.g = 156;
	this->roomColor.b = 214;

	this->corridorColor.r = 156;
	this->corridorColor.g = 156;
	this->corridorColor.b = 156;

	this->playerColor.r = 255;
	this->playerColor.g = 255;
	this->playerColor.b = 255;

	this->mapFactor = 0.25f;
	this->playerFactor = 10.f;
}

//Functions
void Minimap::initShapes(Dungeon& dungeon, Player& player)
{
	for (auto& room : dungeon.rooms)
	{
		this->dungeon.push_back(sf::RectangleShape());
		this->dungeon.back().setSize(room->shape.getSize() * this->mapFactor);
		this->dungeon.back().setOrigin(this->dungeon.back().getSize() / 2.f);
		this->dungeon.back().setPosition(room->shape.getPosition() * this->mapFactor);
		if (room->shape.getSize() == dungeon.getRoomSize())
			this->dungeon.back().setFillColor(this->roomColor);
		else
			this->dungeon.back().setFillColor(this->corridorColor);
	}
	this->player.setPointCount(player.shape.getPointCount());
	this->player.setRadius(player.shape.getRadius() * this->playerFactor * this->mapFactor);
	this->player.setOrigin(sf::Vector2f(this->player.getRadius(), this->player.getRadius()));
	this->player.setPosition(player.shape.getPosition() * this->mapFactor);
	this->player.setRotation(player.shape.getRotation());
	this->player.setFillColor(this->playerColor);
	this->player.setScale(sf::Vector2f(0.75f, 1.f));

	this->ptrPlayer = &player;
}

void Minimap::update(const float& dt)
{
	this->player.setPosition(this->ptrPlayer->shape.getPosition() * this->mapFactor);
	this->player.setRotation(this->ptrPlayer->shape.getRotation());
}

void Minimap::render(sf::RenderTarget* target)
{
	for (auto& shape : this->dungeon)
		target->draw(shape);
	target->draw(this->player);
}
