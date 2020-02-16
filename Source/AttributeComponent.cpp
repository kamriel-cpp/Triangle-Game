///Constructors/Destructors
AttributeComponent::AttributeComponent(const int lvl)
{
	this->lvl = lvl;
	this->exp = 0;
	this->expNext = static_cast<int>((50 / 3) * (pow(this->lvl + 1, 3) - 6 * pow(this->lvl + 1, 2) + ((this->lvl + 1) * 17) - 12));
	this->aps = lvl + 5;
	this->hp = 3;
	this->mhp = 3;
	this->sps = 1;
	this->spr = 15;
	this->dmg = 1;
	this->bps = 1;
	this->bsp = 200;
	this->brd = 5;

	this->updateLevel();
	this->randomDistributeAPS();

	this->wasChangedLVL = true;
	this->wasChangedEXP = true;
	this->wasChangedAPS = true;
	this->wasChangedHP = true;
}

///Functions
const bool AttributeComponent::upgradeMHP()
{
	this->mhp++;
	this->hp = this->hp + 1 > this->mhp ? this->mhp : this->hp + 1;
	return true;
}

const bool AttributeComponent::upgradeSPS()
{
	if (this->sps + 1 > 10)
		return false;

	this->sps++;
	this->spr = this->spr + 5 >= 60 ? 60 : this->spr + 5;
	return true;
}

const bool AttributeComponent::upgradeSPR()
{
	if (this->spr - 20 < 0)
		return false;

	this->spr -= 20;
	return true;
}

const bool AttributeComponent::upgradeDMG()
{
	this->dmg++;
	return true;
}

const bool AttributeComponent::upgradeBPS()
{
	if (this->bps + 1 > 10)
		return false;

	this->bps++;
	this->spr = this->spr + 5 >= 60 ? 60 : this->spr + 5;
	return true;
}

const bool AttributeComponent::upgradeBSP()
{
	if (this->bsp + 50 > 500)
		return false;

	this->bsp += 50;
	this->spr = this->spr + 10 >= 60 ? 60 : this->spr + 10;
	return true;
}

const bool AttributeComponent::upgradeBRD()
{
	if (this->brd + 1 > 10)
		return false;

	this->brd++;
	this->spr = this->spr + 10 >= 60 ? 60 : this->spr + 10;
	return true;
}


void AttributeComponent::debugPrint()
{
	std::cout << this << ':' << '\n'
		<< "LVL: " 		<< this->lvl << '\n'
		<< "EXP: " 		<< this->exp << '\n'
		<< "EXPNEXT: " 	<< this->expNext << '\n'
		<< "APS: " 		<< this->aps << '\n'
		<< "HP: " 		<< this->hp << '\n'
		<< "MHP: " 		<< this->mhp << '\n'
		<< "SPS: " 		<< this->sps << '\n'
		<< "SPR: " 		<< this->spr << '\n'
		<< "DMG: " 		<< this->dmg << '\n'
		<< "BPS: " 		<< this->bps << '\n'
		<< "BSP: " 		<< this->bsp << '\n'
		<< "BRD: " 		<< this->brd << '\n' << std::endl;
}

void AttributeComponent::resetHP()
{
	this->hp = this->mhp;

	this->wasChangedHP = true;
}

void AttributeComponent::loseHP(const int hp)
{
	if (this->hp == 0) return;

	this->hp -= hp;

	if (this->hp < 0)
		this->hp = 0;

	this->wasChangedHP = true;
}

void AttributeComponent::gainHP(const int hp)
{
	if (this->hp == this->mhp) return;

	this->hp += hp;

	if (this->hp > this->mhp)
		this->hp = this->mhp;

	this->wasChangedHP = true;
}

void AttributeComponent::loseEXP(const int exp)
{
	if (this->exp == 0) return;

	this->exp -= exp;

	if (this->exp < 0)
		this->exp = 0;

	this->wasChangedEXP = true;
}

void AttributeComponent::gainEXP(const int exp)
{
	if (this->exp == this->expNext) return;

	this->exp += exp;

	this->updateLevel();

	this->wasChangedEXP = true;
}

const bool AttributeComponent::isDead() const
{
	return this->hp <= 0;
}


void AttributeComponent::randomDistributeAPS()
{
	while (this->aps)
	{
		int dice = rand() % 100 + 1;

		if (dice <= 50)
		{
			if (!this->upgradeMHP()) continue;
		}
		else if (dice > 50 && dice <= 55)
		{
			if (!this->upgradeSPS()) continue;
		}
		else if (dice > 55 && dice <= 60)
		{
			if (!this->upgradeSPR()) continue;
		}
		else if (dice > 60 && dice <= 65)
		{
			if (!this->upgradeDMG()) continue;
		}
		else if (dice > 65 && dice <= 70)
		{
			if (!this->upgradeBPS()) continue;
		}
		else if (dice > 70 && dice <= 85)
		{
			if (!this->upgradeBSP()) continue;
		}
		else if (dice > 85 && dice <= 100)
		{
			if (!this->upgradeBRD()) continue;
		}
		this->aps--;

		this->wasChangedAPS = true;
	}
}

const bool AttributeComponent::manualDistributeAPS(const int& choise)
{
	if (this->aps)
	{
		switch (choise)
		{
		case 0:
			if (!this->upgradeMHP()) return false;
			break;
		case 1:
			if (!this->upgradeSPS()) return false;
			break;
		case 2:
			if (!this->upgradeSPR()) return false;
			break;
		case 3:
			if (!this->upgradeDMG()) return false;
			break;
		case 4:
			if (!this->upgradeBPS()) return false;
			break;
		case 5:
			if (!this->upgradeBSP()) return false;
			break;
		default:
			if (!this->upgradeBRD()) return false;
			break;
		}
		this->aps--;

		this->wasChangedAPS = true;
	}
	else return false;

	return true;
}

void AttributeComponent::updateLevel()
{
	while (this->exp >= this->expNext)
	{
		++this->lvl;
		this->exp -= this->expNext;
		this->expNext = static_cast<int>((50 / 3) * (pow(this->lvl, 3) - 6 * pow(this->lvl, 2) + (this->lvl * 17) - 12));
		++this->aps;
		
		this->wasChangedLVL = true;
		this->wasChangedEXP = true;
		this->wasChangedAPS = true;
	}
}
