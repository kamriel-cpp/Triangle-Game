//Constructors/Destructors
Triangle::Triangle()
{
	this->defaultColor.r = 255;
	this->defaultColor.g = 255;
	this->defaultColor.b = 255;
	this->defaultRadius = 20.f;
	this->defaultOrigin.x = this->defaultRadius;
	this->defaultOrigin.y = this->defaultRadius * 0.75f;
	this->defaultScale.x = 0.75f;
	this->defaultScale.y = 1.f;
	this->defaultPointCount = 3;

	this->shape.setFillColor(this->defaultColor);
	this->shape.setRadius(this->defaultRadius);
	this->shape.setOrigin(this->defaultOrigin);
	this->shape.setScale(this->defaultScale);
	this->shape.setPointCount(this->defaultPointCount);
}

//Functions
void Triangle::update(const float& dt)
{
	
}

void Triangle::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
