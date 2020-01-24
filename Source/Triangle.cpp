///Constructors/Destructors
Triangle::Triangle()
{
	this->defaultOrigin.x = this->defaultRadius;
	this->defaultOrigin.y = this->defaultRadius * 0.75f;
	this->defaultScale.x = 0.75f;
	this->defaultScale.y = 1.f;
	this->defaultPointCount = 3;

	this->setOrigin(this->defaultOrigin);
	this->setScale(this->defaultScale);
	this->setPointCount(this->defaultPointCount);
}

Triangle::~Triangle() { }
