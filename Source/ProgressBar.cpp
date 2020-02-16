///Constructors/Destructors
ProgressBar::ProgressBar(sf::Font* font, const unsigned int& character_size,
	const sf::Vector2f& position, const sf::Vector2f& size,
	const float& outline_thickness, const int& border_percent,
	const sf::Color& back_fill_color, const sf::Color& back_outline_color,
	const sf::Color& front_base_color, const sf::Color& front_secondary_color,
	const sf::Color& info_base_color, const sf::Color& info_secondary_color,
	const int& info_type)
	: borderPercent(border_percent), barBaseColor(front_base_color), barSecondaryColor(front_secondary_color)
	, infoBaseColor(info_base_color), infoSecondaryColor(info_secondary_color), infoType(info_type)
{
	this->backShape.setSize(size);
	this->backShape.setOrigin(0.f, this->backShape.getSize().y / 2.f);
	this->backShape.setFillColor(back_fill_color);
	this->backShape.setOutlineColor(back_outline_color);
	this->backShape.setOutlineThickness(outline_thickness);
	this->backShape.setPosition(position);

	this->frontShape.setSize(size);
	this->frontShape.setOrigin(0.f, this->frontShape.getSize().y / 2.f);
	this->frontShape.setFillColor(front_base_color);
	this->frontShape.setPosition(position);

	this->info = sf::Text("BARINFO", *font, character_size);
	this->info.setOrigin(0.f, (this->info.getGlobalBounds().height / 2.f) + this->info.getCharacterSize() / 4.f);
	this->info.setPosition(position.x + outline_thickness, position.y);
	this->info.setFillColor(info_base_color);
}

ProgressBar::~ProgressBar() { }

///Functions
void ProgressBar::update(const float& current_value, const float& max_value)
{
	int progress_percent = current_value * 100 / max_value;

	this->frontShape.setSize(sf::Vector2f(this->backShape.getSize().x * progress_percent / 100.f, this->backShape.getSize().y));
	
	if (progress_percent >= this->borderPercent)
	{
		this->frontShape.setFillColor(this->barBaseColor);
		this->info.setFillColor(this->infoBaseColor);
	}
	else
	{
		this->frontShape.setFillColor(this->barSecondaryColor);
		this->info.setFillColor(this->infoSecondaryColor);
	}

	if (this->infoType == IT_VALUE)
		this->info.setString(std::to_string((int)current_value) + '/' + std::to_string((int)max_value));
	else if (this->infoType == IT_PERCENT)
		this->info.setString(std::to_string((int)progress_percent) + '%');

	this->info.setOrigin(0.f, (this->info.getGlobalBounds().height / 2.f) + this->info.getCharacterSize() / 4.f);
}

void ProgressBar::update(const float& progress_percent)
{
	this->frontShape.setSize(sf::Vector2f(this->backShape.getSize().x * progress_percent / 100.f, this->backShape.getSize().y));
	
	if (progress_percent >= this->borderPercent)
	{
		this->frontShape.setFillColor(this->barBaseColor);
		this->info.setFillColor(this->infoBaseColor);
	}
	else
	{
		this->frontShape.setFillColor(this->barSecondaryColor);
		this->info.setFillColor(this->infoSecondaryColor);
	}

	this->info.setString(std::to_string((int)progress_percent) + '%');

	this->info.setOrigin(0.f, (this->info.getGlobalBounds().height / 2.f) + this->info.getCharacterSize() / 4.f);
}

void ProgressBar::render(sf::RenderTarget* target)
{
	target->draw(this->backShape);
	target->draw(this->frontShape);
	target->draw(this->info);
}
