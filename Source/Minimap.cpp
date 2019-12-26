//Constructors/Destructors
Minimap::Minimap()
{

}

//Functions
void Minimap::render(sf::RenderTarget* target)
{
	for (auto& shape : this->shapes)
		target->draw(shape);
}
