//Constructors/Destructors
Minimap::Minimap(Floor& floor, Player& player, const sf::RenderWindow* window)
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

	this->mapFactor = 0.01f;
	this->playerFactor = 20.f;

	this->windowOffset = sf::Vector2f(window->getDefaultView().getSize().x * 0.3f, -window->getDefaultView().getSize().y * 0.35f);
	this->floorOffset = floor.centerPosition;

	for (auto& room : floor.rooms)
	{
		this->floor.push_back(sf::RectangleShape());
		this->floor.back().setSize(room->shape.getSize() * this->mapFactor);
		this->floor.back().setOrigin(this->floor.back().getSize() / 2.f);
		this->floor.back().setPosition((room->shape.getPosition() - this->floorOffset) * this->mapFactor + this->windowOffset);
		if (room->shape.getSize() == floor.getRoomSize())
			this->floor.back().setFillColor(this->roomColor);
		else
			this->floor.back().setFillColor(this->corridorColor);
	}

	this->player.setPointCount(player.shape.getPointCount());
	this->player.setRadius(player.shape.getRadius() * this->playerFactor * this->mapFactor);
	this->player.setOrigin(sf::Vector2f(this->player.getRadius(), this->player.getRadius()));
	this->player.setPosition((player.shape.getPosition() - this->floorOffset) * this->mapFactor + this->windowOffset);
	this->player.setRotation(player.shape.getRotation());
	this->player.setFillColor(this->playerColor);
	this->player.setScale(sf::Vector2f(0.75f, 1.f));

	this->ptrPlayer = &player;
}

//Functions
void Minimap::update(const float& dt)
{
	this->player.setPosition((this->ptrPlayer->shape.getPosition() - this->floorOffset) * this->mapFactor + this->windowOffset);
	this->player.setRotation(this->ptrPlayer->shape.getRotation());
}

void Minimap::render(sf::RenderTarget* target)
{
	for (auto& shape : this->floor)
		target->draw(shape);
	target->draw(this->player);
}
