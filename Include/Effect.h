#ifndef EFFECT_H
#define EFFECT_H
#include <Include/Particle.h>

class Effect
{
protected:
	sf::Shape* target;
	bool done;
public:
	virtual ~Effect();
	virtual bool isDone();
	virtual const sf::Shape* getTarget() const;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

class Blink : public Effect
{
private:
	sf::Color baseFillColor;
	sf::Color currentColor;

	float duration;
	float timer;
public:
	Blink(sf::Shape* target, const sf::Color& default_color, float effect_duration);
	virtual ~Blink();
	
	void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
};

class Explosion : public Effect
{
private:
	std::vector<Particle*> particles;
public:
	Explosion(const sf::Vector2f& center, float radius,
		const sf::Color& particles_color, int particles_count,
		float particles_min_radius, float particles_max_radius,
		int particles_min_points_count, int particles_max_points_count,
		int min_fading_speed, int max_fading_speed,
		float min_moving_speed, float max_moving_speed);
	virtual ~Explosion();

	void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
};

class Spawn : public Effect
{
private:
	std::vector<Particle*> particles;
	sf::Vector2f center;
	float radius;

	sf::Color particlesColor;
	int particlesCount;

	float particlesMinRadius;
	float particlesMaxRadius;
	int particlesMinPointsCount;
	int particlesMaxPointsCount;

	int minFadingSpeed;
	int maxFadingSpeed;
	float minMovingSpeed;
	float maxMovingSpeed;

	float duration;
	float period;
	float durationTimer;
	float periodTimer;
public:
	Spawn(const sf::Vector2f& center, float radius,
		const sf::Color& particles_color, int particles_count,
		float particles_min_radius, float particles_max_radius,
		int particles_min_points_count, int particles_max_points_count,
		int min_fading_speed, int max_fading_speed,
		float min_moving_speed, float max_moving_speed,
		float effect_duration, float effect_period);
	virtual ~Spawn();
	
	void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
};

#include <Source/Effect.cpp>
#endif
