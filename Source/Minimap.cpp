//Constructors/Destructors
Minimap::Minimap()
{
	this->roomColor.r = 86;
	this->roomColor.g = 156;
	this->roomColor.b = 214;

	this->corridorColor.r = 156;
	this->corridorColor.g = 156;
	this->corridorColor.b = 156;
}

//Functions
void Minimap::render(sf::RenderTarget* target)
{
	for (auto& shape : this->shapes)
		target->draw(shape);
}
