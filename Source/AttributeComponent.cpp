//Constructors/Destructors
AttributeComponent::AttributeComponent(const int level)
{
	this->level = level;
	this->exp = 0;
	this->expNext = static_cast<int>((50 / 3) * (pow(this->level + 1, 3) - 6 * pow(this->level + 1, 2) + ((this->level + 1) * 17) - 12));
	this->attributePoints = level + 1;

	this->hp = 2;
	this->hpMax = 2;
	this->reloadTime = 1.f;
	this->spread = 30.f;
	this->damage = 1;
	this->bulletsPerShoot = 1;
	this->bulletSpeed = 200.f;
	this->bulletRadius = 5.f;

	this->updateLevel();
	this->randomSelectAllAttributePoints();
}

//Functions
void AttributeComponent::debugPrint()
{
	std::cout << this << ':' << '\n'
			  << "Level: " 			<< this->level << '\n'
			  << "Exp: " 			<< this->exp << '\n'
			  << "Exp Next: " 		<< this->expNext << '\n'
			  << "AP: " 			<< this->attributePoints << '\n'
			  << "HP: " 			<< this->hp << '\n'
			  << "Max HP: " 		<< this->hpMax << '\n'
			  << "Reload Time: " 	<< this->reloadTime << '\n'
			  << "Spread: " 		<< this->spread << '\n'
			  << "Damage: " 		<< this->damage << '\n'
			  << "BPS: " 			<< this->bulletsPerShoot << '\n'
			  << "Bullet Speed: " 	<< this->bulletSpeed << '\n'
			  << "Bullet Radius: " 	<< this->bulletRadius << '\n' << std::endl;
}

void AttributeComponent::resetHP()
{
	this->hp = this->hpMax;
}

void AttributeComponent::loseHP(const int hp)
{
	this->hp -= hp;

	if (this->hp < 0)
		this->hp = 0;
}

void AttributeComponent::gainHP(const int hp)
{
	this->hp += hp;

	if (this->hp > this->hpMax)
		this->hp = this->hpMax;
}

void AttributeComponent::loseEXP(const int exp)
{
	this->exp -= exp;

	if (this->exp < 0)
		this->exp = 0;
}

void AttributeComponent::gainEXP(const int exp)
{
	this->exp += exp;

	this->updateLevel();
}

const bool AttributeComponent::isDead() const
{
	return this->hp <= 0;
}

void AttributeComponent::randomSelectAllAttributePoints()
{
	while (this->attributePoints)
	{
		switch (rand() % 20)
		{
		case 0:
			///Reload Time
			this->reloadTime = this->reloadTime <= 0.1f ? 0.1f : this->reloadTime - 0.1f;
			this->spread = this->spread >= 45.f ? 45.f : this->spread + 2.5f;
			break;
		case 1:
			///Spread
			this->spread = this->spread - 5.f <= 0.f ? 0.f : this->spread - 5.f;
			break;
		case 2:
			///Damage
			this->damage++;
			break;
		case 3:
			///Bullets Per Shoot
			this->bulletsPerShoot++;
			this->spread = this->spread + 5.f >= 45.f ? 45.f : this->spread + 5.f;
			break;
		case 4:
			///Bullet Speed
			this->bulletSpeed = this->bulletSpeed+ 25.f >= 500.f ? 500.f : this->bulletSpeed + 25.f;
			this->spread = this->spread + 2.5f >= 45.f ? 45.f : this->spread + 2.5f;
			break;
		case 5:
			///Bullet Radius
			this->bulletRadius += 0.5f;
			this->spread = this->spread + 2.5f >= 45.f ? 45.f : this->spread + 2.5f;
			break;
		default:
			///Hit Points Maximum
			this->hpMax++;
			break;
		}
		this->attributePoints--;
	}
	this->hp = this->hpMax;
}

const bool AttributeComponent::selectAttributePoints(const int& choise)
{
	if (this->attributePoints)
	{
		switch (choise)
		{
		case 0:
			///Hit Points Maximum
			this->hpMax++;
			break;
		case 1:
			///Reload Time
			if (this->reloadTime - 0.1f <= 0.f)
			{
				this->reloadTime = 0.1f;
				return false;
			}
			this->reloadTime = this->reloadTime - 0.1f > 0.09f && this->reloadTime - 0.1f < 0.1f ? 0.1f : this->reloadTime - 0.1f;
			this->spread = this->spread + 2.5f >= 45.f ? 45.f : this->spread + 2.5f;
			break;
		case 2:
			///Spread
			if (this->spread - 5.f < 0.f)
			{
				this->spread = 0.f;
				return false;
			}
			this->spread -= 5.f;
			break;
		case 3:
			///Damage
			this->damage++;
			break;
		case 4:
			///Bullets Per Shoot
			this->bulletsPerShoot++;
			this->spread = this->spread >= 45.f ? 45.f : this->spread + 5.f;
			break;
		case 5:
			///Bullet Speed
			if (this->bulletSpeed + 25.f > 500.f)
			{
				this->bulletSpeed = 500.f;
				return false;
			}
			this->bulletSpeed += 25.f;
			this->spread = this->spread >= 45.f ? 45.f : this->spread + 2.5f;
			break;
		default:
			///Bullet Radius
			this->bulletRadius += 1.f;
			this->spread = this->spread >= 45.f ? 45.f : this->spread + 2.5f;
			break;
		}
		this->attributePoints--;
	}
	else
	{
		return false;
	}
	this->hp = this->hpMax;
	return true;
}

void AttributeComponent::updateLevel()
{
	while (this->exp >= this->expNext)
	{
		++this->level;
		this->exp -= this->expNext;
		this->expNext = static_cast<int>((50 / 3) * (pow(this->level, 3) - 6 * pow(this->level, 2) + (this->level * 17) - 12));
		++this->attributePoints;
	}
}

void AttributeComponent::update()
{
	this->updateLevel();
}
