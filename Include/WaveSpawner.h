#ifndef WAVESPAWNDER_H
#define WAVESPAWNDER_H

class WaveSpawner
{
public:
	sf::Vector2f position;
	int radius;
	int wavesCount;
	std::string enemyType;
	int enemyLevel;
	int enemyAmount;
public:
	WaveSpawner(const sf::Vector2f& position, const int& radius,
		const int& waves_count, const std::string& enemy_type,
		const int& enemy_level, const int& enemy_amount);
	virtual ~WaveSpawner();

	const bool canSpawnWave() const;
	void spawnWave(std::list<Unit*>& units);
};

#include <Source/WaveSpawner.cpp>
#endif
