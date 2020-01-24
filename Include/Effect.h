#ifndef EFFECT_H
#define EFFECT_H

class Effect
{
protected:
	bool done;
public:
	virtual ~Effect() { this->done = false; }
	bool isDone() { return this->done; }
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

class Explosion : public Effect
{
private:
	std::vector<sf::CircleShape*> particles;
	
	int fadingSpeed;
	float movingSpeed;
public:
	Explosion(const sf::Vector2f& center, float radius,
		const sf::Color& particles_color, int particles_count,
		float particles_min_radius, float particles_max_radius,
		int particles_min_points_count, int particles_max_points_count,
		int fading_speed, float moving_speed);
	virtual ~Explosion();

	void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
};

class Blink : public Effect
{
private:
	sf::Shape* target;

	sf::Color defaultColor;
	sf::Color currentColor;

	float fadingSpeed;
	float duration;
	float timer;
public:
	Blink(sf::Shape* target, const sf::Color& default_color, float fading_speed, float effect_duration);
	virtual ~Blink();
	
	void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
};

class Spawn : public Effect
{
private:
	std::vector<sf::CircleShape*> particles;
	sf::Vector2f center;
	float radius;

	sf::Color particlesColor;
	int particlesCount;

	float particlesMinRadius;
	float particlesMaxRadius;
	int particlesMinPointsCount;
	int particlesMaxPointsCount;
	int fadingSpeed;
	float movingSpeed;

	float duration;
	float period;
	float durationTimer;
	float periodTimer;
public:
	Spawn(const sf::Vector2f& center, float radius,
		const sf::Color& particles_color, int particles_count,
		float particles_min_radius, float particles_max_radius,
		int particles_min_points_count, int particles_max_points_count,
		int fading_speed, float moving_speed,
		float effect_duration, float effect_period);
	virtual ~Spawn();
	
	void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
};

#include <Source/Effect.cpp>
#endif
