///Constructors/Destructors
Triangle::Triangle()
{
	this->baseOrigin.x = this->baseRadius;
	this->baseOrigin.y = this->baseRadius * 0.75f;
	this->baseScale.x = 0.75f;
	this->baseScale.y = 1.f;
	this->basePointCount = 3;

	this->setOrigin(this->baseOrigin);
	this->setScale(this->baseScale);
	this->setPointCount(this->basePointCount);
}

Triangle::~Triangle() { }
