///Constructors/Destructors
Particle::Particle(const sf::Vector2f& position, sf::Color color,
	const float& radius, const float& points_count, const float& angle,
	const int& fading_speed, const float& moving_speed)
	: fadingSpeed(fading_speed), movingSpeed(moving_speed)
{
	this->setPosition(position);
	this->setFillColor(color);
	this->setRadius(radius);
	this->setPointCount(points_count);
	this->setRotation(angle);
	this->setOrigin(radius, radius);
}

Particle::~Particle() { }

///Functions
void Particle::update(const float& dt)
{
	///Fading
	sf::Color color = this->getFillColor();
	color.a = color.a - this->fadingSpeed < 0 ? 0 : color.a - this->fadingSpeed;
	this->setFillColor(color);

	///Moving
	sf::Vector2f moving_dir;
	moving_dir.x = sin(this->getRotation() * 3.14159265358979323846f / 180.f);
	moving_dir.y = -cos(this->getRotation() * 3.14159265358979323846f / 180.f);
	this->move(moving_dir * this->movingSpeed * dt);
}
