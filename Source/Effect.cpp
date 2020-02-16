///Effect Constructors/Destructors
Effect::~Effect()
{
 	this->target = nullptr;
 	this->done = false;
}

///Effect Functions
bool Effect::isDone()
{
	return this->done;
}

const sf::Shape* Effect::getTarget() const
{
	return this->target;
}

///Blink Constructors/Destructors
Blink::Blink(sf::Shape* target, const sf::Color& default_color, float effect_duration)
	: baseFillColor(default_color), currentColor(target->getFillColor()), duration(effect_duration), timer(0.f)
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
		this->currentColor.r = this->currentColor.r + 50.f > 255 ? 255 : this->currentColor.r + 50.f;
		this->currentColor.g = this->currentColor.g + 50.f > 255 ? 255 : this->currentColor.g + 50.f;
		this->currentColor.b = this->currentColor.b + 50.f > 255 ? 255 : this->currentColor.b + 50.f;

		this->target->setFillColor(this->currentColor);
	}
	else if (this->timer < this->duration)
	{
		this->currentColor.r = this->currentColor.r - 50.f < this->baseFillColor.r ? this->baseFillColor.r : this->currentColor.r - 50.f;
		this->currentColor.g = this->currentColor.g - 50.f < this->baseFillColor.g ? this->baseFillColor.g : this->currentColor.g - 50.f;
		this->currentColor.b = this->currentColor.b - 50.f < this->baseFillColor.b ? this->baseFillColor.b : this->currentColor.b - 50.f;

		this->target->setFillColor(this->currentColor);
	}
	else
	{
		this->done = true;
		
		this->target->setFillColor(this->baseFillColor);
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
	int min_fading_speed, int max_fading_speed,
	float min_moving_speed, float max_moving_speed)
{
	this->done = false;
	radius = radius < 1.f ? 1.f : radius;

	while (particles_count)
	{
		///Particle Settings
		int fading_speed = rand() % (max_fading_speed + 1 - min_fading_speed) + min_fading_speed;
		float moving_speed = rand() % (int)(max_moving_speed + 1.f - min_moving_speed) + min_moving_speed;
		float radius = particles_min_radius > 1.f ? (rand() % (int)(particles_max_radius + 1.f - particles_min_radius) + particles_min_radius) : 1.f;
		int points_count = particles_max_points_count > 1 ? (rand() % (particles_max_points_count + 1 - particles_min_points_count) + particles_min_points_count) : 1;
		sf::Vector2f position = sf::Vector2f(center.x + (rand() % (int)radius * 2) - radius, center.y + (rand() % (int)radius * 2) - radius);

		this->particles.push_back(new Particle(position, particles_color, radius, points_count, rand() % 360, fading_speed, moving_speed));

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
		if (particle != nullptr)
			particle->update(dt);

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
	int min_fading_speed, int max_fading_speed,
	float min_moving_speed, float max_moving_speed,
	float effect_duration, float effect_period)
	: center(center), radius(radius < 1.f ? 1.f : radius)
	, particlesColor(particles_color), particlesCount(particles_count)
	, particlesMinRadius(particles_min_radius), particlesMaxRadius(particles_max_radius)
	, particlesMinPointsCount(particles_min_points_count), particlesMaxPointsCount(particles_max_points_count)
	, minFadingSpeed(min_fading_speed), maxFadingSpeed(max_fading_speed)
	, minMovingSpeed(min_moving_speed), maxMovingSpeed(max_moving_speed)
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
				///Particle Settings
				int fading_speed = rand() % (this->maxFadingSpeed + 1 - this->minFadingSpeed) + this->minFadingSpeed;
				float moving_speed = rand() % (int)(this->maxMovingSpeed + 1.f - this->minMovingSpeed) + this->minMovingSpeed;
				float radius = this->particlesMaxRadius > 1.f ? (rand() % (int)(this->particlesMaxRadius + 1.f - this->particlesMinRadius) + this->particlesMinRadius) : 1.f;
				int points_count = this->particlesMaxPointsCount > 1 ? (rand() % (this->particlesMaxPointsCount + 1 - this->particlesMinPointsCount) + this->particlesMinPointsCount) : 1;
				sf::Vector2f position = sf::Vector2f(this->center.x + (rand() % (int)this->radius * 2) - this->radius, this->center.y + (rand() % (int)this->radius * 2) - this->radius);

				this->particles.push_back(new Particle(position, this->particlesColor, radius, points_count, rand() % 360, fading_speed, moving_speed));

				particles_count--;
			}
		}

		this->periodTimer = 0.f;
	}

	for (auto& particle : this->particles)
		if (particle != nullptr)
			particle->update(dt);

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
