//Constructors/Destructors
Minimap::Minimap(Dungeon& dungeon, Player& player)
{
	this->roomColor.r = 150;
	this->roomColor.g = 150;
	this->roomColor.b = 150;

	this->corridorColor.r = 100;
	this->corridorColor.g = 100;
	this->corridorColor.b = 100;

	this->playerColor.r = 50;
	this->playerColor.g = 250;
	this->playerColor.b = 250;

	this->mapFactor = 0.25f;
	this->playerFactor = 20.f;

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

//Functions
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
