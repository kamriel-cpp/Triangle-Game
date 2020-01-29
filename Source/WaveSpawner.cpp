//Constructors/Destructors
WaveSpawner::WaveSpawner(const sf::Vector2f& position, const int& radius,
	const int& waves_count, const std::string& enemy_type,
	const int& enemy_level, const int& enemy_amount)
{
	this->position = position;
	this->radius = radius;
	this->wavesCount = waves_count;
	this->enemyType = enemy_type;
	this->enemyLevel = enemy_level;
	this->enemyAmount = enemy_amount;
}

//Functions
void WaveSpawner::spawnWave(std::list<Enemy*>& enemies)
{
	if (this->wavesCount > 0)
	{
		int enemy_amount = this->enemyAmount;
		while (enemy_amount)
		{
			sf::Vector2f rand_position(sf::Vector2f(
				this->position.x + rand() % (this->radius * 2) - this->radius,
				this->position.y + rand() % (this->radius * 2) - this->radius));

			enemies.push_back(new Enemy(rand_position, this->enemyType, this->enemyLevel));
			enemy_amount--;
		}
		this->wavesCount--;
	}
}
