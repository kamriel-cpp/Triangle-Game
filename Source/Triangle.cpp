///Constructors/Destructors
Triangle::Triangle()
{
	this->customOrigin.x = this->customRadius;
	this->customOrigin.y = this->customRadius * 0.75f;
	this->customScale.x = 0.75f;
	this->customScale.y = 1.f;
	this->customPointCount = 3;

	this->setOrigin(this->customOrigin);
	this->setScale(this->customScale);
	this->setPointCount(this->customPointCount);
}

Triangle::~Triangle() { }
