///Constructors/Destructors
ShootComponent::ShootComponent()
: cooldown(0.f), timer(0.f) { }

ShootComponent::~ShootComponent() { }

///Functions
void ShootComponent::shoot(std::list<Bullet*>* bullets,
		const sf::Vector2f& position, const float& rotation,
		const int& spread, const int& damage,
		int bullets_per_shoot,
		const float& bullet_speed, const float& bullet_radius)
{
	if (this->timer > this->cooldown)
	{
		this->timer = 0.f;

		///Debug print
		#ifdef DEBUG_ATTACK_OUTPUT
		std::cout << "Shoot" << std::endl;
		#endif

		while (bullets_per_shoot)
		{
			float _rotation = (int)spread != 0 ? rotation + (rand() % (int)spread - spread / 2.f) : rotation;

			bullets->push_back(new Bullet(position, _rotation,
				sf::Color(250, 250, 50), damage,
				bullet_speed, bullet_radius));
			
			bullets_per_shoot--;
		}
	}
}

void ShootComponent::update(const float& dt, const float& cooldown)
{
	this->cooldown = cooldown;
	this->timer += dt;
}
