///Constructors/Destructors
Bullet::Bullet(Unit* caster, const sf::Vector2f& position, const float& rotation,
	const sf::Color& color, const int& damage,
	const float& moving_speed, const float& radius)
	: caster(caster), damage(damage), movingSpeed(moving_speed)
{
	this->setPosition(position);
	this->setRotation(rotation);
	this->setFillColor(color);
	this->setRadius(radius);
	this->setOrigin(radius, radius);

	///Maybe it can be used in future, but now it looks like a sh...
	//this->setScale(sf::Vector2f(sqrt(200.f) / sqrt(moving_speed), 1.f));
}

Bullet::~Bullet()
{
	this->caster = nullptr;
}

///Functions
void Bullet::explode(std::list<Effect*>* effects)
{
	effects->push_back(new Explosion(
		this->getPosition(), 1.f,
		this->getFillColor(), 5,
		this->getRadius() / 4.f, this->getRadius() / 2.f,
		3, 4,
		this->movingSpeed / (20 * sqrt(this->getRadius())), this->movingSpeed / (17.5 * sqrt(this->getRadius())),
		this->movingSpeed * (0.1 * sqrt(this->getRadius())), this->movingSpeed * (0.2 * sqrt(this->getRadius()))));
}

void Bullet::update(const float& dt)
{
	sf::Vector2f move_factor;
	move_factor.x = this->movingSpeed * dt * sin(this->getRotation() * 3.14159265358979323846f / 180.f);
	move_factor.y = this->movingSpeed * dt * -cos(this->getRotation() * 3.14159265358979323846f / 180.f);
	this->move(move_factor);
}
