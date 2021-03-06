///Constructors/Destructors
ShootComponent::ShootComponent() : cooldown(1.f), timer(0.f) { }

ShootComponent::~ShootComponent() { }

///Functions
void ShootComponent::shoot(std::list<Bullet*>* bullets,
		Unit* caster, sf::Color color,
		const sf::Vector2f& position, const float& rotation,
		const int& spread, const int& damage,
		int bullets_per_shoot,
		const float& bullet_speed, const float& bullet_radius)
{
	if (this->timer >= this->cooldown)
	{
		this->timer = 0.f;

		#ifdef DEBUG_ATTACK_OUTPUT
		std::cout << "SHOOTCOMPONENT::SHOOTING" << std::endl;
		#endif

		while (bullets_per_shoot)
		{
			float _rotation = (int)spread != 0 ? rotation + (rand() % (int)spread - spread / 2.f) : rotation;

			bullets->push_back(new Bullet(caster, position, _rotation,
				color, damage,
				bullet_speed, bullet_radius));
			
			bullets_per_shoot--;
		}
	}
}

void ShootComponent::update(const float& dt, const float& shoots_per_second)
{
	this->cooldown = 1 / shoots_per_second;
	this->timer = this->timer + dt > this->cooldown ? this->cooldown : this->timer + dt;
	this->reloadPercent = this->timer * 100 / this->cooldown;
}
