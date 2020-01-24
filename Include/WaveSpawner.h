#ifndef WAVESPAWNDER_H
#define WAVESPAWNDER_H

class WaveSpawner
{
public:
	sf::Vector2f position;
	int radius;
	int wavesCount;
	std::string enemyType;
	int enemyAmount;
public:
	WaveSpawner(const sf::Vector2f& position, const int& radius,
		const int& waves_count, const std::string& enemy_type, const int& enemy_amount);

	void spawnWave(std::list<Enemy*>& enemies);
};

#include <Source/WaveSpawner.cpp>
#endif
