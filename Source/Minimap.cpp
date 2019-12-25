//Constructors/Destructors
Minimap::Minimap()
{

}


//Functions
void Minimap::setShapesList(const std::list<sf::RectangleShape> shapes)
{
	for (auto& shape : shapes)
	{
		this->shapes.push_back(sf::RectangleShape());
		this->shapes.back().setSize(shape.getSize());
		this->shapes.back().setPosition(shape.getPosition());
		this->shapes.back().setOrigin(shape.getOrigin());
		this->shapes.back().setFillColor(shape.getOutlineColor());
	}
}

void Minimap::render(sf::RenderTarget* target)
{
	for (auto& shape : this->shapes)
		target->draw(shape);
}
