///Constructors/Destructors
StatusBar::StatusBar(const sf::Vector2f& position, const sf::Vector2f& size, const float& border,
	const sf::Color& back_color, const sf::Color& front_base_color, const sf::Color& front_secondary_color)
	: border(border), baseColor(front_base_color), secondaryColor(front_secondary_color)
{
	this->backShape.setSize(size);
	this->backShape.setOrigin(0.f, this->backShape.getSize().y / 2.f);
	this->backShape.setFillColor(back_color);
	this->backShape.setOutlineColor(back_color);
	this->backShape.setOutlineThickness(2.5f);
	this->backShape.setPosition(position);

	this->frontShape.setSize(size);
	this->frontShape.setOrigin(0.f, this->frontShape.getSize().y / 2.f);
	this->frontShape.setFillColor(front_base_color);
	this->frontShape.setPosition(position);
}

StatusBar::~StatusBar() { }

///Functions
void StatusBar::update(const float& modifier)
{
	this->frontShape.setSize(sf::Vector2f(this->backShape.getSize().x * modifier, this->backShape.getSize().y));
	if (modifier < border)
		this->frontShape.setFillColor(this->secondaryColor);
	else
		this->frontShape.setFillColor(this->baseColor);
}

void StatusBar::render(sf::RenderTarget* target)
{
	target->draw(this->backShape);
	target->draw(this->frontShape);
}
