///Blink Constructors/Destructors
Blink::Blink(sf::Shape* target, const sf::Color& default_color, float fading_speed, float effect_duration)
	: baseFillColor(default_color), currentColor(target->getFillColor()), fadingSpeed(fading_speed), duration(effect_duration), timer(0.f)
{
	this->target = target;
	this->done = false;
}

Blink::~Blink()
{
	this->target = nullptr;
}

///Blink Functions
void Blink::update(const float& dt)
{
	this->done = false;
	this->timer += dt;

	if (this->timer < this->duration / 2.f)
	{
		this->currentColor.r = this->currentColor.r + this->fadingSpeed > 255 ? 255 : this->currentColor.r + this->fadingSpeed;
		this->currentColor.g = this->currentColor.g + this->fadingSpeed > 255 ? 255 : this->currentColor.g + this->fadingSpeed;
		this->currentColor.b = this->currentColor.b + this->fadingSpeed > 255 ? 255 : this->currentColor.b + this->fadingSpeed;

		this->target->setFillColor(this->currentColor);
	}
	else if (this->timer < this->duration)
	{
		this->currentColor.r = this->currentColor.r - this->fadingSpeed < this->baseFillColor.r ? this->baseFillColor.r : this->currentColor.r - this->fadingSpeed;
		this->currentColor.g = this->currentColor.g - this->fadingSpeed < this->baseFillColor.g ? this->baseFillColor.g : this->currentColor.g - this->fadingSpeed;
		this->currentColor.b = this->currentColor.b - this->fadingSpeed < this->baseFillColor.b ? this->baseFillColor.b : this->currentColor.b - this->fadingSpeed;

		this->target->setFillColor(this->currentColor);
	}
	else
	{
		this->done = true;
	}
}

void Blink::render(sf::RenderTarget* target)
{

}

///Explosion Constructors/Destructors
Explosion::Explosion(const sf::Vector2f& center, float radius,
	const sf::Color& particles_color, int particles_count,
	float particles_min_radius, float particles_max_radius,
	int particles_min_points_count, int particles_max_points_count,
	int fading_speed, float moving_speed)
	: fadingSpeed(fading_speed), movingSpeed(moving_speed)
{
	this->done = false;
	radius = radius < 1.f ? 1.f : radius;

	while (particles_count)
	{
		float particles_radius = particles_max_radius > 1.f ? (rand() % (int)(particles_max_radius + 1.f - particles_min_radius) + particles_min_radius) : 1.f;
		int particles_points_count = particles_max_points_count > 1 ? (rand() % (particles_max_points_count + 1 - particles_min_points_count) + particles_min_points_count) : 1;
		this->particles.push_back(new sf::CircleShape(particles_radius, particles_points_count));
		this->particles.back()->setOrigin(particles_radius, particles_radius);
		this->particles.back()->setPosition(center.x + (rand() % (int)radius * 2) - radius, center.y + (rand() % (int)radius * 2) - radius);
		this->particles.back()->setRotation(rand() % 360);
		this->particles.back()->setFillColor(particles_color);

		particles_count--;
	}
}

Explosion::~Explosion()
{
	while (!this->particles.empty())
	{
		delete this->particles.back();
		this->particles.pop_back();
	}
}

///Explosion Functions
void Explosion::update(const float& dt)
{
	this->done = false;

	for (auto& particle : this->particles)
	{
		///Fading
		sf::Color color = particle->getFillColor();
		int color_factor = this->fadingSpeed;

		color.a = color.a - color_factor < 0 ? 0 : color.a - color_factor;
		if (color.a == 0)
			this->done = true;

		particle->setFillColor(color);

		///Moving
		sf::Vector2f move_factor;
		move_factor.x = this->movingSpeed * dt * sin(particle->getRotation() * 3.14159265358979323846f / 180.f);
		move_factor.y = this->movingSpeed * dt * -cos(particle->getRotation() * 3.14159265358979323846f / 180.f);
		particle->move(move_factor);
	}
}

void Explosion::render(sf::RenderTarget* target)
{
	for (auto& particle : this->particles)
		target->draw(*particle);
}

///Spawn Constructors/Destructors
Spawn::Spawn(const sf::Vector2f& center, float radius,
	const sf::Color& particles_color, int particles_count,
	float particles_min_radius, float particles_max_radius,
	int particles_min_points_count, int particles_max_points_count,
	int fading_speed, float moving_speed,
	float effect_duration, float effect_period)
	: center(center), radius(radius < 1.f ? 1.f : radius)
	, particlesColor(particles_color), particlesCount(particles_count)
	, particlesMinRadius(particles_min_radius), particlesMaxRadius(particles_max_radius)
	, particlesMinPointsCount(particles_min_points_count), particlesMaxPointsCount(particles_max_points_count)
	, fadingSpeed(fading_speed), movingSpeed(moving_speed)
	, duration(effect_duration), period(effect_period)
	, durationTimer(0.f), periodTimer(0.f)
{
	this->done = false;
}

Spawn::~Spawn()
{
	while (!this->particles.empty())
	{
		delete this->particles.back();
		this->particles.pop_back();
	}
}

///Spawn Functions
void Spawn::update(const float& dt)
{
	this->done = false;
	this->durationTimer += dt;
	this->periodTimer += dt;

	if (this->periodTimer > this->period)
	{
		if (this->durationTimer < this->duration)
		{
			int particles_count = this->particlesCount;
			while (particles_count)
			{
				float particles_radius = this->particlesMaxRadius > 1.f ? (rand() % (int)(this->particlesMaxRadius + 1.f - this->particlesMinRadius) + this->particlesMinRadius) : 1.f;
				int particles_points_count = this->particlesMaxPointsCount > 1 ? (rand() % (this->particlesMaxPointsCount + 1 - this->particlesMinPointsCount) + this->particlesMinPointsCount) : 1;
				this->particles.push_back(new sf::CircleShape(particles_radius, particles_points_count));
				this->particles.back()->setOrigin(particles_radius, particles_radius);
				this->particles.back()->setPosition(center.x + (rand() % (int)this->radius * 2) - this->radius, center.y + (rand() % (int)this->radius * 2) - this->radius);
				this->particles.back()->setRotation(rand() % 360);
				this->particles.back()->setFillColor(this->particlesColor);

				particles_count--;
			}
		}

		this->periodTimer = 0.f;
	}

	for (auto& particle : this->particles)
	{
		///Fading
		sf::Color color = particle->getFillColor();
		int color_factor = this->fadingSpeed;

		color.a = color.a - color_factor < 0 ? 0 : color.a - color_factor;

		particle->setFillColor(color);

		///Moving
		sf::Vector2f move_factor;
		move_factor.x = this->movingSpeed * dt * sin(particle->getRotation() * 3.14159265358979323846f / 180.f);
		move_factor.y = this->movingSpeed * dt * -cos(particle->getRotation() * 3.14159265358979323846f / 180.f);
		particle->move(move_factor);
	}

	for (auto& particle : this->particles)
	{
		this->done = true;
		if (particle->getFillColor().a != 0)
		{
			this->done = false;
			break;
		}
	}
}

void Spawn::render(sf::RenderTarget* target)
{
	for (auto& particle : this->particles)
		target->draw(*particle);
}
