//Constructors/Destructors
AttributeComponent::AttributeComponent()
{
	this->level = 1;
	this->exp = 0;
	this->expNext = static_cast<int>((50 / 3) * (pow(this->level + 1, 3) - 6 * pow(this->level + 1, 2) + ((this->level + 1) * 17) - 12));
	this->attributePoints = 2;

	this->vitality = 1;
	this->strength = 1;
	this->dexterity = 1;
	this->agility = 1;
	this->intelligence = 1;

	this->updateLevel();
	this->updateStats(true);
}

//Functions
void AttributeComponent::initVariables(const int level)
{
	this->level = level;
	this->exp = 0;
	this->expNext = static_cast<int>((50 / 3) * (pow(this->level + 1, 3) - 6 * pow(this->level + 1, 2) + ((this->level + 1) * 17) - 12));
	this->attributePoints = 2;

	this->vitality = 1;
	this->strength = 1;
	this->dexterity = 1;
	this->agility = 1;
	this->intelligence = 1;

	this->updateLevel();
	this->updateStats(true);
}

std::string AttributeComponent::debugPrint() const
{
	std::stringstream ss;

	ss << "Level: " << this->level << std::endl
		<< "Exp: " << this->exp << std::endl
		<< "Exp Next: " << this->expNext << std::endl
		<< "Attp: " << this->attributePoints << std::endl
		<< std::endl
		<< "Vitality: " << this->vitality << std::endl
		<< "Strength: " << this->strength << std::endl
		<< "Dexterity: " << this->dexterity << std::endl
		<< "Agility: " << this->agility << std::endl
		<< "Intelligence: " << this->intelligence << std::endl
		<< std::endl
		<< "HP: " << this->hp << std::endl
		<< "Max HP: " << this->hpMax << std::endl;

	return ss.str();
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

void AttributeComponent::updateStats(const bool reset)
{
	this->hpMax			= this->vitality * 5 + this->vitality + this->strength / 2 + this->intelligence / 5;
	this->damageMin		= this->strength * 2 + this->strength / 4 + this->intelligence / 5;
	this->damageMax		= this->strength * 2 + this->strength / 2 + this->intelligence / 5;
	this->accuracy		= this->dexterity * 5 + this->dexterity / 2 + this->intelligence / 5;
	this->defence		= this->agility * 2 + this->agility / 4 + this->intelligence / 5;
	this->luck			= this->intelligence * 2 + this->intelligence / 5;

	if (reset)
	{
		this->hp = this->hpMax;
	}
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
	if (this->attributePoints)
	{
		switch (rand() % 5)
		{
		case 0:
			this->vitality++;
			break;
		case 1:
			this->strength++;
			break;
		case 2:
			this->dexterity++;
			break;
		case 3:
			this->agility++;
			break;
		default:
			this->intelligence++;
			break;
		}
		attributePoints--;
	}
}


