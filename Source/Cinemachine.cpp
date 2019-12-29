//Constructors/Destructors
Cinemachine::Cinemachine()
{
	this->camera = nullptr;
	this->target = nullptr;
}

Cinemachine::~Cinemachine()
{
	this->camera = nullptr;
	this->target = nullptr;
	delete this->camera;
	delete this->target;
}

//Functions
void Cinemachine::setCamera (Camera* camera)
{
	this->camera = camera;
}

void Cinemachine::setTarget (sf::Shape* target)
{
	this->target = target;
}

void Cinemachine::update(const float& dt)
{
	if (this->camera != nullptr && this->target != nullptr)
		this->camera->setCenter(this->target->getPosition());
}
