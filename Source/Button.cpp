///Constructors/Destructors
Button::Button(float x, float y,
	float offset_x, float offset_y, float width, float height,
	sf::Font* font, std::string text, std::string tag, unsigned char character_size,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color fill_idle_color, sf::Color fill_hover_color, sf::Color fill_active_color,
	sf::Color outline_idle_color, sf::Color outline_hover_color, sf::Color outline_active_color,
	float outline_thickness)
	: font(font), buttonState(BTN_IDLE)
	, textIdleColor(text_idle_color), textHoverColor(text_hover_color), textActiveColor(text_active_color)
	, fillIdleColor(fill_idle_color), fillHoverColor(fill_hover_color), fillActiveColor(fill_active_color)
	, outlineIdleColor(outline_idle_color), outlineHoverColor(outline_hover_color), outlineActiveColor(outline_active_color)
	, tag(tag), wasPressed(false)
{
	this->buttonState = BTN_IDLE;

	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(fill_idle_color);
	this->shape.setOutlineThickness(outline_thickness);
	this->shape.setOutlineColor(outline_idle_color);

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setOrigin(
		this->shape.getGlobalBounds().width  / 2.f,
		this->shape.getGlobalBounds().height / 2.f);

	this->text.setFont(*this->font);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize(character_size);
	this->text.setString(text);

	this->text.setPosition(sf::Vector2f(x + offset_x, y + offset_y));
	this->text.setOrigin(
		this->text.getGlobalBounds().width  / 2.f,
		this->text.getGlobalBounds().height / 2.f);
}

///Accessors
const bool Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
		return true;
	return false;
}

///Functions
void Button::update(const sf::Vector2f& mousePos)
{
	/*Update the booleans for hover and pressed*/

	///Idle
	this->buttonState = BTN_IDLE;

	///Hover
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;

		///Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			this->buttonState = BTN_ACTIVE;
	}

	switch (this->buttonState)
	{
	case BTN_IDLE: 
		this->text.setFillColor(this->textIdleColor);
		this->shape.setFillColor(this->fillIdleColor);
		this->shape.setOutlineColor(this->outlineIdleColor);
		break;
	case BTN_HOVER: 
		this->text.setFillColor(this->textHoverColor);
		this->shape.setFillColor(this->fillHoverColor);
		this->shape.setOutlineColor(this->outlineHoverColor);
		break;
	case BTN_ACTIVE: 
		this->text.setFillColor(this->textActiveColor);
		this->shape.setFillColor(this->fillActiveColor);
		this->shape.setOutlineColor(this->outlineActiveColor);
		break;
	default:
		std::cerr << "ERROR::BUTTON::UNKNOWN_STATE_DETECTED::" << std::to_string(this->buttonState) << std::endl;
		throw;
	}
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->text);
}
