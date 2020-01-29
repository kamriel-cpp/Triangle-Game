///Constructors/Destructors
Bullet::Bullet(const sf::Vector2f& position, const float& rotation,
	const sf::Color& color, const int& damage,
	const float& moving_speed, const float& radius)
{
	this->setPosition(position);
	this->setRotation(rotation);
	this->setFillColor(color);
	this->damage = damage;
	this->movingSpeed = moving_speed;
	this->setRadius(radius);
	this->setOrigin(radius, radius);
}

///Functions
void Bullet::explode(std::list<Effect*>* effects)
{
	effects->push_back(new Explosion(
		this->getPosition(), 1.f,
		this->getFillColor(), 8,
		this->getRadius() / 3.f, this->getRadius() / 2.f,
		3, 4,
		5, 75.f));
	effects->push_back(new Explosion(
		this->getPosition(), 1.f,
		this->getFillColor(), 10,
		this->getRadius() / 4.f, this->getRadius() / 3.f,
		3, 4,
		6, 100.f));
}

void Bullet::update(const float& dt)
{
	sf::Vector2f move_factor;
	move_factor.x = this->movingSpeed * dt * sin(this->getRotation() * 3.14159265358979323846f / 180.f);
	move_factor.y = this->movingSpeed * dt * -cos(this->getRotation() * 3.14159265358979323846f / 180.f);
	this->move(move_factor);
}
