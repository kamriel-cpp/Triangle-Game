///Constructors/Destructors
AttackComponent::AttackComponent(const bool can_shoot, const bool can_pick, const bool can_dash,
	const float& shooting_cooldown, const float& picking_cooldown, const float& dashing_cooldown, float damage)
: canShoot(can_shoot), canPick(can_pick), canDash(can_dash)
, shootingCooldown(shooting_cooldown), pickingCooldown(picking_cooldown), dashingCooldown(dashing_cooldown)
, shootingTimer(shooting_cooldown), pickingTimer(picking_cooldown), dashingTimer(dashing_cooldown), damage(damage) { }

AttackComponent::~AttackComponent() { }

///Functions
void AttackComponent::shoot(std::list<Bullet*>* bullets, const sf::Vector2f& position, const float& rotation)
{
	if (this->canShoot)
	{
		if (this->shootingTimer > this->shootingCooldown)
		{
			this->shootingTimer = 0.f;

			///Debug print
			#ifdef DEBUG_CONSOLE_OUTPUT
			//std::cout << "Shoot" << std::endl;
			#endif

			bullets->push_back(new Bullet(position, sf::Color(250, 250, 50), 5.f, 30, 500.f, this->damage));
			bullets->back()->setRotation(rotation);
		}
	}
	else
	{
		std::cerr << "I_CANT_SHOOT_WHAT_ARE_YOU_DOING" << std::endl;
	}
}

void AttackComponent::pick()
{
	if (this->canPick)
	{
		if (this->pickingTimer > this->pickingCooldown)
		{
			this->pickingTimer = 0.f;

			///Debug print
			#ifdef DEBUG_CONSOLE_OUTPUT
			//std::cout << "Pick" << std::endl;
			#endif
		}
	}
	else
	{
		std::cerr << "I_CANT_PICK_WHAT_ARE_YOU_DOING" << std::endl;
	}
}

void AttackComponent::dash()
{
	if (this->canDash)
	{
		if (this->dashingTimer > this->dashingCooldown)
		{
			this->dashingTimer = 0.f;

			///Debug print
			#ifdef DEBUG_CONSOLE_OUTPUT
			//std::cout << "Dash" << std::endl;
			#endif
		}
	}
	else
	{
		std::cerr << "I_CANT_DASH_WHAT_ARE_YOU_DOING" << std::endl;
	}
}

void AttackComponent::update(const float& dt)
{
	if (this->canShoot)
		this->shootingTimer += dt;
	if (this->canPick)
		this->pickingTimer += dt;
	if (this->canDash)
		this->dashingTimer += dt;
}
